#include <iostream>
using namespace std;

/*
C++中的类型转换:
int a = (int) b;
const_cast; 去掉const属性的类型转换
static_cast; 提供编译器认为安全的类型转换，可以用于基类和派生类之间的转换  使用最多
reinterpret_cast; 类似与C风格的强制类型转换
dynamic_cast; 主要用于继承机构中，可以支持RTTI类型识别的上下转换
*/

class Base
{
public:
    virtual void func() = 0;
};
class Derive1 : public Base
{
public:
    virtual void func() { cout << "Derive1::func()" << endl; }
};
class Derive2 : public Base
{
public:
    virtual void func() { cout << "Derive2::func()" << endl; }
    void derive02Func() { cout << "Derive2::derive02Func()" << endl; }
};
void showFunc(Base *p)
{
    /*
    dynamic_cast会检查p指针是否指向Derive2类型的对象
    通过p->vfptr->vftable RTTI信息，判断p指针是否指向Derive2类型的对象
    如果是，转换成功，否则返回nullptr
    */
    Derive2 *pd2 = dynamic_cast<Derive2 *>(p);

    // static_cast是编译时期的类型转换
    // Derive2 *pd2 = static_cast<Derive2 *>(p); // 全部调用derive02Func()

    if (pd2 != nullptr)
    {
        pd2->derive02Func();
    }
    else 
    {
        p->func();
    }
}

int main()
{
    const int a = 10;
    double *p1 = (double *)&a; // 可以编译，但不安全

    int *p2 = const_cast<int *>(&a); // 只能转成类型一致的
    int b = const_cast<int&>(a); // const_cast<这里必须是指针或者引用类型>

    int *p = nullptr;
    // double *p3 = static_cast<double *>(p); // 从类型‘int*’到类型‘double*’中的 static_cast 无效

    Derive1 d1;
    Derive2 d2;
    showFunc(&d1);
    showFunc(&d2);

    return 0;
}