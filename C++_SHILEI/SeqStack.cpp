#include <iostream>
using namespace std;

template <typename T>
class Allocator
{
public:
    T *allocate(size_t size)
    {
        return (T *)malloc(size * sizeof(T));
    }
    void deallocate(T *p)
    {
        free(p);
    }
    void construct(T *p, const T &x)
    {
        new (p) T(x);
    }
    void destroy(T *p)
    {
        p->~T();
    }
};

// 容器底层内存开辟，内存释放，对象构造和析构，都通过allocator来完成
template <typename T, typename Alloc = Allocator<T>>
class SeqStack
{
public:
    // 构造和析构函数名不用加<T>，其它出现模板的地方都要加上类型参数列表
    SeqStack(int size = 10, const Alloc &alloc = Allocator<T>()) // 需要把内存开辟和对象构造分开处理
                                                                 //  : _pstack(new T[size])
                                                                 //  , _top(0)
                                                                 //  , _size(size)
    {
        _pstack = _allocator.allocate(size);
        _top = 0;
        _size = size;
    }
    ~SeqStack()
    {
        // 析构有效的元素，然后释放_pstack指针指向的堆内存
        // delete[] _pstack;
        for (int i = 0; i < _top; ++i)
        {
            _allocator.destroy(&_pstack[i]); // 析构对象
        }
        _allocator.deallocate(_pstack); // 释放堆上的数组内存
        _pstack = nullptr;
    }
    SeqStack(const SeqStack<T> &stack)
        : _top(stack._top), _size(stack._size)
    {
        // _pstack = new T[stack._size];
        _pstack = _allocator.allocate(stack._size);
        for (int i = 0; i < stack._top; ++i)
        {
            _pstack[i] = stack._pstack[i];
        }
        _top = stack._top;
        _size = stack._size;
        cout << "SeqStack(const SeqStack<T> &stack)" << endl;
    }
    SeqStack<T> &operator=(const SeqStack<T> &stack)
    {
        if (this != &stack)
        {
            // delete[] _pstack;
            for (int i = 0; i < _top; ++i)
            {
                _allocator.destroy(&_pstack[i]); // 析构对象
            }
            _allocator.deallocate(_pstack); // 释放堆上的数组内存
            _pstack = nullptr;
            // _pstack = new T[stack._size];
            _pstack = _allocator.allocate(stack._size);
            for (int i = 0; i < stack._top; ++i)
            {
                _pstack[i] = stack._pstack[i];
            }
            _top = stack._top;
            _size = stack._size;

            cout << "SeqStack<T> &operator=(const SeqStack<T> &stack)" << endl;
        }
        return *this;
    }

    void Push(const T &x)
    {
        if (IsFull())
        {
            expand();
        }
        // _pstack[_top++] = x;
        _allocator.construct(&_pstack[_top++], x);
    }
    void Pop()
    {
        if (IsEmpty())
        {
            return;
        }
        --_top;
        _allocator.destroy(&_pstack[_top]);
    }
    T &GetTop() const
    {
        return _pstack[_top - 1];
    }
    bool IsEmpty() const
    {
        return _top == 0;
    }
    bool IsFull() const
    {
        return _top == _size;
    }
    int GetSize() const
    {
        return _top;
    }

private:
    T *_pstack;
    int _top;
    int _size;
    Alloc _allocator;

    void expand()
    {
        // T *p = new T[_size * 2];
        T *p = _allocator.allocate(_size * 2);

        for (int i = 0; i < _size; ++i)
        {
            // p[i] = _pstack[i];
            _allocator.construct(&p[i], _pstack[i]);
        }

        // delete[] _pstack;
                for (int i = 0; i < _top; ++i)
        {
            _allocator.destroy(&_pstack[i]); // 析构对象
        }
        _allocator.deallocate(_pstack); // 释放堆上的数组内存
        _pstack = nullptr;

        _pstack = p;
        _size *= 2;
    }
};

class Test
{
public:
    Test() { cout << "Test()" << endl; }
    Test(const Test &t) { cout << "Test(const Test &t)" << endl; }
    Test &operator=(const Test &t)
    {
        cout << "Test &operator=(const Test &t)" << endl;
        return *this;
    }
    Test(const Test &&t) { cout << "Test(const Test &&t)" << endl; }
    
    ~Test() { cout << "~Test()" << endl; }
};

int main()
{
    Test t1;
    cout << "------------" << endl;
    SeqStack<Test> s;
    s.Push(t1);
    s.Pop();
    cout << "------------" << endl;
    

    return 0;
}