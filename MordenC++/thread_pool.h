#include "thread_safe_queue_v5.h"
#include <vector>
#include <thread>
#include <memory>
#include <future>

using std::future;
using std::packaged_task;
using std::thread;
using std::vector;

class Joiner
{
public:
    explicit Joiner(vector<thread> &threads) : m_threads(threads)
    {
    }

    ~Joiner()
    {
        for (auto &&th : m_threads)
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

class FunctionWrapper
{
    // 类型擦除的基础类型
    struct impl_base
    {
        virtual void call() = 0;

        virtual ~impl_base() = default;
    };

    // 类型擦除的实现类型
    template <typename F>
    struct impl_type : public impl_base
    {
        F f;

        explicit impl_type(F &&f) : f(std::move(f))
        {
        }

        void call() override
        {
            f();
        }
    };

public:
    template <typename F>
    FunctionWrapper(F &&func) : m_impl(new impl_type<F>(std::forward<F>(func)))
    {
    }

    FunctionWrapper(FunctionWrapper &&other) noexcept : m_impl(std::move(other.m_impl))
    {
    }

    FunctionWrapper() = default;

    FunctionWrapper &operator=(FunctionWrapper &&other) noexcept
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
        }
        catch (...)
        {
            m_done = true;
            throw std::runtime_error("add thread error");
        }
    }

    ~ThreadPool()
    {
        m_done = true;
    }

    template <typename FunctionType>
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
            }
            else
            {
                // 使用this_thread::yield()是不是会在程序闲时会使得死循环线程一直
                // 在“获得时间片-yield让出-下个时间片再次获得”中循环，然后导致CPU占用升高。
                std::this_thread::yield(); // 当前线程挂起，避免争抢资源，
            }
        }
    }

private:
    std::atomic<bool> m_done;
    ThreadSafeQueue<FunctionWrapper> m_queue;
    vector<thread> m_threads;
    Joiner m_joiner;
};