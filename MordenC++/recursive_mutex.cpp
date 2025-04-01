#include <iostream>
#include <mutex>

class Dosomething
{
public:
    void doSomething()
    {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        // std::lock_guard<std::mutex> lock2(m_mutex2);
        std::cout << "do something" << std::endl;
        doSomethingElse();
    }

    void doSomethingElse()
    {
        std::lock_guard<std::recursive_mutex> lock(m_mutex); // OK
        // std::lock_guard<std::mutex> lock2(m_mutex2); // deadlock
        std::cout << "do something else" << std::endl;
    }

private:
    std::recursive_mutex m_mutex;
    // std::mutex m_mutex2;
};

int main()
{
    Dosomething ds;
    ds.doSomething();
    return 0;
}