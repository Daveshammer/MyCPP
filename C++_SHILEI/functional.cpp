#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <ctime>
#include <string>
using namespace std;

void hello1()
{
    cout << "hello1" << endl;
}
void hello2(string str)
{
    cout << str << endl;
}
int sum(int a, int b)
{
    return a + b;
}
class Test
{
public:
    void hello(string str) { cout << str << endl; }
};

int main()
{
    function<void()> func1 = hello1;
    func1(); // func.operator() => hello1()

    function<void(string)> func2 = hello2;
    func2("hello2"); // func.operator() => hello2("hello2")

    function<int(int, int)> func3 = sum;
    cout << func3(20, 30) << endl;

    function<int(int, int)> func4 = [](int a, int b) -> int { return a + b; };
    cout << func4(20, 30) << endl;

    function<void(Test*, string)> func5 = &Test::hello;
    Test t;
    func5(&t, "Test::hello");

    cout << "---------------------" << endl;

    //函数指针类型和函数类型
    typedef int(*PFUNC1)(int, int);
    PFUNC1 pfunc1 = sum;
    cout << pfunc1(10, 20) << endl;

    typedef int PFUNC2 (int, int);
    PFUNC2 *pfunc2 = sum;
    cout << pfunc2(10, 20) << endl;

    return 0;
}