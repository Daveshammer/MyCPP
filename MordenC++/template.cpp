#include <iostream>
#include <cstring>
using namespace std;
/*模板函数*/
// 普通模板
template <class T1, class T2>
bool Compare(T1 a, T2 b)
{
    cout << "普通模板" << endl;
    return a == b;
}

// 函数模板特化
template <>
bool Compare(const char *a, const char *b)
{
    cout << "函数模板特化" << endl;
    return strcmp(a, b) == 0;
}

/*类模板*/
template <class T1, class T2>
class Test
{
public:
    Test(T1 a, T2 b) : _a(a), _b(b)
    {
        cout << "模板化" << endl;
    }

private:
    T1 _a;
    T2 _b;
};

// 模板全特化
template <>
class Test<int, int>
{
public:
    Test(int a, int b) : _a(a), _b(b)
    {
        cout << "模板全特化" << endl;
    }

private:
    int _a;
    int _b;
};

// 模板偏特化
template <class T>
class Test<int, T>
{
public:
    Test(int a, T b) : _a(a), _b(b)
    {
        cout << "模板偏特化" << endl;
    }

private:
    int _a;
    T _b;
};

int main()
{
    Compare(1, 2);
    Compare("hello", "hello");

    Test<double, double> t1(1.01, 1.01);
    Test<int, int> t2(1, 1);
    Test<int, char *> t3(1, "111");
}