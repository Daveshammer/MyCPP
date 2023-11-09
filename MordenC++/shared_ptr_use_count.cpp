#include <iostream>
#include <memory>

using namespace std;

class Base
{
public:
    Base(int num = 0):num(num) { cout << "Base::Base()" << endl; }
    ~Base() { cout << "Base::~Base()" << endl; }
    int num;
};

void func1(shared_ptr<Base>& sp) { // 传递引用不会增加引用计数
    cout << "func1 num: " << sp->num << " count: " << sp.use_count() << endl;
    sp->num++;
}

void func2(shared_ptr<Base> sp) { // 传递引用不会增加引用计数
    cout << "func2 num: " << sp->num << " count: " << sp.use_count() << endl;
    sp->num++;
}

int main()
{
    //shared_ptr
    cout << "test shared_ptr" << endl;
    auto sp = make_shared<Base>(10);
    func1(sp); // count: 1
    func2(sp); // count: 2
    cout << "main num: " << sp->num << " count: " << sp.use_count() << endl;

    //unique_ptr
    cout << endl << "test shared_ptr" << endl;
    auto np = make_unique<Base>(10);
    func2(std::move(np)); // 通过std::move将unique_ptr传递给shared_ptr
}
