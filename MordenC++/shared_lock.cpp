#include <iostream>
#include <shared_mutex>
#include <thread>
#include <sstream>
#include <string>
#include <mutex>
#include <chrono>
#include <vector>
#include <iomanip>

class SharedContent
{
public:
    using high_resolution_clock = std::chrono::high_resolution_clock;
    using float_seconds = std::chrono::duration<float, std::chrono::seconds::period>;

    SharedContent() { startTime = high_resolution_clock::now(); }
    void write()
    {
        std::srand(std::time(nullptr));
        int random_number = std::rand();
        std::stringstream ss;
        ss << "rn = " << random_number << "\n";

        std::lock_guard lock(mtx);
        content = ss.str();
        print("write");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    void read()
    {
        // std::lock_guard lock(mtx); // 500ms for each read
        std::shared_lock lock(mtx);
        print("read");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
private:
    float elased_time() { return float_seconds(high_resolution_clock::now() - startTime).count(); }
    template <typename T>
    void print(T &&msg)
    {
        std::lock_guard lock(cout_mtx);
        std::cout << std::fixed << std::setprecision(2) << std::setw(7) << elased_time() << "s:[tid:" << std::this_thread::get_id() << "] " << std::setw(5) << msg << content << std::endl;
    }
private:
    // std::mutex mtx; // 500ms for each read
    std::shared_mutex mtx;
    std::string content = "no data\n";
    std::mutex cout_mtx;
    high_resolution_clock::time_point startTime;
};

int main()
{
    SharedContent content;
    auto read = [&content] {
        for (int i = 0; i < 1000; i++)
        {
            content.read();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    };

    auto write = [&content] {
        for (int i = 0; i < 1000; i++)
        {
            content.write();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    };

    std::thread w_th(write);
    std::vector<std::thread> r_threads;
    for (int i = 0; i < 4; i ++) {
        r_threads.push_back(std::thread(read));
    }

    w_th.join();
    for (auto &th : r_threads) {
        th.join();
    }
}