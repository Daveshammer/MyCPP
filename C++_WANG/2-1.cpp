#include <iostream>
using namespace std;

class A
{
public:
	void func()  {}; // 成员函数
	void func1() {};
	void func2() {};

	char ab; // 成员变量
	int cd;
};

int main()
{
	A obja;
	int ilen = sizeof(obja);
	cout << "sizeof(obja) = " << ilen << endl; // sizeof(a) = 1，因为有内存地址，所以不会为0

	// (1)类的成员函数 不占用 类对象的内存空间
	// (2)一个类对象至少占用一个字节的内存空间
	obja.ab = 'a'; 
	// (3)成员变量占用对象的内存空间
	obja.cd = 12;

	// 结论：成员变量是包含在每个对象中的，是占用对象字节的
	// 而成员函数不占用对象字节数（内存空间）

	return 0;
}