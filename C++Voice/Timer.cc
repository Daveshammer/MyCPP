#include <sys/epoll.h>
#include <functional>
#include <chrono>
#include <set>
#include <memory>
#include <iostream>

using namespace std;

struct TimerNodeBase // 定时器节点基类，用于红黑树中的比较
{
    time_t expire; // 过期时间
    int64_t id;
};

struct TimerNode : public TimerNodeBase
{
    using Callback = function<void(const TimerNode &)>;
    Callback callback;
};

// 基类引用指向派生类对象
bool operator<(const TimerNodeBase &lhs ,const TimerNodeBase &rhs) // 使用了红黑树，重载小于号
{
    if (lhs.expire < rhs.expire)
        return true;
    if (lhs.expire == rhs.expire && lhs.id < rhs.id)
        return true;
    return false;
}

class Timer
{
public:
    static time_t GetTick()
    {
        auto sc = chrono::time_point_cast<chrono::milliseconds>(chrono::steady_clock::now()); // 获取当前时间
        auto temp = chrono::duration_cast<chrono::milliseconds>(sc.time_since_epoch());       // 从系统启动到现在的毫秒数
        return temp.count();
    }

    static int64_t GenID() { return ++gid; }

    TimerNodeBase AddTimer(time_t msec, TimerNode::Callback callback)
    {
        TimerNode node;
        node.expire = GetTick() + msec; // 设置过期时间
        node.callback = callback;       // 设置回调函数
        node.id = GenID();              // 设置定时器id
        timer_set.insert(node); // 加入到红黑树中
        return static_cast<TimerNodeBase>(node); // 返回TimerNodeBase以便后续删除操作
    }

    bool DelTimer(TimerNodeBase node)
    {
        auto iter = timer_set.find(node);
        if (iter != timer_set.end())
        {
            timer_set.erase(iter);
            return true;
        }
        return false;
    }

    bool CheckTimer()
    {
        auto iter = timer_set.begin();
        if (iter != timer_set.end() && iter->expire <= GetTick())
        {
            iter->callback(*iter);
            timer_set.erase(iter);
            return true;
        }
        return false;
    }

    time_t TimeToSleep()
    {
        auto iter = timer_set.begin(); // 先找到某个数据结构中的最小的过期时间
        if (iter == timer_set.end()) // 没有任何定时任务
            return -1;
        time_t duration = iter->expire - GetTick();
        
        return duration > 0 ? duration : 0;
    }

private:
    static int64_t gid;
    set<TimerNode, std::less<>> timer_set;
};
int64_t Timer::gid = 0;

int main()
{
    int epfd = epoll_create(1);

    unique_ptr<Timer> timer = make_unique<Timer>();

    int i = 0;
    timer->AddTimer(1000, [&](const TimerNode &node) {
        cout << Timer::GetTick() << "node id:" << node.id << endl << " revoked times:" << ++ i << endl;
    });

    auto node = timer->AddTimer(1000, [&](const TimerNode &node) {
        cout << Timer::GetTick() << "node id:" << node.id << endl << " revoked times:" << ++ i << endl;
    });
    timer->DelTimer(node); // 删除id为2的定时器
      
    timer->AddTimer(3000, [&](const TimerNode &node) {
        cout << Timer::GetTick() << "node id:" << node.id << endl << " revoked times:" << ++ i << endl;
    });

    cout << "now time:" << Timer::GetTick() << endl;  

    epoll_event ev[64] = {0};
    while (true)
    {
        /*
            -1 没有事件永久阻塞
            0 没有事件发生立即返回，有事件就拷贝到ev数组中
            >0 等待指定的毫秒数
        */
        int n = epoll_wait(epfd, ev, 64, timer->TimeToSleep());
        for (int i = 0; i < n; i++)
        {
        }

        while (timer->CheckTimer()); //处理定时任务
    }
}