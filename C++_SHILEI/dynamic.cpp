#include <iostream>
using namespace std;

/*
虚函数和动态绑定 问题：是不是虚函数的调用一定就是动态绑定？ 不是
在类的构造函数当中，调用虚函数，也是静态绑定（构造函数中调用其它虚函数，不会发生动态绑定）
*/

class Base
{
public:
    Base(int data = 10) : ma(data) { cout << "Base()" << endl; }
    virtual ~Base() { cout << "~Base()" << endl; }

    virtual void show() { cout << "Base::show()" << endl; }
    // virtual void show(int data) { cout << "Base::show(int data)" << endl; }

protected:
    int ma;
};
class Derive : public Base
{
public:
    Derive(int data = 20) : Base(data), mb(data) { cout << "Derive()" << endl; }
    ~Derive() { cout << "~Derive()" << endl; }
    void show() { cout << "Derive::show()" << endl; }

private:
    int mb;
};

int main()
{
    Base b;
    Derive d;

    // 用对象本身调用虚函数，是静态绑定
    b.show(); // call Base::show()
    d.show(); // call Derive::show()

    // 用指针调用虚函数，是动态绑定
    Base *pb1 = &b;
    Base *pb2 = &d;
    pb1->show(); 
    pb2->show(); 

    // 用引用调用虚函数，是动态绑定
    Base &rb1 = b;
    Base &rb2 = d;
    rb1.show();
    rb2.show();

    // 派生类指针指向基类对象，调用虚函数，是动态绑定
    Derive *pd2 = (Derive *)&b;
    pd2->show(); // Base::show()

    return 0;
}