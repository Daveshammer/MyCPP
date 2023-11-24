#include<mutex>
#include <queue>
#include<condition_variable>

/*
    在v3的基础上，添加互斥锁，实现线程安全
*/

template<typename T>
class ThreadSafeQueue
{
    struct node
    {
        std::shared_ptr <T> data;
        std::unique_ptr <node> next;
    };
    std::mutex m_headMtx;
    std::unique_ptr <node> m_head;
    std::mutex m_tailMtx;
    node *m_tail;

public:
    ThreadSafeQueue() :
            m_head(new node), m_tail(m_head.get())
    {}

    ThreadSafeQueue(const ThreadSafeQueue &other) = delete;

    ThreadSafeQueue &operator=(const ThreadSafeQueue &other) = delete;

    std::shared_ptr <T> TryPop() // 持有m_tailMtx的时间很短，可以并发访问
    {
        std::unique_ptr <node> old_head = pop_head();
        return old_head ? old_head->data : std::shared_ptr<T>();
    }

    void Push(T new_value)
    {
        std::shared_ptr <T> new_data(
                std::make_shared<T>(std::move(new_value)));
        std::unique_ptr <node> p(new node);
        node *const new_tail = p.get();
        
        //开始锁临界区
        std::lock_guard <std::mutex> tail_lock(m_tailMtx);
        m_tail->data = new_data;
        m_tail->next = std::move(p);
        m_tail = new_tail;
    }

private:
    
    node *get_tail()
    {
        std::lock_guard <std::mutex> tail_lock(m_tailMtx);
        return m_tail;
    }

    std::unique_ptr <node> pop_head()
    {
        //这里head一定要先被锁
        std::lock_guard <std::mutex> head_lock(m_headMtx);
        if (m_head.get() == get_tail())
        {
            return nullptr;
        }
        std::unique_ptr <node> old_head = std::move(m_head); // 暂存出队节点
        m_head = std::move(old_head->next); // 头指针指向下一个节点
        return old_head;
    }
};