#include <iostream>
#include <typeinfo>
using namespace std;

/*
问题一：哪些函数不能实现成虚函数

虚函数依赖：
1.虚函数能产生地址，存储在vftable当中
2.对象必须存在（vfptr -> vftable -> 虚函数地址）

构造函数
1.virtual + 构造函数 NO!
2.构造函数中（调用的任何函数，都是静态绑定的）调用虚函数，也不会发生静态绑定
派生类对象构造过程 1.先调用的是基类的构造函数 2.再调用的是派生类的构造函数

static静态方法 NO! 

问题二：虚析构函数 析构函数调用的时候，对象是存在的
什么时候把基类的析构函数必须是现成虚函数？
基类的指针（引用）指向堆上new出来的派生类对象的时候，delete pb(基类的指针)，
它调用析构函数的时候，必须发生动态绑定，否则会导致派生类的析构函数不会被调用
*/

class Base
{
public:
    Base(int data = 10) : ma(data) { cout << "Base()" << endl; }
    virtual ~Base() { cout << "~Base()" << endl; }

    virtual void show() { cout << "Base::show()" << endl; }
    virtual void show(int data) { cout << "Base::show(int data)" << endl; }

protected:
    int ma;
private:
};
class Derive : public Base
{
public:
    Derive(int data = 20) : Base(data), mb(data) { cout << "Derive()" << endl; }
    ~Derive() { cout << "~Derive()" << endl; }

protected:
private:
    int mb;
};

int main()
{
    Base *pb = new Derive(10);
    pb->show(); // Derive::show()
    /*
    如果没有将基类的虚构函数声明为虚函数，那么delete，只会调用基类的析构函数
    pb->Base Base::~Base 对于析构函数的调用，是静态绑定的
    call Base::~Base
    */
    delete pb;

    return 0;
}