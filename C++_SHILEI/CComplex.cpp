#include <iostream>
using namespace std;

// 复数类
class CComplex
{
public:
    CComplex(int real = 0, int image = 0)
        : _mreal(real), _mimage(image)
    {
    }
    CComplex(const CComplex &c)
        : _mreal(c._mreal), _mimage(c._mimage)
    {
    }
    CComplex& operator=(const CComplex &c)
    {
        if (this != &c)
        {
            _mreal = c._mreal;
            _mimage = c._mimage;
        }
        return *this;
    }
    ~CComplex()
    {
    }
    CComplex operator+(const CComplex &c)
    {
        return CComplex(_mreal + c._mreal, _mimage + c._mimage);
    }
    CComplex operator++(int x)
    {
        // CComplex tmp = *this;
        // ++_mreal;
        // ++_mimage;
        // return tmp;
        return CComplex(_mreal++, _mimage++); //少了tmp对象的构造和析构
    }
    CComplex& operator++()
    {
        ++_mreal;
        ++_mimage;
        return *this;
    }

    void show()
    {
        cout << _mreal << " + " << _mimage << "i" << endl;
    }

private:
    int _mreal;
    int _mimage;

    friend CComplex operator+(const CComplex &lhs, const CComplex &rhs);
    friend ostream& operator<<(ostream& os, const CComplex& c);
    friend istream& operator>>(istream& in, CComplex& c);
};
CComplex operator+(const CComplex &lhs, const CComplex &rhs) //全局的成员方法访问私有成员需要加friend
{
    return CComplex(lhs._mreal + rhs._mreal, lhs._mimage + rhs._mimage);
}

ostream& operator<<(ostream& os, const CComplex& c)
{
    os << c._mreal << " + " << c._mimage << "i" << endl;
    return os;
}
istream& operator>>(istream& in, CComplex& c)
{
    in >> c._mreal >> c._mimage;
    return in;
}

int main()
{
    CComplex comp1(10, 10);
    CComplex comp2(20, 20);

    CComplex comp3 = comp1.operator+(comp2);
    comp3.show();

    CComplex comp4 = comp1 + 20;
    comp4.show();

    CComplex comp5 = 30 + comp1;
    comp5.show();
    cout << "----------------" << endl;

    comp5 = comp1 ++; //operator++() 前置++，operator++(int) 后置++
    comp1.show();
    comp5.show();
    cout << "----------------" << endl;

    comp5 = ++comp1;
    comp1.show();
    // comp5.show();
    cout << comp5 << endl;
    cout << "----------------" << endl;

    cin >> comp1 >> comp2;
    cout << comp1 << comp2 << endl;

    return 0;
}