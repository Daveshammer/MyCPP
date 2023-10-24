#include <iostream>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <unistd.h>

int timer_fd = -1;

void handle_stdin()
{
    constexpr size_t len = 8192;
    char buffer[len];

    const ssize_t n = read(STDIN_FILENO, buffer, len);
    if (n > 0) 
    {
        write(STDOUT_FILENO, "Read: ", 6);
        write(STDOUT_FILENO, buffer, n);
    }
}

void handle_timer()
{
    printf("Timer expired.\n");

    uint64_t buf[1];
    const ssize_t n = read(timer_fd, buf, sizeof(buf));
    if (n < 0)
    {
        perror("read");
    }
}

void register_stdin(int epoll_fd)
{
    struct epoll_event event;
    event.events = EPOLLIN;
    // event.data.fd = STDIN_FILENO;
    event.data.ptr = reinterpret_cast<void*>(handle_stdin);

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1)
    {
        std::cerr << "Failed to add file descriptor to epoll." << std::endl;
        exit(EXIT_FAILURE);
    }
}

timespec second_to_timespec(int seconds)
{
    timespec ts;
    ts.tv_sec = seconds;
    ts.tv_nsec = 0;
    return ts;
}

void register_timer(int epoll_fd, int second)
{
    timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (timer_fd == -1)
    {
        perror("timerfd_create");
        exit(EXIT_FAILURE);
    }

    struct epoll_event event;
    event.events = EPOLLIN;
    // event.data.fd = timer_fd;
    event.data.ptr = reinterpret_cast<void*>(handle_timer);

    struct itimerspec timer;
    timer.it_interval = second_to_timespec(second);
    timer.it_value = second_to_timespec(second);

    if (timerfd_settime(timer_fd, 0, &timer, nullptr) == -1)
    {
        perror("timerfd_settime");
        exit(EXIT_FAILURE);
    }

        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, timer_fd, &event) == -1)
    {
        std::cerr << "Failed to add file descriptor to epoll." << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main()
{
    const int epoll_fd = epoll_create1(0);

    register_stdin(epoll_fd);
    register_timer(epoll_fd, 5); //过期时间为5秒

    while (true)
    {
        epoll_event events[4];
        const int n = epoll_wait(epoll_fd, events, 4, -1);

        if (n < 0)
        {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        // for (int i = 0; i < n; i ++)
        // {
        //     if (events[i].data.fd == STDIN_FILENO)
        //     {
        //         handle_stdin();
        //     }
        //     else if (events[i].data.fd == timer_fd)
        //     {
        //         handle_timer();
        //     }
        // }
        for (int i = 0; i < n; i ++)
        {
            void (*callback)(void) = reinterpret_cast<void (*)(void)>(events[i].data.ptr);
            callback();
        }
    }
}