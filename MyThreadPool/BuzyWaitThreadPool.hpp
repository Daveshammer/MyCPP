//
// Created by Alone on 2022-8-24.
//

#ifndef MYUTIL_THREAD_POOL_H
#define MYUTIL_THREAD_POOL_H

#include<thread>
#include<future>
#include<vector>
#include<memory>

namespace util
{
    using std::shared_ptr;
    using std::mutex;
    using std::lock_guard;
    using std::condition_variable;
    using std::unique_lock;

    template<typename T>
    class ThreadSafeQueue
    {
    private:
        struct node
        {
            shared_ptr<T> data_;
            node *next_{};
        };
    public:
        ThreadSafeQueue() : m_head(new node), m_tail(m_head)
        {}

        ~ThreadSafeQueue()
        {
            destroy();
        }

        ThreadSafeQueue(ThreadSafeQueue const &) = delete;

        ThreadSafeQueue &operator=(ThreadSafeQueue const &) = delete;
        
        void Push(T value)
        {
            auto p = std::make_shared<T>(std::move(value));
            node *new_tail = new node;
            {
                lock_guard<mutex> tail_lock(m_tailMtx);
                m_tail->data_ = std::move(p);
                m_tail->next_ = new_tail;
                m_tail = new_tail;
            }
            m_cond.notify_one();
        }

        shared_ptr<T> WaitAndPop()
        {
            node *old_head = wait_pop_head();
            auto ret = old_head->data_;
            delete old_head;
            return ret;
        }

        void WaitAndPop(T &value)
        {
            node *old_head = wait_pop_head(value);
            delete old_head;
        }

        shared_ptr<T> TryPop()
        {
            node *old_head = try_pop_head();

            if (!old_head) return nullptr;

            auto ret = old_head->data_;
            delete old_head;
            return ret;
        }

        bool TryPop(T &value)
        {
            node *old_head = try_pop_head(value);

            if (!old_head)return false;

            delete old_head;

            return true;
        }

    private:
        node *get_tail()
        {
            lock_guard<mutex> tail_lock(m_tailMtx);
            return m_tail;
        }

        node *pop_head()
        {
            auto *old_head = m_head;
            m_head = m_head->next_;
            return old_head;
        }

        unique_lock<mutex> wait_for_data()
        {
            unique_lock<mutex> head_lock(m_headMtx);
            m_cond.wait(head_lock, [this]
            {
                return m_head != get_tail();
            });
            return std::move(head_lock);
        }

        node *wait_pop_head()
        {
            unique_lock<mutex> head_lock(wait_for_data());
            return pop_head();
        }

        node *wait_pop_head(T &value)
        {
            unique_lock<mutex> head_lock(wait_for_data());
            value = std::move(*(m_head->data_));
            return pop_head();
        }

        node *try_pop_head()
        {
            lock_guard head_lock(m_headMtx);
            if (m_head == get_tail())
            {
                return nullptr;
            }
            return pop_head();
        }

        node *try_pop_head(T &value)
        {
            lock_guard head_lock(m_headMtx);
            if (m_head == get_tail())
            {
                return nullptr;
            }
            value = std::move(*(m_head->data_));
            return pop_head();
        }

        void destroy()
        {
            std::lock(m_headMtx, m_tailMtx); //获得锁确保操作的内存不被共享
            while (m_head)
            {
                auto *next = m_head->next_;
                delete m_head;
                m_head = next;
            }
        }

    private:
        condition_variable m_cond;
        mutex m_headMtx;
        node *m_head;
        mutex m_tailMtx;
        node *m_tail;
    };
}

namespace util
{
    using std::vector;
    using std::thread;

    class Joiner
    {
    public:
        explicit Joiner(vector<thread> &threads) : m_threads(threads)
        {}

        ~Joiner()
        {
            for (auto &&th: m_threads)
            {
                if (th.joinable())
                {
                    th.join();
                }
            }
        }

    private:
        vector<thread> &m_threads;
    };
}

namespace util
{
    using std::thread;
    using std::future;
    using std::packaged_task;
    using std::vector;
    using std::unique_ptr;

    class FunctionWrapper
    {
        //类型擦除的基础类型
        struct impl_base
        {
            virtual void call() = 0;

            virtual ~impl_base() = default;
        };

        //类型擦除的实现类型
        template<typename F>
        struct impl_type : public impl_base
        {
            F f;

            explicit impl_type(F &&f) : f(std::move(f))
            {}

            void call() override
            {
                f();
            }
        };

    public:
        template<typename F>
        FunctionWrapper(F &&func):m_impl(new impl_type<F>(std::forward<F>(func)))
        {}

        FunctionWrapper(FunctionWrapper &&other) noexcept: m_impl(std::move(other.m_impl))
        {}

        FunctionWrapper() = default;

        FunctionWrapper &operator=(FunctionWrapper &&other)
        noexcept
        {
            m_impl = std::move(other.m_impl);
            return *this;
        }

        void operator()()
        {
            m_impl->call();
        }

        FunctionWrapper(FunctionWrapper const &) = delete;

        FunctionWrapper(FunctionWrapper &) = delete;

        FunctionWrapper &operator=(FunctionWrapper &) = delete;

    private:
        std::unique_ptr<impl_base> m_impl;
    };


    class ThreadPool
    {
    public:
        explicit ThreadPool(uint32_t threadNum = std::thread::hardware_concurrency()) : m_done(false),
                                                                                        m_joiner(m_threads)
        {
            try
            {
                for (int i = 0; i < threadNum; i++)
                {
                    m_threads.emplace_back(thread(&ThreadPool::worker_thread, this));
                }
            } catch (...)
            {
                m_done = true;
                throw std::runtime_error("add thread error");
            }
        }

        ~ThreadPool()
        {
            m_done = true;
        }

        template<typename FunctionType>
        std::future<typename std::result_of<FunctionType()>::type> submit(FunctionType f)
        {
            using resultType = typename std::result_of<FunctionType()>::type;
            packaged_task<resultType()> task(std::move(f));
            future<resultType> res(task.get_future());
            m_queue.Push(std::move(task));
            return res;
        }

    private:
        void worker_thread()
        {
            while (!m_done)
            {
                FunctionWrapper task;
                if (m_queue.TryPop(task))
                {
                    task();
                } else
                {
                    std::this_thread::yield(); //当前线程挂起，避免争抢资源
                }
            }
        }

    private:
        std::atomic<bool> m_done;
        util::ThreadSafeQueue<FunctionWrapper> m_queue;
        vector<thread> m_threads;
        util::Joiner m_joiner;
    };
}
#endif //MYUTIL_THREAD_POOL_H