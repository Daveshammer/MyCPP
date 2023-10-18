#include <iostream>
#include <sys/eventfd.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <thread>
#include <assert.h>

using namespace std;

void threadFunc(int eventFd)
{
    sleep(5); //模拟函数执行时间
    uint64_t buf = 999;
    ssize_t n = write(eventFd,&buf,sizeof buf);

    if(n!=sizeof buf)
    {
        cout<<"write "<<n<<" bytes instead of 8"<<endl;
        exit(-1);
    }
}

int main()
{
    int eventFd = eventfd(0,EFD_NONBLOCK | EFD_CLOEXEC);
    cout<<"eventFd : "<<eventFd<<endl;
    
    int epfd = epoll_create(1);
    struct epoll_event events[5];

    {
        struct epoll_event event;
        event.data.fd = eventFd;
        event.events = EPOLLIN;
        epoll_ctl(epfd,EPOLL_CTL_ADD,eventFd,&event);
    }

    std::thread t(threadFunc,eventFd);

    while(true)
    {
        int numEvents = epoll_wait(epfd,events,5,1000);
        if(numEvents == 0)
        {
            cout<<"timeout"<<endl;
            continue;
        }
        assert(numEvents == 1);
        assert(events[0].data.fd == eventFd);
        uint64_t buf = 0;
        unsigned long n = read(eventFd,&buf,sizeof buf);
        if(n!=sizeof buf)
        {
            cout<<"read "<<n<<" bytes instead of 8"<<endl;
            exit(-1);
        }
        else
        {
            cout<<"read "<<n<<" bytes "<<buf<<endl;
        }
        break;
    }

    t.join();
    close(eventFd);

    cout<<"finished"<<endl;

    return 0;
}