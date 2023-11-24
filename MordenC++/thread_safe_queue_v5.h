#include <memory>
#include <condition_variable>
#include <mutex>

/*
    在v4的基础上，添加条件变量
*/

using std::condition_variable;
using std::lock_guard;
using std::mutex;
using std::shared_ptr;
using std::unique_lock;
using std::unique_ptr;

template <typename T>
class ThreadSafeQueue
{
private:
    struct node
    {
        shared_ptr<T> data_;
        // 使用了unique_ptr管理next_指针，那么析构的时候会自动完成;如果队列中的数据量大的话（大概1e4），整个函数栈会爆掉
        // 这个问题可以通过对节点逐个进行析构来解决
        unique_ptr<node> next_; 
    };
    condition_variable m_cond;
    mutex m_headMtx;
    unique_ptr<node> m_head;
    mutex m_tailMtx;
    node *m_tail;

public:
    ThreadSafeQueue() : m_head(new node), m_tail(m_head.get())
    {
    }
    ~ThreadSafeQueue()
    {
        while (m_head)
        {
            unique_ptr<node> next = std::move(m_head->next_);
            m_head = std::move(next);
        }
    }

    ThreadSafeQueue(ThreadSafeQueue const &) = delete;

    ThreadSafeQueue &operator=(ThreadSafeQueue const &) = delete;

    void Push(T new_value)
    {
        auto new_data = std::make_shared<T>(std::move(new_value));
        
        std::unique_ptr<node> p(new node);
        { // 生产临界区
            std::lock_guard<std::mutex> tail_lock(m_tailMtx);
            m_tail->data_ = new_data;
            auto *new_tail = p.get();
            m_tail->next_ = std::move(p);
            m_tail = new_tail;
        }
        m_cond.notify_one();
    }

    std::shared_ptr<T> WaitAndPop()
    {
        std::unique_ptr<node> const old_head = wait_pop_head();
        return old_head->data_;
    }

    void WaitAndPop(T &value)
    {
        auto _ = wait_pop_head(value);
    }

    std::shared_ptr<T> TryPop()
    {
        std::unique_ptr<node> old_head = try_pop_head();
        return old_head ? old_head->data : std::shared_ptr<T>();
    }

    bool TryPop(T &value)
    {
        std::unique_ptr<node> const old_head = try_pop_head(value);
        return old_head ? true : false;
    }

    void Empty()
    {
        std::lock_guard<std::mutex> head_lock(m_headMtx);
        return (m_head.get() == get_tail());
    }

private:
    node *get_tail()
    {
        lock_guard<mutex> tail_lock(m_tailMtx);
        return m_tail;
    }

    unique_ptr<node> pop_head() // 出队（代码复用）
    {
        auto old_head = std::move(m_head);
        m_head = std::move(old_head->next_);
        return old_head;
    }

    unique_lock<mutex> wait_for_data() // 队列为空就等待数据（代码复用）
    {
        unique_lock<mutex> head_lock(m_headMtx);
        m_cond.wait(head_lock, [&] { // 队列为空就阻塞等待
            return m_head.get() != get_tail(); 
        });
        return std::move(head_lock); // 将锁转移给wait_pop_head
    }

    unique_ptr<node> wait_pop_head() // 版本1
    {
        unique_lock<mutex> head_lock(wait_for_data()); // 从wait_for_data中获取锁
        return pop_head();
    }

    unique_ptr<node> wait_pop_head(T &value)
    {
        unique_lock<mutex> head_lock(wait_for_data());
        value = std::move(*(m_head->data_));
        return pop_head();
    }

    unique_ptr<node> try_pop_head()
    {
        std::lock_guard<std::mutex> head_lock(m_headMtx);
        if (m_head.get() == get_tail())
        {
            return std::unique_ptr<node>();
        }
        return pop_head();
    }

    unique_ptr<node> try_pop_head(T &value)
    {
        std::lock_guard<std::mutex> head_lock(m_headMtx);
        if (m_head.get() == get_tail())
        {
            return std::unique_ptr<node>();
        }
        value = std::move(*(m_head->data_));
        return pop_head();
    }
};
