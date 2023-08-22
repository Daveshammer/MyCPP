#include <iostream>
#include <memory>
#include <functional>
using namespace std;

template <typename T>
class MyArrayDeletor
{
public:
    void operator()(T *ptr)
    {
        cout << "MyArrayDeletor()" << endl;
        delete[] ptr;
    }
};
template <typename T>
class MyFileDeletor
{
public:
    void operator()(T *ptr)
    {
        cout << "MyFileDeletor()" << endl;
        fclose(ptr);
    }
};

int main()
{
    unique_ptr<int, MyArrayDeletor<int>> ptr1(new int[100]);
    unique_ptr<FILE, MyFileDeletor<FILE>> ptr2(fopen("test.txt", "w"));

    // lambda表达式 =》 函数对象 function
    unique_ptr<int, function<void(int *)>> ptr3(new int[100], [](int *ptr) -> void
                                                {
        cout << "lambda() release new int[100]" << endl;
        delete []ptr; });

    unique_ptr<FILE, function<void(FILE *)>> ptr4(fopen("test.txt", "w"), [](FILE *ptr)
                                                  {
        cout << "lambda() release fopen()" << endl;
        fclose(ptr); });

    return 0;
}