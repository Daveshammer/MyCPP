#include <iostream>
#include <memory>
#include <vector>

void test1()
{
    std::cout << "test1: \n";
    auto p = std::make_shared<int>(4);
    int num{10};
    auto p1 = std::shared_ptr<int>(p, &num); //p1和p共用一个控制块，但是指向不同资源

    std::cout << "p1 use_count: " << p1.use_count()
              << "\n"
              << "p1: " << *p1 << "\n"
              << "p use_count: " << p.use_count()
              << "\n"
              << "p: " << *p << "\n";
    std::cout << "------------------" << std::endl;
}

void test2()
{
    std::cout << "test2: \n";
    auto vp = std::make_shared<std::vector<int>>(4); //p指向一个vector，该vector有4个元素
    vp->push_back(1);
    vp->push_back(2);

    std::shared_ptr<int> p1(vp, &vp->at(0)); //p1和p共用一个控制块，但是指向不同资源
    std::shared_ptr<int> p2(vp, &vp->at(1)); //p2和p共用一个控制块，但是指向不同资源

    std::cout << "vp use_count: " << vp.use_count()
              << "\n";
    std::cout << "------------------" << std::endl;
}

int main()
{
    test1();

    test2();
    return 0;
}