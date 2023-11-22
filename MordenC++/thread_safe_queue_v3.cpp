#include<mutex>
#include <queue>
#include<condition_variable>

/*
    非线程安全细粒度队列
    不使用STL中的queue，而是自己实现一个链式队列，这样就可以把锁的粒度减少，实际就是把变量的共享和操作细分。
*/

#if 0
/*
    缺点：
    1.pop操作需要用到head，push操作需要用到head和tail
    2.
    
    未采用空头节点，两个成员函数内用 next_ 指针访问到的内存都可能发生共享（对应 m_tail->next_ 与 oldHead->next_）
*/
template<typename T>
class Queue
{
private:
    struct node
    {
        T data_;
        std::unique_ptr <node> next_; // 使用了unique_ptr管理next_指针，那么析构的时候会自动完成;如果队列中的数据量大的话（大概1e4），整个函数栈会爆掉

        node(T data) : data_(std::move(data))
        {}
    };

    std::unique_ptr <node> m_head;
    node *m_tail{};

public:
    Queue() = default;

    Queue(const Queue &other) = delete;

    Queue &operator=(const Queue &other) = delete;

    std::shared_ptr <T> TryPop()
    {
        if (!m_head)
        {
            return nullptr;
        }
        auto ret = std::make_shared<T>(std::move(m_head->data_));
        auto oldHead = std::move(m_head); 
        m_head = std::move(oldHead->next_); //这里把next资源进行转移，防止oldHead析构后导致整个链表析构
        return ret;
    }

    void Push(T new_value)
    {
        auto p = std::make_unique<node>(new_value);
        auto *new_tail = p.get();
        if (m_tail)
        {//如果队列不为空
            m_tail->next_ = std::move(p);
        } else
        {//队列为空则需要特殊处理
            m_head = std::move(p);
        }
        m_tail = new_tail;
    }
};
#endif

/*
    预分配一个虚拟节点(无数据)，确保这个节点永远在队列的最后，用来分离头尾指针能访问的节点
    两个操作共享的内存就只有 m_head 和 m_tail 了，且在 Push 操作中只使用到了m_tail
*/
template<typename T>
class Queue
{
private:
    struct node
    {
        std::shared_ptr<T> data_;
        std::unique_ptr <node> next_;
    };

    std::unique_ptr <node> m_head;
    node *m_tail; // m_tail指向最后一个节点（空节点）

public:
    Queue():m_head(new node),m_tail(m_head.get()){}; //初始化空节点

    Queue(const Queue &other) = delete;

    Queue &operator=(const Queue &other) = delete;

    std::shared_ptr <T> TryPop()
    {
        if (m_head.get() == m_tail)
        {
            return nullptr;
        }
        auto ret = m_head->data_;
        auto oldHead = std::move(m_head); 
        m_head = std::move(oldHead->next_);
        return ret;
    }

    void Push(T new_value)
    {
        auto data = std::make_shared<T>(std::move(new_value));
        auto p = std::make_unique<node>(new_value); //新的空节点
        m_tail->data_ = data;
        //开始移动补充最后的空节点
        auto* new_tail = p.get();
        m_tail->next_ = std::move(p); 
        m_tail = new_tail; //更新尾指针
    }
};