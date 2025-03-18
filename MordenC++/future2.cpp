#include <iostream>
#include <future>
#include <thread>
#include <vector>

std::mutex coutMutex;

void teach(std::promise<void> && prom)
{
    std::cout << "teaching start" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "teaching end" << std::endl;
    prom.set_value();
}

void learn(std::shared_future<void> &&sf)
{
    sf.wait();
    std::lock_guard<std::mutex> coutGuard(coutMutex);
    std::cout << "learning" << std::endl;
}

int main()
{
    std::promise<void> promise;
    std::shared_future<void> sf = promise.get_future().share();

    std::thread teacher(teach, std::move(promise));
    std::vector<std::thread> students;

    for (int i = 0; i < 10; i++)
    {
        students.push_back(std::thread(learn, sf));
    }

    teacher.join();
    for (auto &student : students)
    {
        student.join();
    }
}