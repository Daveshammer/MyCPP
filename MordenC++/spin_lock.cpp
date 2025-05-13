#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>
#include <mutex>
#include <chrono>
#include <immintrin.h>

class spinlock_atomic_flag {
public:
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {}
    }
    
    void unlock() {
        flag.clear(std::memory_order_release);
    }
private:
    std::atomic_flag flag{ATOMIC_FLAG_INIT};
};

class spinlock_atomic {
public:
    void lock() {
        while (lock_flag.exchange(true, std::memory_order_acquire)) {}
    }

    void unlock() {
        lock_flag.store(false, std::memory_order_release);
    }
private:
    std::atomic<bool> lock_flag{false};  // 锁的状态：true 表示已占用，false 表示未占用
};

/*
普通自旋锁面对的两大问题：

1. busy-waiting带来的资源浪费：
自旋锁在等待锁的过程中会不断地检查锁的状态，这种忙等待（busy-waiting）会导致 CPU 资源的浪费。
应该使用_mm_pause() 或 std::this_thread::yield() 是一些优化方式，用于告诉 CPU 或操作系统，
让其他线程优先运行。这些方法可以减少忙等待（busy-waiting）导致的资源浪费。

2. 自旋锁引发的缓存争夺：
如果多个核心频繁争夺一个自旋锁，它们会不断地修改锁变量，每次修改都会触发 MESI 协议，使得所有其他核心的缓存变成无效（Invalid）。
这样就导致大量的协调工作，所有核心都在不断尝试获取锁，同时不断地让其他核心的缓存失效。
由于缓存失效，数据必须从主存重新加载，或者从其他核心传输过来，这种数据传输会极大地影响性能。

通过在尝试更改内存之前加载内存来解决第二个问题。在 MESI 协议中，这意味着缓存行可以在所有内核上处于“共享”状态。
在数据实际更改之前，不需要 CPU 内核之间的通信。
*/

class spinlock_amd
{
public:
    void lock()
    {
        for (;;)
        {
            bool was_locked = locked.load(std::memory_order_relaxed);
            if (!was_locked && locked.compare_exchange_weak(was_locked, true, std::memory_order_acquire))
                break;
            _mm_pause();
        }
    }
    void unlock()
    {
        locked.store(false, std::memory_order_release);
    }
 
private:
    std::atomic_bool locked{false};
};

class spinlock
{
public:
    void lock()
    {
        for (int spin_count = 0; !try_lock(); ++spin_count)
        {
            if (spin_count < 16)
                _mm_pause();
            else
            {
                std::this_thread::yield();
                spin_count = 0;
            }
        }
    }
    bool try_lock()
    {
        return !locked.load(std::memory_order_relaxed) && !locked.exchange(true, std::memory_order_acquire);
    }
    void unlock()
    {
        locked.store(false, std::memory_order_release);
    }
 
private:
    std::atomic<bool> locked{false};
};

class ticket_spinlock
{
public:
    void lock()
    {
        unsigned my = in.fetch_add(1, std::memory_order_relaxed);
        for (int spin_count = 0; out.load(std::memory_order_acquire) != my; ++spin_count)
        {
            if (spin_count < 16)
                _mm_pause();
            else
            {
                std::this_thread::yield();
                spin_count = 0;
            }
        }
    }
    void unlock()
    {
        out.store(out.load(std::memory_order_relaxed) + 1, std::memory_order_release);
    }
 
private:
    std::atomic<unsigned> in{0};
    std::atomic<unsigned> out{0};
};

void test1()
{
    spinlock_amd spin;
    int count = 0;
    
    auto inc = [&]() {
        for (int i = 0; i < 1000; ++i) {
            std::lock_guard<spinlock_amd> lock(spin);
            ++count;
        }
    };
    
    std::thread t1(inc);
    std::thread t2(inc);
    
    t1.join();
    t2.join();
    std::cout << "Count: " << count << std::endl;
}

// spinlock_atomic_flag mutex;
// spinlock_atomic mutex;
// spinlock_amd mutex;
// spinlock mutex;
ticket_spinlock mutex;
// std::mutex mutex;
int num = 0;
void threadFunc(size_t num_loops) {
    for (size_t i = 0; i < num_loops; ++i) {
        mutex.lock();
        num ++;
        mutex.unlock();
    }
}

void testSpinLockPerformance(size_t numThreads, size_t numLoopsPerThread) {
    std::vector<std::thread> threads;

    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(threadFunc, numLoopsPerThread);
    }

    for (auto& t : threads) {
        t.join();
    }
}

int main() {
    size_t numThreads = 2;
    size_t numLoopsPerThread = 100000; // 每个线程的循环次数

    auto start = std::chrono::high_resolution_clock::now();
    testSpinLockPerformance(numThreads, numLoopsPerThread);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    std::cout << "Final value of num: " << num << std::endl;
    return 0;
}