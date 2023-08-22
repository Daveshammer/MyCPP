#include <iostream>
#include <vector>
#include <functional>
#include <ctime>

std::vector<std::function<bool(int)>> gv;

// gv[0]
void myfunc()
{
    srand((unsigned)time(NULL));

    int tmpvalue = rand() % 6;
    gv.push_back(
        [tmpvalue](int tv) { // 按引用捕获会导致悬空引用
            if (tv % tmpvalue == 0)
                return true;
            else
                return false;
        });
}

class AT
{
public:
    // gv[1]
    void addItem()
    {
        auto tmpvalueCopy = m_tmpvalue;
        gv.push_back(
            [tmpvalueCopy](auto tv) { //[=]实质上是[this]
                if (tv % tmpvalueCopy == 0)
                    return true;
                else
                    return false;
            });
    }

    // gv[2]
    void addItem1()
    {
        gv.push_back(
            [tmpvalueCopy = m_tmpvalue](auto tv) { // 广义lambda捕获
                if (tv % tmpvalueCopy == 0)
                    return true;
                else
                    return false;
            });
    }

    int m_tmpvalue = 7;
};

int main()
{
    myfunc();                            // 该函数向gv容器中添加一个函数对象
    std::cout << gv[0](10) << std::endl; // 调用容器gv中第一个元素（即上述函数对象）并传入值10作为其参数

    AT *pat = new AT();
    pat->addItem(); // 该函数向gv容器中添加一个函数对象
    pat->addItem1();
    delete pat;
    std::cout << gv[1](10) << std::endl; // 调用容器gv中第二个元素（即上述函数对象）并传入值10作为其参数
    std::cout << gv[2](10) << std::endl;

    return 0;
}