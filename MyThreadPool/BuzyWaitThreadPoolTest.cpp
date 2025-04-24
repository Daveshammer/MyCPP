
#include<future>
#include<iostream>
#include "BuzyWaitThreadPool.hpp"


int main()
{
    util::ThreadPool pool;
    auto f = pool.submit([]()
                         {
                             std::cout << "fdsafdsaf";
                             return 32;
                         });

    pool.submit([ff = f.share()]()
                {
                    std::cout << ff.get();
                });
}