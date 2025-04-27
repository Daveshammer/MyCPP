#include <iostream>
#include <atomic>
#include <thread>
#include <syncstream>

class SpinLock {
private:
    std::atomic<bool> lock_flag;  // 锁的状态：true 表示已占用，false 表示未占用

public:
    SpinLock() : lock_flag(false) {}  // 初始化为未占用

    SpinLock(const SpinLock&) = delete;
    SpinLock& operator=(const SpinLock&) = delete;

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

// 测试代码
int shared_resource = 0;
SpinLock spinlock;

void task(int id) {
    for (int i = 0; i < 100; ++i) {
        spinlock.lock();  // 获取锁
        ++shared_resource;  // 修改共享资源
        spinlock.unlock();  // 释放锁
    }
    std::osyncstream out(std::cout) ;
    out << "Task " << id << " completed.\n";
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);

    t1.join();
    t2.join();

    std::cout << "Final value of shared_resource: " << shared_resource << "\n";
    return 0;
}