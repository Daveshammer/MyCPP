#include <iostream>
#include <thread>
#include <list>
#include <mutex>
using namespace std;

/*
模拟车站三个窗口买票的场景
*/
int ticketCount = 100; // 假设一共有100张票，由三个窗口一起卖票
mutex mtx;             // 互斥量

// 模拟卖票的线程函数
void sellTicket(int index)
{
    while (ticketCount > 0)
    {
        // mtx.lock(); // 加锁
        {
            lock_guard<mutex> lock(mtx);
            if (ticketCount > 0)
            {
                cout << "窗口" << index << "卖出了第" << ticketCount << "张票" << endl;
                ticketCount--;
            }
        } // 离开作用域，lock_guard自动解锁
        // mtx.unlock(); // 解锁
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main()
{
    list<thread> tlist;
    for (int i = 1; i <= 3; ++i)
    {
        tlist.push_back(thread(sellTicket, i));
    }
    for (thread &t : tlist)
    {
        t.join();
    }

    return 0;
}