#include <iostream>
#include <cstring>
#include <typeinfo>
using namespace std;

#if 1
template <typename T>
void func(T a)
{
    cout << "func:" << endl;
    cout << typeid(T).name() << endl;
}
int sum(int a, int b)
{
    return a + b;
}

template <typename R, typename A1, typename A2>
void func2(R (*pfunc)(A1, A2))
{
    cout << "func2:" << endl;
    cout << typeid(R).name() << endl;
    cout << typeid(A1).name() << endl;
    cout << typeid(A2).name() << endl;
}
template<typename R, typename T, typename A1, typename A2>  
void func3(R(T::*pfunc)(A1, A2))
{
    cout << "func3:" << endl;
    cout << typeid(R).name() << endl;
    cout << typeid(T).name() << endl;
    cout << typeid(A1).name() << endl;
    cout << typeid(A2).name() << endl;
}

class Test
{
public:
    int sum(int a, int b)
    {
        return a + b;
    }
};

int main()
{
    func(10);
    func("aaaa");
    func(sum);
    func2(sum);
    func3(&Test::sum);

    return 0;
}
#endif

#if 0
template<typename T>
class Vector
{
public:
    Vector() { cout << "Vector()" << endl; }
};
// 下面这个是对char*类型的完全特例化版本
template<>
class Vector<char *>
{
public:
    Vector() { cout << "Vector<char *>" << endl; }
};
// 下面这个是对指针类型提供的部分特例化版本
template<typename T>
class Vector<T *>
{
public:
    Vector() { cout << "Vector<T *>" << endl; }
};
// 下面这个是对函数指针（有返回值，有两个形参变量）类型提供的部分特例化版本
template<typename R, typename A1, typename A2>
class Vector<R(*)(A1, A2)>
{
public:
    Vector() { cout << "Vector<R(*)(A1, A2)>" << endl; }
};

int sum(int a, int b)
{
    return a + b;
}
int main()
{
    Vector<int> vec1; // Vector()
    // Vector<char *> vec2; /Vector<char *>
    Vector<int *> vec3; // Vector<T *>
    Vector<int(*) (int, int)> vec4; // Vector<R(*)(A1, A2)>

    typedef int(*PFUNC1)(int, int); // PFUNC1是函数指针类型
    PFUNC1 pfunc1 = sum;
    cout << pfunc1(10, 20) << endl;

    typedef int PFUNC2(int, int); // PFUNC2是函数类型
    PFUNC2 *pfunc2 = sum;
    cout << (*pfunc2) (10, 20) << endl;

    return 0;    
}
#endif

#if 0
template<typename T>
bool compare(T a, T b)
{
    cout << "template compare" << endl;
    return a > b;
}
template<>
bool compare(const char *a, const char *b)
{
    cout << "compare<const char *>" << endl;
    return strcmp(a, b) > 0;
}

int main()
{
    compare(10, 20);
    compare("aaa", "bbb");


    return 0;
}
#endif