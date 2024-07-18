#include <iostream>
using namespace std;

class Base
{
public:
    Base()
    {
        cout<<"Base默认构造函数调用"<<endl;
    }
    Base(int i)
    {
        cout<<"Base参数构造函数调用"<<endl;
        cout<<i<<endl;
    }
    virtual ~Base(){}
};

class Base1: virtual public Base{
public:
    Base1(int i,int j=0):Base(j){
        cout<<"Base1参数构造函数调用"<<endl;
        cout<<i<<endl;
    }
    virtual ~Base1(){}
};

class Base2: virtual public Base{
public:
    Base2(int i):Base(i){
        cout<<"Base2参数构造函数调用"<<endl;
        cout<<i<<endl;
    }
    virtual ~Base2(){}
};

class Drived:public Base1,public Base2{
public:

    Drived(int a,int b):Base1(a),Base2(b){

    }
    virtual ~Drived(){}
};

int main()
{
    Drived d(1, 2);
}