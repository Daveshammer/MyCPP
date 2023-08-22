#include <iostream>
#include <cstring>
using namespace std;

class String
{
public:
    String(const char *str = nullptr)
    {
        cout << "String(const char *)" << endl;
        if (str == nullptr)
        {
            _pstr = new char[1];
            *_pstr = '\0';
        }
        else
        {
            int len = strlen(str);
            _pstr = new char[len + 1];
            strcpy(_pstr, str);
        }
    }
    String(const String &other)
    {
        cout << "String(const String &other)" << endl;
        int len = strlen(other._pstr);
        _pstr = new char[len + 1];
        strcpy(_pstr, other._pstr);
    }
    String &operator=(const String &other)
    {
        cout << "String &operator=(const String &other)" << endl;
        if (this != &other)
        {
            delete[] _pstr;
            int len = strlen(other._pstr);
            _pstr = new char[len + 1];
            strcpy(_pstr, other._pstr);
        }
        return *this;
    }
    ~String()
    {
        cout << "~String()" << endl;
        delete[] _pstr;
        _pstr = nullptr;
    }

    bool operator>(const String &str) const
    {
        return strcmp(_pstr, str._pstr) > 0;
    }
    bool operator<(const String &str) const
    {
        return strcmp(_pstr, str._pstr) < 0;
    }
    bool operator==(const String &str) const
    {
        return strcmp(_pstr, str._pstr) == 0;
    }
    int length() const { return strlen(_pstr); }
    char &operator[](int index) { return _pstr[index]; }
    const char &operator[](int index) const { return _pstr[index]; }
    const char *c_str() const { return _pstr; }

    //给String提供迭代器的实现，迭代器一般实现成容器的嵌套类型
    class iterator
    {
    public:
        iterator(char *p = nullptr) : _p(p) {}
        bool operator!=(const iterator &it) { return _p != it._p; } //迭代器不相等=底层指针不相等
        void operator++() { ++_p; } //前置++
        char& operator*() { return *_p; } //解引用
    private:
        char *_p;
    };
    //begin返回的是容器底层首元素的迭代器的表示
    iterator begin() { return iterator(_pstr); }
    //end返回的是容器底层尾元素后继位置的迭代器的表示
    iterator end() { return iterator(_pstr + strlen(_pstr)); }
private:
    char *_pstr;
    friend String operator+(const String &lhs, const String &rhs);
    friend ostream& operator<<(ostream &os, const String &str);
};
String operator+(const String &lhs, const String &rhs)
{
    int len = strlen(lhs._pstr) + strlen(rhs._pstr);
    String tmp;
    tmp._pstr = new char[len + 1];
    strcpy(tmp._pstr, lhs._pstr);
    strcat(tmp._pstr, rhs._pstr);
    return tmp;
}
ostream& operator<<(ostream &os, const String &str)
{
    os << str._pstr;
    return os;
}

int main()
{
    String str1 = "hello world!";
    String::iterator it = str1.begin();
    while (it != str1.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;

#if 0
    String str1;
    String str2 = "aaa";
    String str3 = "bbb";
    String str4 = str2 + str3;
    String str5 = str2 + "ccc";
    String str6 = "ddd" + str3;

    cout << "str6: " << str6 << endl;

    if (str5 > str6)
    {
        cout << "str5 > str6" << endl;
    }
    else
    {
        cout << "str5 < str6" << endl;
    }

    int len = str6.length();
    for (int i = 0; i < len; ++i)
    {
        str6[i] ++;
        cout << str6[i] << " ";
    }
    cout << endl;

    char buf[1024] = {0};
    strcpy(buf, str6.c_str());
    cout << "buf: " << buf << endl;
#endif

    return 0;
}