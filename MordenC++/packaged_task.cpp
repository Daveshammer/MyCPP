#include <future>
#include <iostream>
#include <thread>

//首先创建一个promise，通过promise可以拿到future，future有wait()和get()等方法，这种方法会阻塞当前线程，
//直到future的源promise调用了set_value，future的wait()只有阻塞功能，而
//get()方法不仅有阻塞功能，还能拿到set_value()设置的值。
void test1()
{
    std::promise<bool> prom;
    std::future<bool> f = prom.get_future();
    prom.set_value(true);
    std::cout << f.get() << std::endl;
}

void test2()
{
    std::promise<bool> prom;
    std::future<bool> f = prom.get_future();
    std::thread t(
        [](std::promise<bool> p)
        {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        p.set_value(true); 
        },
        std::move(prom));

    std::cout << f.get() << std::endl;
    if (t.joinable()) t.join();
}

// packaged_task ≈ promise + function
void test3()
{
    std::packaged_task<int(int, int)> task([](int a, int b) { return a + b; });
    std::future<int> f = task.get_future();
    std::thread t(std::move(task), 1, 2);
    std::cout << f.get() << std::endl;
    if (t.joinable()) t.join();
}


// future不能拷贝，只能移动，这就意味着只能有一个线程一个实例可以通过get()拿到对应的结果
// 如果想要多个线程多个实例拿到结果，可以通过future的share()可拿到shared_future
void test4()
{
    std::promise<int> prom;
    std::future<int> f = prom.get_future();
    std::shared_future<int> shared_f = f.share();
    std::future<void> f1 = std::async(std::launch::async, [shared_f]() { std::cout << "f1" << shared_f.get() << std::endl; } );
    auto f2 = std::async(std::launch::async, [shared_f]() { std::cout << "f2" << shared_f.get() << std::endl; } );
    prom.set_value(123);
    f1.get();
    f2.get();
}

int main()
{
    test3();
    return 0;
}