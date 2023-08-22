#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
函数对象的缺点：
使用在泛型算法参数传递    比较性质/自定义操作    优先级队列    智能指针

lambda表达式的语法：
[捕获列表](参数列表) -> 返回值类型 {函数体}

如果lambda表达式没有返回值，那么返回值类型可以省略

[捕获外部变量]
[]: 不捕获任何变量
[&]: 按引用捕获外部所有变量
[=]: 按值捕获外部所有变量
[this]：捕获外部的this指针
[=, &a]: 按值捕获外部所有变量，但是a按引用捕获
[a, b]：按值捕获a和b，但是如果外部没有定义a和b，编译器会报错
[&a, &b]：按引用捕获a和b，但是如果外部没有定义a和b，编译器会报错
[=, &a, &b]：按值捕获外部所有变量，但是a和b按引用捕获
[&, a, b]：按引用捕获外部所有变量，但是a和b按值捕获
[=, &a, b]：按值捕获外部所有变量，但是a按引用捕获，b按值捕获
[&, a, &b]：按引用捕获外部所有变量，但是a按值捕获，b按引用捕获
*/

template <typename T = void>
class TestLambda01
{
public:
    void operator()()
    {
        cout << "hello2" << endl;
    }
};
template <typename T = int>
class TestLambda02
{
public:
    int operator()(int a, int b)
    {
        return a + b;
    }
};
template <typename T = int>
class TestLambda03
{
public:
    TestLambda03(int &a, int &b) : ma(a), mb(b) {}
    void operator()() const
    {
        int tmp = ma;
        ma = mb;
        mb = tmp;
    }

private:
    int &ma;
    int &mb;
};

int main()
{
    auto func1 = []()
    { cout << "hello1" << endl; };
    func1(); // hello1
    // 和上面等价
    TestLambda01<> t1;
    t1(); // t1.operator()()

    auto func2 = [](int a, int b) -> int
    { return a + b; };
    cout << func2(10, 20) << endl; // 30
    // 和上面等价
    TestLambda02<> t2;
    cout << t2(10, 20) << endl; // 30

    int a = 10;
    int b = 20;
    auto func3 = [&a, &b]()
    {
        int tmp = a;
        a = b;
        b = tmp;
    };
    func3();
    cout << a << " " << b << endl; // 20 10
    // 和上面等价
    TestLambda03<> t3(a, b);
    t3();
    cout << a << " " << b << endl; // 10 20

    cout << "------------------------" << endl;

    vector<int> vec;
    for (int i = 0; i < 10; i++)
    {
        vec.push_back(rand() % 100 + 1);
    }
    sort(vec.begin(), vec.end(), [](int a, int b) -> bool
         { return a < b; });
    for (auto &val : vec)
        cout << val << " ";
    cout << endl;
    // 65按序插入序列 要找第一个大于65的数
    auto it = find_if(vec.begin(), vec.end(), [](int a) -> bool
                      { return a > 65; });
    if (it != vec.end())
    {
        vec.insert(it, 65);
    }
    for (auto &val : vec)
        cout << val << " ";
    cout << endl;

    for_each(vec.begin(), vec.end(), [](int &a)
             { if (a % 2 == 0) cout << a << " "; });
    cout << endl;

    return 0;
}