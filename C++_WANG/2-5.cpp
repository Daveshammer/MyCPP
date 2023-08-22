#include <iostream>
using namespace std;

class MBTXPARENT
{
public:
    MBTXPARENT()
    {
        cout << "MBTXPARENT::MBTXPARENT()" << endl;
    }
};
class MBTX //: MBTXPARENT
{
public:
    int m_i;
    int m_j;
    // MATX m_a;
    void funcj()
    {
        cout << "IAmVeryGood" << endl;
    }

    virtual void mvirfunc()
    {
        cout << "mvirfunc()" << endl;
    }
};

int main()
{
    // “合成默认的构造函数”，只有在必要的时候，编译器才会为我们合成出来，而不是必然或者必须为我们合成出来。
    // 该类MBTX没有任何构造函数，但包含一个类类型（MATX）的成员变量m_a，所以编译器会为我们合成出一个默认的构造函数。
    MBTX mby;

    // 构造函数语义续
    // 父类带缺省构造函数，子类没有任何构造函数，那因为父类这个缺省的构造函数要被调用，所以编译器会为这个子类合成出一个默认的构造函数

    // 如果一个类含有虚函数，但没有任何构造函数时
    // a)编译器会给我们生成一个基于该类的虚函数表vftable
    // b)把类的虚函数地址赋给类对象的虚函数表指针

	return 0;
}