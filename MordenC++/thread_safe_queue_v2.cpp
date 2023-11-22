#include<mutex>
#include <queue>
#include<condition_variable>

/*
    优点：
    不仅是预防了异常安全，同样性能也得到了很好的优化，Push 过程的内存申请过程可以放到临界区以外，提高了并发度。

    缺点：
    几乎没有任何并发的性能，因为所有的成员函数都必须加锁，临界区非常的大
    
    原因：由于我们是通过stl内部的queue封装所实现的，我们的任何的成员函数操作实现都必须访问到这个共享变量，
    一旦变量被共享，要实现线程安全那就必须加锁同步
*/

template <typename T>
class ThreadSafeQueue
{
public:
    void Push(T new_value)
    {
        auto data = std::make_shared(std::move(new_value)); // 改为存智能指针
        std::lock_guard<std::mutex> lk(m_mtx);
        m_queue.push(data);
        m_cond.notify_one(); // 1
    }

    void WaitAndPop(T &value) // 2
    {
        std::unique_lock<std::mutex> lk(m_mtx);
        m_cond.wait(lk, [this] { 
            return !m_queue.empty(); 
        });
        value = std::move(*m_queue.front()); // 对智能指针解引用
        m_queue.pop();
    }

    std::shared_ptr<T> WaitAndPop() // 3
    {
        std::unique_lock<std::mutex> lk(m_mtx);
        m_cond.wait(lk, [this] { 
            return !m_queue.empty(); 
        }); // 4
        std::shared_ptr<T> res = m_queue.front();
        m_queue.pop();
        return res;
    }

    bool TryPop(T &value)
    {
        std::lock_guard<std::mutex> lk(m_mtx);
        if (m_queue.empty())
            return false;
        value = std::move(*m_queue.front());
        m_queue.pop();
        return true;
    }

    std::shared_ptr<T> TryPop()
    {
        std::lock_guard<std::mutex> lk(m_mtx);
        if (m_queue.empty())
            return std::shared_ptr<T>(); // 5
        std::shared_ptr<T> res = m_queue.front();
        m_queue.pop();
        return res;
    }

    bool Empty() const
    {
        std::lock_guard<std::mutex> lk(m_mtx);
        return m_queue.empty();
    }

private:
    mutable mutex m_mtx; // 锁需要设置为mutable，保证const版本的成员函数可用
    queue<std::shared_ptr<T>> m_queue;
    condition_variable m_cond;
};