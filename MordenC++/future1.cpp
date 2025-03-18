#include <iostream>
#include <future>

void compute_pi(const long num_steps, std::promise<double>&& promise)
{
    double step = 1.0 / num_steps;
    double sum = 0.0;
    for (long i = 0; i < num_steps; i++)
    {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    promise.set_value(sum * step);
}

void display(std::future<double>&& future)
{
    std::cout << "PI: " << future.get() << std::endl;
}

int main()
{
    const int N_STEPS = 100000000;
    std::thread t1;
    std::thread t2;
    {
        std::promise<double> promise;
        std::future<double> future = promise.get_future();
        t1 = std::thread(compute_pi, N_STEPS, std::move(promise));
        t2 = std::thread(display, std::move(future));
    }
    t1.join();
    t2.join();
}