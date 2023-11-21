#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class CMyString
{
public:
    CMyString(const char *str = nullptr)
    {
        cout << "CMyString(const char *)" << endl;
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
    CMyString(const CMyString &other)
    {
        cout << "CMyString(const CMyString &other)" << endl;
        int len = strlen(other._pstr);
        _pstr = new char[len + 1];
        strcpy(_pstr, other._pstr);
    }
    CMyString(CMyString &&other)
    {
        cout << "CMyString(CMyString &&other)" << endl;
        // 资源转移
        _pstr = other._pstr;
        other._pstr = nullptr;
    }

    CMyString& operator=(const CMyString &other)
    {
        cout << "CMyString& operator=(const CMyString &other)" << endl;
        if (this != &other)
        {
            delete[] _pstr;
            int len = strlen(other._pstr);
            _pstr = new char[len + 1];
            strcpy(_pstr, other._pstr);
        }
        return *this;
    }
    CMyString& operator=(CMyString &&other)
    {
        cout << "CMyString& operator=(const CMyString &&other)" << endl;
        if (this != &other)
        {
            delete[] _pstr;
            _pstr = other._pstr;
            other._pstr = nullptr;
        }
        return *this;
    }
    ~CMyString()
    {
        cout << "~CMyString()" << endl;
        delete[] _pstr;
        _pstr = nullptr;
    }
    const char *c_str() const { return _pstr; }

private:
    char *_pstr;

    friend CMyString operator+(const CMyString &str1, const CMyString &str2);
    friend ostream &operator<<(ostream& os, const CMyString& str);
};

CMyString GetString(CMyString &str)
{
    const char *pstr = str.c_str();
    return CMyString(pstr);
}

CMyString operator+(const CMyString &str1, const CMyString &str2)
{
    int len = strlen(str1.c_str()) + strlen(str2.c_str());
    // char *pstr = new char[len + 1];
    // strcpy(pstr, str1.c_str());
    // strcat(pstr, str2.c_str());
    // CMyString tmpStr(pstr);
    // delete[] pstr;
    // return tmpStr;

    CMyString tmpStr;
    tmpStr._pstr = new char[len + 1];
    strcpy(tmpStr._pstr, str1.c_str());
    strcat(tmpStr._pstr, str2.c_str());
    return tmpStr;
}
ostream& operator<<(ostream& os, const CMyString& str)
{
    os << str.c_str();
    return os;
}

int main()
{
#if 0
    CMyString str1("aaaaaaaaaaa"); // CMyString(const char *)
    CMyString str2;                // CMyString(const char *)
    // 会首选带右值引用的赋值，如果没有，再去找带左值引用的赋值
    str2 = GetString(str1);        // CMyString(const char *) 和 CMyString &operator=(const CMyString &&other)
    // CMyString str2 = GetString(str1); // 直接构造，没有拷贝 CMyString(const char *)
    cout << str2.c_str() << endl;

    CMyString &&str3 = CMyString("aaa"); // 可以把右值绑定到一个右值引用上
    CMyString &str4 = str3;              // 右值引用有内存有名字，可以绑定到左值引用上
#endif

#if 0
    CMyString str1 = "hello";
    CMyString str2 = "world";
    CMyString str3 = str1 + str2; // 直接构造，没有拷贝
    cout << str3 << endl;
#endif

#if 1
    vector<CMyString> vec;
    vec.reserve(10);

    CMyString str1 = "aaa"; // CMyString(const char *)
    vec.push_back(str1); // CMyString(const CMyString& other)

    vec.push_back(CMyString("bbb")); // CMyString(const char *) 和 CMyString(CMyString&& other)
    

#endif

    return 0;
}