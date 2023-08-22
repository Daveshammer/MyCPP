#include <iostream>
#include <typeinfo>
#include <string>
#include <functional>
#include <thread>
#include <vector>
using namespace std;

class Thread
{
public:
    Thread(function<void(int)> func, int no) : _func(func), _no(no) {}
    thread start() { return thread(_func); }

private:
    function<void(int)> _func; // 线程函数，需要一个int类型的参数
    int _no; //线程编号
};
class ThreadPool
{
public:
    ThreadPool() {}
    ~ThreadPool()
    {
        // 释放Thread对象占用的堆资源
        for (int i = 0; i < _pool.size(); ++i)
        {
            delete _pool[i];
        }
    }
    // 开启线程池
    void startPool(int size)
    {
        for (int i = 0; i < size; ++i)
        {
            _pool.push_back(new Thread(bind(&ThreadPool::runInThread, this, placeholders::_1), i));
        }
        for (int i = 0; i < size; ++i)
        {
            _handler.push_back(_pool[i]->start());
        }
        for (thread &t : _handler)
        {
            t.join();
        }
    }

private:
    vector<Thread *> _pool;
    vector<thread> _handler;
    // 把runInThread这个成员方法充当线程函数 thread pthread_create
    void runInThread(int id)
    {
        cout << "call runInThread! id:" << id << endl;
    }
};

int main()
{
    ThreadPool pool;
    pool.startPool(1000);

    return 0;
}

#if 0 // bind和function的使用
void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
class Test
{
public:
    int sum(int a, int b) { return a + b; }
};

int main()
{
    // bind是函数模板 可以自动推演模板类型参数
    bind(hello, "hello bind")();
    cout << bind(sum, 10, 20)() << endl;
    cout << bind(&Test::sum, Test(), 10, 20)() << endl;

    // 参数占位符
    bind(hello, placeholders::_1)("hello placeholders::_1"); 

    // 此处把bind返回的绑定器binder就复用起来了
    function<void(string)> func1 = bind(hello, placeholders::_1);
    func1("hello func1.1");
    func1("hello func1.2");

    return 0;
}
#endif