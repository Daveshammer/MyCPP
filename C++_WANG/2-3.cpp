#include <iostream>
using namespace std;

class A
{
public:
	int a; 
	A()
	{
		printf("A::A()的this指针是：%p\n", this);
	}
	void funcA()
	{
		printf("A::funcA()的this指针是：%p\n", this);
	}
};

class B
{
public:
	int b;
	B()
	{
		printf("B::B()的this指针是：%p\n", this);
	}
	void funcB()
	{
		printf("B::funcB()的this指针是：%p\n", this);
	}
};

class C : public A, public B
{
public:
	int c;
	C()
	{
		printf("C::C()的this指针是：%p\n", this);
	}
	void funcC()
	{
		printf("C::funcC()的this指针是：%p\n", this);
	}
    void funcB()
	{
		printf("C::funcB()的this指针是：%p\n", this);
	}

};

int main()
{
	//this指针调整：多重继承
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
    cout << sizeof(C) << endl;

    C myc;
    myc.funcA();
    myc.funcB(); // 被子类C覆盖
    myc.B::funcB();
    myc.funcC();

    // 派生类对象包含对各基类，和第一个基类子对象的开始地址相同

    // 总结：调用哪个子类的成员函数，这个this指针就会被编译器自动调整到对象内存布局中 对应子类对象的起始地址那去

	return 0;
}