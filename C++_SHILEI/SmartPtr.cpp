#include <iostream>
#include <memory>
using namespace std;

// 对资源进行引用计数的类
template <typename T>
class RefCnt
{
public:
    RefCnt(T *ptr = nullptr) : m_ptr(ptr)
    {
        if (m_ptr != nullptr)
            m_cnt = 1;
    }
    void addRef() { m_cnt++; }
    int delRef() { return --m_cnt; }
    int getCnt() { return m_cnt; }

private:
    T *m_ptr;
    int m_cnt;
};

// 利用栈上的对象出作用域自动析构，来做到资源的自动释放
template <typename T>
class CSmartPtr
{
public:
    CSmartPtr(T *ptr = nullptr) : m_ptr(ptr)
    {
        if (m_ptr != nullptr)
            m_pRefCnt = new RefCnt<T>(m_ptr);
    }
    ~CSmartPtr()
    {
        if (0 == m_pRefCnt->delRef()) // 引用计数为0时，释放资源
        {
            delete m_ptr;
            m_ptr = nullptr;
        }
    }
    CSmartPtr(const CSmartPtr &src) : m_ptr(src.m_ptr), m_pRefCnt(src.m_pRefCnt)
    {
        if (m_ptr != nullptr)
            m_pRefCnt->addRef(); // 引用计数加1
    }
    CSmartPtr<T> &operator=(const CSmartPtr &src)
    {
        if (this == &src)
            return *this;

        m_ptr = src.m_ptr;
        m_pRefCnt = src.m_pRefCnt;
        m_pRefCnt->addRef(); // 引用计数加1
        
        return *this;
    }
    T &operator*() { return *m_ptr; }
    T *operator->() { return m_ptr; }
    RefCnt<T> *getRefCnt() { return m_pRefCnt; }

private:
    T *m_ptr;             // 指向资源的指针
    RefCnt<T> *m_pRefCnt; // 引用计数
};

int main()
{
#if 1
    CSmartPtr<int> ptr1(new int);
    CSmartPtr<int> ptr2(ptr1);
    cout << ptr2.getRefCnt()->getCnt() << endl;
    CSmartPtr<int> ptr3;
    ptr3 = ptr2;

    *ptr1 = 20;
    cout << ptr2.getRefCnt()->getCnt() << endl;
    cout << "*ptr2:" << " " << *ptr3 << endl;

#endif
        return 0;
}