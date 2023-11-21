#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>

int main() {
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        std::cerr << "Failed to create epoll instance." << std::endl;
        return 1;
    }

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1) {
        std::cerr << "Failed to add file descriptor to epoll." << std::endl;
        return 1;
    }

    const int max_events = 10;
    struct epoll_event events[max_events];

    while (true) {
        int num_events = epoll_wait(epoll_fd, events, max_events, -1);
        if (num_events == -1) {
            std::cerr << "Failed to wait for events." << std::endl;
            return 1;
        }

        for (int i = 0; i < num_events; ++i) {
            if (events[i].data.fd == STDIN_FILENO) {
                // Standard input is ready for reading
                std::string input;
                std::getline(std::cin, input);

                // Process the input
                std::cout << "Received input: " << input << std::endl;
            }
        }
    }

    close(epoll_fd);

    return 0;
}
