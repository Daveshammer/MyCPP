#include <iostream>

int a = 1;
namespace MyNameSpace
{
	int a = 2;
	void f() { std::cout << "MyNameSpace" << std::endl; };
	namespace A
	{
		int a = 3;
		void f() { std::cout << "A" << std::endl; }
	}
}

int main()
{
	using namespace MyNameSpace::A;
	using MyNameSpace::a;
	std::cout << a << std::endl;
	f();
}
