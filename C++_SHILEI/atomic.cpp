#include <iostream>
#include <atomic>
#include <thread>
#include <list>
using namespace std;

volatile atomic_bool isReady(false);
volatile atomic_int mycount(0);

void task()
{
    while (!isReady)
    {
        this_thread::yield(); // 线程让出当前的CPU时间片，让其它线程去执行
    }
    for (int i = 0; i < 100; ++i)
    {
        mycount ++;
    }
}

int main()
{
    list<thread> threads;
    for (int i = 0; i < 10; ++i)
    {
        threads.push_back(thread(task));
    }

    // this_thread::sleep_for(chrono::seconds(3));
    isReady = true;

    for (auto &t : threads)
    {
        t.join();
    }
    cout << "mycount: " << mycount << endl;

    return 0;
}