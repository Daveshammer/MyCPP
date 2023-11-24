#include<mutex>
#include <queue>
#include<condition_variable>

/*
    隐患:
    如果在调用WaitAndPop函数时发生了异常，由于可能有其他的线程也在调用WaitAndPop发生等待，
    而由于每次notify一个线程，一旦构造 std::shared_ptr的过程中发生异常，那么其他的线程将会陷入永久的等待！

    解决方法： 由于异常发生在内存的申请过程中，我们如果把 std::queue 中直接存入 shared_ptr 那么就不会有这个问题。
*/

template <typename T>
class ThreadSafeQueue
{
public:
    void Push(T new_value)
    {
        std::lock_guard<std::mutex> lk(m_mtx);
        m_queue.push(std::move(new_value));
        m_cond.notify_one(); // 1
    }

    void WaitAndPop(T &value) // 2
    {
        std::unique_lock<std::mutex> lk(m_mtx);
        m_cond.wait(lk, [this] { // 条件变量产生的虚假唤醒，你可以通过手动while循环来避免，也可以通过在wait后面加上谓词条件（lamda表达式）
            return !m_queue.empty(); 
        });
        value = std::move(m_queue.front());
        m_queue.pop();
    }

    std::shared_ptr<T> WaitAndPop() // 3
    {
        std::unique_lock<std::mutex> lk(m_mtx);
        m_cond.wait(lk, [this] { 
            return !m_queue.empty(); 
        }); // 4
        std::shared_ptr<T> res(
            std::make_shared<T>(std::move(m_queue.front())));
        m_queue.pop();
        return res;
    }

    bool TryPop(T &value)
    {
        std::lock_guard<std::mutex> lk(m_mtx);
        if (m_queue.empty())
            return false;
        value = std::move(m_queue.front());
        m_queue.pop();
        return true;
    }

    std::shared_ptr<T> TryPop()
    {
        std::lock_guard<std::mutex> lk(m_mtx);
        if (m_queue.empty())
            return std::shared_ptr<T>(); // 5
        std::shared_ptr<T> res(
            std::make_shared<T>(std::move(m_queue.front())));
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
    queue<T> m_queue;
    condition_variable m_cond;
};