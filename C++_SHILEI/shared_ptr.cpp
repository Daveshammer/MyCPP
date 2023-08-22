#include <iostream>
#include <memory>
using namespace std;

/*
shared_ptr: 可以改变资源的引用计数
weak_ptr: 不会改变资源的引用计数

强智能指针循环引用（交叉引用问题）:
造成new出来的资源无法释放，内存泄漏问题
因此要在定义对象的时候，使用强智能指针；引用对象的时候，使用弱智能指针
*/

class B;
class A
{
public:
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
    void testA()
    {
        cout << "testA()" << endl;
    }

    weak_ptr<B> m_ptrb; // shared_ptr<B> m_ptrb;
};
class B
{
public:
    B() { cout << "B()" << endl; }
    ~B() { cout << "~B()" << endl; }
    void func()
    {
        // m_ptra->testA();
        shared_ptr<A> pa = m_ptra.lock();
        if (pa != nullptr)
        {
            pa->testA();
        }
    }

    weak_ptr<A> m_ptra; // shared_ptr<A> m_ptr;
};

int main()
{
    shared_ptr<A> pa(new A);
    shared_ptr<B> pb(new B);

    pa->m_ptrb = pb; //如果都采用shared_ptr，会造成循环引用，导致内存泄漏
    pb->m_ptra = pa; //如果都采用weak_ptr，不会造成循环引用，不会导致内存泄漏
    pb->func();


    cout << pa.use_count() << endl;
    cout << pb.use_count() << endl;

    return 0;
}