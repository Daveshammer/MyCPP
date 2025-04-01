#include<iostream>
#include<mutex>
#include<condition_variable>
#include<thread>
#include<string>
#include<sstream>

class Channel
{
public:
    void getData()
    {
        auto tid = std::this_thread::get_id();
        std::unique_lock lck(m_mutex);
        std::cout << "receiver:" << "waiting for data " << tid << std::endl;
        m_cond.wait(lck, [this] { return !m_sharedData.empty(); });
        // m_cond.wait(lck); // deadlock, spurious wakeup
        if (m_sharedData.empty())
        {
            std::cout << "receiver:" << "no data " << tid << std::endl;
        }
        else
        {
            std::cout << "receiver:" << "data received " << m_sharedData << " " << tid << std::endl;
            m_sharedData.clear();
        }
    }

    void setData()
    {
        static int id = 1;
        std::stringstream ss;
        ss << "Hello #" << id;
        {
            std::unique_lock lck(m_mutex);
            m_sharedData = ss.str();
            std::cout << "sender:" << "data set " << m_sharedData << std::endl;
            id ++;
        }
        m_cond.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

private:
    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::string m_sharedData;
};

int main()
{
    Channel ch;
    std::thread sender(&Channel::setData, &ch);
    std::thread receiver(&Channel::getData, &ch);

    sender.join();
    receiver.join();
}