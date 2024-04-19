#include <iostream>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>
typedef std::function<void()> FP;

// this 捕获陷阱

class Point
{
public:
    Point(int x, int y) : m_x(x), m_y(y)
    {
    }
    void print1()
    {
        // 在lambda里使用m_x,相当于this->m_x。在this销毁后在调用这个lambda，这时候的this就不知指到哪里了。
        s_print_history.push_back([=]()
                                  { std::cout << "(X:" << m_x << ",Y:" << m_y << ")" << std::endl; });
        std::cout << "(X:" << m_x << ",Y:" << m_y << ")" << std::endl;
    }
    void print()
    {
        int x = m_x;
        int y = m_y;
        // 这时，会把x，y通过传值捕获，lambda里没有保存this指针信息，避免隐藏this的影响。
        s_print_history.push_back([x, y]()
                                  { std::cout << "(X:" << x << ",Y:" << y << ")" << std::endl; });
        std::cout << "(X:" << m_x << ",Y:" << m_y << ")" << std::endl;
    }

    static void print_history()
    {
        std::for_each(s_print_history.begin(), s_print_history.end(), [](FP p)
                      {
            if(p)
                p(); });
    }

private:
    int m_x;
    int m_y;
    typedef std::function<void(void)> FP;
    static std::vector<FP> s_print_history;
};
std::vector<FP> Point::s_print_history = std::vector<FP>();

int main()
{
    std::unique_ptr<Point> p;
    p.reset(new Point(1, 1));
    p->print();
    p.reset(new Point(2, 2));
    p->print();
    p.reset(new Point(3, 3));
    p->print();
    Point::print_history();
    return 0;
}
