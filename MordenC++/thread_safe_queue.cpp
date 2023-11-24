#include<vector>
#include<iostream>
#include<thread>


#include "thread_safe_queue_v5.h"

void test_multi_producer()
{
    ThreadSafeQueue<std::vector<int>> mq;
    ThreadSafeQueue<int> print_mq;
    std::thread producer([&]
                         {
                             for (int i = 0; i < 1500000; i++)
                             {
                                 mq.Push(std::vector<int>{3,23,323,432,4324,32432,4324,3532,532532,5325,32532,5325,325234,23432,4324,23432,324,32432,4324,32432,4324,324324,3423,4324});
                             }
                         });

    std::thread t1([&]()
                   {

                       for (int i = 0; i < 500000; i++)
                       {
                           auto ptr = mq.WaitAndPop();
                           print_mq.Push(ptr->front());
                       }
                   });
    std::thread t2(
            [&]()
            {
                for (int i = 0; i < 500000; i++)
                {
                auto ptr =    mq.WaitAndPop();
                    print_mq.Push(ptr->front());
                }
            }
    );
    std::thread t3(
            [&]()
            {
                int x;
                for (int i = 0; i < 50000; i++)
                {
                    auto ptr = mq.WaitAndPop();
                    print_mq.Push(ptr->front());
                }
            }
    );
    std::thread t4(
            [&]
            {
                int x;
                for (int i = 0; i < 200000; i++)
                {
                    print_mq.WaitAndPop(x);
                    std::cout << x << "\n";
                }
            }
    );
    producer.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

void test_one_producer()
{
    ThreadSafeQueue<int> mq;
    ThreadSafeQueue<int> print_mq;

    std::thread producer(
            [&]
            {
                for (int i = 0; i < 15000; i++)
                {
                    mq.Push(i);
                }
            });

    std::thread t1([&]()
                   {
                       int x;
                       for (int i = 0; i < 5000; i++)
                       {
                           mq.WaitAndPop(x);
                           std::cout << x << "\n";
                       }
                   });
    std::thread t2(
            [&]()
            {
                int x;
                for (int i = 0; i < 5000; i++)
                {
                    mq.WaitAndPop(x);
                    std::cout << x << "\n";
                }
            }
    );
    std::thread t3(
            [&]()
            {
                int x;
                for (int i = 0; i < 5000; i++)
                {
                    mq.WaitAndPop(x);
                    std::cout << x << "\n";
                }
            }
    );

    producer.join();
    t1.join();
    t2.join();
    t3.join();
}

int main()
{
    freopen("../../test_source/thread_output_text", "w", stdout);
    test_multi_producer();
    // test_one_producer();
}