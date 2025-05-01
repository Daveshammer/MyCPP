#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>
#include <mutex>

class SpinLock_atomic_flag {
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

class SpinLock_atomic {
private:
    std::atomic<bool> lock_flag;  // 锁的状态：true 表示已占用，false 表示未占用

public:
    SpinLock_atomic() : lock_flag(false) {}  // 初始化为未占用

    SpinLock_atomic(const SpinLock_atomic&) = delete;
    SpinLock_atomic& operator=(const SpinLock_atomic&) = delete;

    // 加锁
    void lock() {
        while (lock_flag.exchange(true, std::memory_order_acquire)) {
            // 忙等待：如果锁已被占用，则不断检查
            // 可以插入 PAUSE 指令来优化性能（可选）
            __asm__ volatile("pause" ::: "memory");
        }
    }

    // 解锁
    void unlock() {
        lock_flag.store(false, std::memory_order_release);  // 释放锁
    }
};

int main(void)
{
    SpinLock_atomic_flag spin;
    int count = 0;
    
    auto inc = [&]() {
        for (int i = 0; i < 1000; ++i) {
            std::lock_guard<SpinLock_atomic_flag> lock(spin);
            ++count;
        }
    };
    
    std::thread t1(inc);
    std::thread t2(inc);
    
    t1.join();
    t2.join();
    std::cout << "Count: " << count << std::endl;
}