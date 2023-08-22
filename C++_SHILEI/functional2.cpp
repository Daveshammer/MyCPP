#include <iostream>
#include <typeinfo>
#include <string>
#include <functional>
using namespace std;

void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }

template<typename Fty>
class myfunction {};

#if 1
template<typename R, typename A1>
class myfunction<R(A1)>
{
public:
    using PFUNC = R(*)(A1);
    myfunction(PFUNC pfunc)
        : _pfunc(pfunc)
    {
    }
    R operator()(A1 arg)
    {
        return _pfunc(arg);
    }
private:
    PFUNC _pfunc;
};
template<typename R, typename A1, typename A2>
class myfunction<R(A1, A2)>
{
public:
    using PFUNC = R(*)(A1, A2);
    myfunction(PFUNC pfunc)
        : _pfunc(pfunc)
    {
    }
    R operator()(A1 arg1, A2 arg2)
    {
        return _pfunc(arg1, arg2);
    }
private:
    PFUNC _pfunc;
};
#endif

#if 0
template<typename R, typename... A>
class myfunction<R(A...)>
{
public:
    using PFUNC = R(*)(A...);
    myfunction(PFUNC pfunc)
        : _pfunc(pfunc)
    {
    }
    R operator()(A... arg)
    {
        return _pfunc(arg...);
    }
private:
    PFUNC _pfunc;
};
#endif

int main()
{
    myfunction<void(string)> func1 = hello;
    func1("hello"); // func.operator() => hello("hello")

    myfunction<int(int, int)> func2 = sum;
    cout << func2(20, 30) << endl;

    return 0;
}