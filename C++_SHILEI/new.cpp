#include <iostream>
using namespace std;

/*
1.malloc和new的区别
a.malloc按字节开辟内存, new开辟内存时需要指定类型
  所有malloc返回的都是void*，需要强制转换成相应的类型
b.malloc只负责开辟空间, new不仅有malloc的功能, 还可以进行数据的初始化
  new int(20);  new int[20]();
c.malloc开辟内存失败返回nullptr指针; new抛出的是bad_alloc异常

2.free和delete的区别
delete会先调用对象的析构函数, 然后再释放内存
*/

void* operator new(size_t size)
{
    void* p = malloc(size);
    if (nullptr == p)
    {
        throw bad_alloc();
    }
    cout << "operator new addr:" << p << endl;
    return p;
}
void operator delete(void* ptr)
{
    cout << "operator delete addr:" << ptr << endl;
    free(ptr);
}

void* operator new[](size_t size)
{
    void* p = malloc(size);
    if (nullptr == p)
    {
        throw bad_alloc();
    }
    cout << "operator new[] addr:" << p << endl;
    return p;
}
void operator delete[](void* ptr)
{
    cout << "operator delete[] addr:" << ptr << endl;
    free(ptr);
}

class Test
{
public:
    Test(int data = 10) { cout << "Test()" << endl;}
    ~Test() { cout << "~Test()" << endl; }

#if 0
    Test(int data = 10) :ptr(new int(data)) { cout << "Test()" << endl;}
    ~Test() { cout << "~Test()" << endl; delete ptr; }
#endif
private:
    int *ptr;
};

int main()
{
#if 0
    Test *p1 = new Test();
    delete p1;
#endif

#if 1
    Test *p2 = new Test[2];
    cout << "p2[0]:" << &p2[0] << endl; // p2[0]的地址和申请内存地址不一样，需要额外记录数组元素个数
    delete[] p2;
#endif

#if 0
    try
    {
        int *p = new int; // 调用operator new分配内存，然后调用int的构造函数初始化
        delete p; // 调用ptr指向对象的析构函数，然后调用operator delete释放ptr指向的内存

        int *q = new int[10];
        delete[] q;
    }
    catch(const bad_alloc& e)
    {
        std::cerr << e.what() << '\n';
    }
#endif   

    return 0;
}