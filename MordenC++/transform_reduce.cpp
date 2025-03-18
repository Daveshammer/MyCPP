#include <thread>
#include <vector>
#include <array>
#include <iostream>

// 1. transform_reduce
template <typename Iter, typename UnaryOp, typename BinaryOp, typename Result>
void transform_reduce1(Iter first, Iter last, UnaryOp transform, BinaryOp reduce, Result &res)
{
    for (auto it = first; it < last; it ++)
        res = reduce(res, transform(*it));
}

// 2. devid-conquer(os can not handle too many threads)
template <typename Iter, typename UnaryOp, typename BinaryOp, typename Result, std::size_t MinDist = 10>
void transform_reduce2(Iter first, Iter last, UnaryOp transform, BinaryOp reduce, Result &res)
{
    std::size_t distance = std::distance(first, last);
    if (distance == 1)
        res = reduce(res, transform(*first));
    else
    {
        std::size_t half = distance / 2;
        Iter middle = first + half;

        Result r_result = 0;
        Result l_result = 0;

        std::thread l_thread(transform_reduce2<Iter, UnaryOp, BinaryOp, Result>, first, middle, transform, reduce, std::ref(l_result));
        std::thread r_thread(transform_reduce2<Iter, UnaryOp, BinaryOp, Result>, middle, last, transform, reduce, std::ref(r_result));

        l_thread.join();
        r_thread.join();
        res = reduce(res, reduce(l_result, r_result));
    }
}

// 3. limit the threads(distance)
template <typename Iter, typename UnaryOp, typename BinaryOp, typename Result, std::size_t MinDist = 10000000>
void transform_reduce3(Iter first, Iter last, UnaryOp transform, BinaryOp reduce, Result &res)
{
    std::size_t distance = std::distance(first, last);
    if (distance <= MinDist) { // 如果任务足够小，则直接处理
        for (auto it = first; it < last; ++it)
            res = reduce(res, transform(*it));
    } else {
        std::size_t half = distance / 2;
        Iter middle = first + half;

        Result l_result = 0;
        Result r_result = 0;

        std::thread l_thread(transform_reduce3<Iter, UnaryOp, BinaryOp, Result>, first, middle, transform, reduce, std::ref(l_result));
        transform_reduce3(middle, last, transform, reduce, r_result); // 当前线程也处理一半的任务

        l_thread.join();

        res = reduce(res, reduce(l_result, r_result));
    }
}

int main()
{
    const int N = 100000000;
    std::vector<double> numbers;
    numbers.reserve(N);

    for (int i = 0; i < N; i ++)
        numbers.push_back((double)i / N);

    auto transform = [](double x) {return x * x;};
    auto reduce = [](double a, double b) {return a + b;};

    const int N_Thread = 2;
    std::vector<std::thread> workers;
    std::array<double, N_Thread> subResult{0};

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N_Thread; i ++)
    {
        auto low = numbers.begin() + i * numbers.size() / N_Thread;
        auto high = numbers.begin() + (i + 1) * numbers.size() / N_Thread;

        workers.push_back(
            std::thread(
                transform_reduce3<std::vector<double>::iterator,
                decltype(transform),
                decltype(reduce), double>,
                low, high, transform, reduce, std::ref(subResult[i])
            )
        );
    }

    double result = 0;
    for (int i = 0; i < N_Thread; i ++)
    {
        workers[i].join();
        result = reduce(result, subResult[i]);
    }
    std::cout << result << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;

}