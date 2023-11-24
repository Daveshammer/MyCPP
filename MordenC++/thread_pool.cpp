#include "thread_pool.h"
#include <iostream>

int main()
{
    ThreadPool pool;
    auto f = pool.submit([]()
                         {
                             std::cout << "task1 is finished" << std::endl;
                             return 32; });

    pool.submit([ff = f.share()]()
                { std::cout << ff.get() << std::endl; }); // 打印任务返回值
}