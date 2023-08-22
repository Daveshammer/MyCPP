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
        new (p) T(x); // 定位new
    }
    void destroy(T *p)
    {
        p->~T();
    }
};

// template<typename T>
template <typename T, typename Alloc = Allocator<T>>
class vector
{
public:
    vector(int size = 10, const Alloc &alloc = Allocator<T>())
    {
        // 将内存开辟和对象构造分开处理
        //  _first = new T[size];
        _first = _allocator.allocate(size);
        _last = _first;
        _end = _first + size;
    }
    ~vector()
    {
        // 析构有效的元素，然后释放指针指向的堆内存
        //  delete[] _first;
        for (int i = 0; i < _last - _first; ++i)
        {
            _allocator.destroy(&_first[i]); // 析构对象
        }
        _allocator.deallocate(_first); // 释放堆上的数组内存
        _first = _last = _end = nullptr;
    }
    vector(const vector<T> &rhs)
    {
        int size = rhs._end - rhs._first;
        _first = new T[size];
        int len = rhs._last - rhs._first;
        for (int i = 0; i < len; ++i)
        {
            // _first[i] = rhs._first[i];
            _allocator.construct(&_first[i], rhs._first[i]); // 构造对象
        }
        _last = _first + len;
        _end = _first + size;
    }
    vector<T> &operator=(const vector<T> &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        // delete[] _first; //释放原有的资源
        for (int i = 0; i < _last - _first; ++i)
        {
            _allocator.destroy(&_first[i]); // 析构对象
        }
        _allocator.deallocate(_first); // 释放堆上的数组内存

        int size = rhs._end - rhs._first;
        _first = new T[size];
        int len = rhs._last - rhs._first;
        for (int i = 0; i < len; i++)
        {
            _first[i] = rhs._first[i];
        }
        _last = _first + len;
        _end = _first + size;
    }
    void push_back(const T &val)
    {
        if (full())
        {
            expand();
        }
        // *_last = val;
        _allocator.construct(_last, val); // 构造对象
        ++_last;
    }
    void pop_back()
    {
        if (empty())
            return;
        verify(_last - 1, _last);
        // erase(it); //则需检查verify(it._ptr, _last);
        --_last;                   // 不仅要维护_last指针，还要析构对象
        _allocator.destroy(_last); // 析构对象
    }
    T back() const
    {
        return *(_last - 1);
    }
    bool full() const { return _last == _end; }
    bool empty() const { return _first == _last; }
    int size() const { return _last - _first; }
    T &operator[](int index)
    {
        if (index < 0 || index >= size())
        {
            throw "OutOfRangeException";
        }
        return _first[index];
    }

    // 迭代器一般实现成容器的嵌套类型
    class iterator
    {
    public:
        friend class vector<T, Alloc>; // 容器类是迭代器类的友元类
        iterator(T *ptr = nullptr, vector<T, Alloc> *pvec = nullptr) : _ptr(ptr), _pvec(pvec)
        {
            Iterator_Base *itb = new Iterator_Base(this, _pvec->_head._next);
            _pvec->_head._next = itb;
        }
        bool operator!=(const iterator &it) const
        {
            // 检查迭代器有效性
            if (_pvec == nullptr || _pvec != it._pvec) // 容器指针为空，或者容器不一样
            {
                throw "iterator is invalid";
            }
            return _ptr != it._ptr;
        }
        void operator++() // 前置++
        {
            if (_pvec == nullptr)
            {
                throw "iterator is invalid";
            }
            ++_ptr;
        }
        T &operator*()
        {
            if (_pvec == nullptr)
            {
                throw "iterator is invalid";
            }
            return *_ptr;
        }
        const T &operator*() const
        {
            if (_pvec == nullptr)
            {
                throw "iterator is invalid";
            }
            return *_ptr;
        }

    private:
        T *_ptr;
        // 当前迭代器是哪个容器对象
        vector<T, Alloc> *_pvec;
    };
    // 需要给容器提供begin()和end()接口
    iterator begin() { return iterator(_first, this); }
    iterator end() { return iterator(_last, this); }

    //检查迭代器失效
    void verify(T *first, T *last)
    {
        Iterator_Base *pre = &this->_head; //迭代器链表头节点
        Iterator_Base *it = pre->_next;   //迭代器链表第一个节点
        while (it != nullptr)
        {
            if (it->_cur->_ptr > first && it->_cur->_ptr <= last) //左开右闭区间
            {
                //迭代器失效，把iterator持有的容器指针置nullptr
                it->_cur->_pvec = nullptr;
                //删除迭代器节点，继续判断后面的迭代器节点是否失效
                pre->_next = it->_next;
                delete it;
                it = pre->_next;
            }
            else
            {
                pre = it;
                it = it->_next;
            }
        }
    }

    //自定义vector容器insert方法的实现
    iterator insert(iterator it, const T &val)
    {
        verify(it._ptr - 1, _last); //左开右闭区间
        T *p = _last;
        while (p > it._ptr)
        {
            _allocator.construct(p, *(p - 1)); // 构造对象
            _allocator.destroy(p - 1);         // 析构对象
            --p;
        }
        _allocator.construct(p, val); // 构造对象
        ++_last;
        return iterator(p, this);
    }

    //自定义vector容器erase方法的实现
    iterator erase(iterator it)
    {
        verify(it._ptr - 1, _last); //左闭右开区间
        T *p = it._ptr;
        while (p < _last - 1)
        {
            _allocator.destroy(p + 1);         // 析构对象
            _allocator.construct(p, *(p + 1)); // 构造对象
            ++p;
        }
        _allocator.destroy(p); // 析构对象
        --_last;
        return iterator(it._ptr, this);
    }

private:
    T *_first;        // 指向数组的起始位置
    T *_last;         // 指向数组中有效元素的后继位置
    T *_end;          // 指向数组空间的后继位置
    Alloc _allocator; // 空间配置器

    //容器迭代器失效增加代码
    struct Iterator_Base
    {
        Iterator_Base(iterator *c = nullptr, Iterator_Base *n = nullptr)
            : _cur(c), _next(n)
        {
        }
        iterator *_cur;
        Iterator_Base *_next;
    };
    Iterator_Base _head; //迭代器链表头节点

    void expand() // 容器两倍扩容
    {
        int size = _end - _first;
        // T *ptmp = new T[size * 2];
        T *ptmp = _allocator.allocate(size * 2);
        for (int i = 0; i < size; ++i)
        {
            // ptmp[i] = _first[i];
            _allocator.construct(&ptmp[i], _first[i]); // 构造对象
        }
        // delete[] _first;
        for (int i = 0; i < _last - _first; ++i)
        {
            _allocator.destroy(&_first[i]); // 析构对象
        }
        _allocator.deallocate(_first); // 释放堆上的数组内存

        _first = ptmp;
        _last = _first + size;
        _end = _first + size * 2;
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
#if 0
    Test t1, t2, t3;
    cout <<  "----------------" << endl;
    vector<Test> vec;
    vec.push_back(t1);
    vec.push_back(t2);
    vec.push_back(t3);
    cout <<  "----------------" << endl;
    vec.pop_back();
    cout <<  "----------------" << endl;
#endif

#if 0
    vector<int> vec;
    for (int i = 0; i < 20; i++)
    {
        vec.push_back(i);
    }
    // while (!vec.empty())
    // {
    //     cout << vec.back() << " ";
    //     vec.pop_back();
    // }
    // cout << endl;

    vector<int>::iterator it = vec.begin();
    while (it != vec.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
#endif

#if 0
    vector<int> vec;
    for (int i = 0; i < 2; i ++)
        vec.push_back(rand() % 100);
    
    auto it1 = vec.end();
    vec.pop_back(); //verify(_last - 1, _last);
    auto it2 = vec.end();
    cout << (it1 != it2) << endl;
#endif

#if 1
    vector<int> vec;
    for (int i = 0; i < 2; i ++)
        vec.push_back(rand() % 100);
    
    for (auto &e : vec) cout << e << " ";
    cout << endl;
    
    auto it = vec.begin();
    while (it != vec.end())
    {
        if (*it % 2 == 0) 
        {
            // vec.insert(it, *it - 1);
            it = vec.insert(it, *it - 1);
            ++ it;
        }
        ++ it;
    }

    for (auto &e : vec) cout << e << " ";
#endif

    return 0;
}