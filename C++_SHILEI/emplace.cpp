#include <iostream>
// #include <vector>
using namespace std;

class Test
{
public:
    Test(int a) {cout << "Test(int)" << endl;}
    Test(int a, int b) {cout << "Test(int, int)" << endl;}
    ~Test() {cout << "~Test()" << endl;}
    Test(const Test &t) {cout << "Test(const Test &)" << endl;}
    Test(Test &&t) {cout << "Test(Test &&)" << endl;}
private:
};

// 实现容器的空间配置器
template <typename T>
struct MyAllocator
{
    T *allocate(size_t size)
    {
        cout << "allocate" << endl;
        return (T *)malloc(sizeof(T) * size);
    }
    void deallocate(T *p, size_t size)
    {
        cout << "deallocate" << endl;
        
    }
    template<typename... Args> 
    void construct(T *p, Args&&... args)
    {
        cout << "construct" << endl;
        new(p) T(std::forward<Args>(args)...);
    }
};

template<typename T, typename Alloc = MyAllocator<T>>
class vector
{
public:
    vector() : vec_(nullptr), size_(0), idx_(0) {}
    // 预留内存空间
    void reserve(size_t size)
    {
        vec_ = allocator_.allocate(size);
        size_ = size;
    }
    // push_back
    /*
    void push_back(const T &val)
    {
        allocator_.construct(vec_ + idx_, val);
        idx_++;
    }
    void push_back(T &&val)
    {
        allocator_.construct(vec_ + idx_, std::move(val));
        idx_++;
    }
    */
    template<typename Type>
    void push_back(Type &&val)
    {
        allocator_.construct(vec_ + idx_, std::forward<Type>(val));
        idx_++;
    }
    // emplace_back
    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        // 不管左值引用、右值引用变量，它本身是个左值。传递的过程中，要保持args的引用类型
        allocator_.construct(vec_ + idx_, std::forward<Args>(args)...);
        idx_++;
    }
private:
    T *vec_; // 指向动态开辟的空间
    int size_;  // 空间的大小
    int idx_; // 当前元素的个数
    Alloc allocator_; // 空间配置器
};

int main()
{

#if 1
    Test t1(10);
    // std::vector<Test> v;
    vector<Test, MyAllocator<Test>> v;
    v.reserve(100); // 先开辟100个空间
    cout << "----------------" << endl;

    // 直接插入对象，两个没有区别
    v.push_back(t1); // Test(const Test &)
    v.emplace_back(t1); // Test(const Test &)
    cout << "----------------" << endl;
    /*
    Test(int) // 临时对象
    Test(Test &&) // 移动构造
    ~Test() // 临时对象析构
    */
    v.push_back(Test(20));
    v.emplace_back(Test(20));
    cout << "----------------" << endl;

    v.push_back(20); // Test(int)和Test(Test &&)
    v.emplace_back(30); // Test(int)
    cout << "----------------" << endl;

#endif
 
    return 0;
}