#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

/*
C++多线程编程 - 线程间的同步通信机制
多线程编程两个问题：
1.线程间的互斥
竟态条件 =》 临界区代码段 => 保证原子操作 =》 互斥锁mutex 轻量级的无锁实现CAS
2.线程间的同步通信
生产者消费者模型

*/
class Queue
{
public:
    void put(int val)
    {
        unique_lock<mutex> lock(mtx); // 互斥锁，保证线程安全
        while (!que.empty())
        {
            // que不为空，生产者应该通知消费者去消费，消费完了，再继续生产
            // 生产者线程应该进入等待状态，并且把mtx互斥锁释放掉            
            cv.wait(lock);
        }
        que.push(val);
        cout << "生产者 生产：" << val << "号物品" << endl;
        /*
        通知其它线程，可以去消费了
        其它线程得到通知，就会从等待状态 =》 阻塞状态 =》 获取互斥锁 =》 执行代码
        */ 
        cv.notify_all(); 
    }

    int get()
    {
        unique_lock<mutex> lock(mtx);
        while (que.empty())
        {
            // 消费者线程发现que是空的，通知生产者线程先生产物品
            // 进入等待状态，并且把mtx互斥锁释放掉            
            cv.wait(lock); // 等待
        }
        int val = que.front();
        cout << "消费者 消费：" << val << "号物品" << endl;
        que.pop();
        cv.notify_all(); // 消费完了，通知生产者线程，可以去生产了
        return val;
    }
private:
    queue<int> que;
    mutex mtx; // 定义互斥锁，做线程间的互斥操作
    condition_variable cv; // 定义条件变量，做线程间的同步通信操作
};

void producer(Queue *que)
{
    for (int i = 0; i < 1000; ++i)
    {
        que->put(i);
        // this_thread::sleep_for(chrono::milliseconds(100));
    }
}
void consumer(Queue *que)
{
    for (int i = 0; i < 1000; ++i)
    {
        que->get();
        // this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main()
{
    Queue que; // 两个线程共享的队列

    thread t1(producer, &que);
    thread t2(consumer, &que);

    t1.join();
    t2.join();

    return 0;
}