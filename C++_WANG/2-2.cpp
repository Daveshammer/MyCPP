#include <iostream>
using namespace std;

class A
{
public:
	int a; // 非静态成员变量 占用4个字节，若为64位系统导致内存对齐占用8个字节
	static int b; //静态成员变量跟着类走

	static void sfunc() {}; // 静态成员函数
	void myfunc() {}; // 普通成员函数

	virtual void myfunc3() {};
	virtual void myfunc4() {};
	virtual void myfunc5() {};
};

int main()
{
	// (1)非静态的成员变量跟着对象走（存在对象内部），也就是每个类对象都有自己的成员变量
	A obja;
	int ilen = sizeof(obja);
	cout << "sizeof(obja) = " << ilen << endl; // 16 = int a(4) + 内存对齐(4) + vptr(8)

	// (2)静态成员变量保存在对象外面
	// (3)成员函数：静态/非静态都保存在类对象之外
	// (4)虚函数：不管几个虚函数，sizeof()都会多8字节
	// (4.1)类里只要有一（多）个虚函数，这个类会产生一（多）个指向虚函数的指针
	// 类本身 指向虚函数的指针（一个或者一堆），存放在虚函数表vtbl中
	// (4.2)因为有了虚函数，导致系统往类对象中添加了一个指针vptr，指向虚函数表

	// 总结类对象大小的组成：
	// (1)非静态成员变量所占的内存总量以及这些成员变量之间字节对齐额外占用的内存
	// (2)若有虚函数，则会产生虚函数表指针vptr


	return 0;
}