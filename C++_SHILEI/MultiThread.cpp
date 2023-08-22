#include <iostream>
#include <memory>
#include <thread>
using namespace std;

class A
{
public:
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
    void testA()
    {
        cout << "testA()" << endl;
    }
};

void handler01(weak_ptr<A> q)
{
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 睡眠1秒，等待主线程中的A对象析构
    shared_ptr<A> p = q.lock();
    if (p != nullptr)
    {
        p->testA();
    }
    else
    {
        cout << "A对象已经析构，不能再访问" << endl;
    }
}

int main()
{
    {
        shared_ptr<A> p(new A());
        thread t1(handler01, weak_ptr<A>(p));
        t1.detach(); // 分离线程，线程独立运行，主线程不会等待线程t1执行完毕
    } // ~A()
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 睡眠2秒，等待线程t1执行完毕


    return 0;
}