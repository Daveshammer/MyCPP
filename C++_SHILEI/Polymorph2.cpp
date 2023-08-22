#include <iostream>
#include <cstring>
using namespace std;

class Base
{
public:
    Base()
    {
        /*
        00007FF7AEEC1FF0  mov         qword ptr [rsp+8],rcx
        00007FF7AEEC1FF5  push        rbp
        00007FF7AEEC1FF6  push        rdi
        00007FF7AEEC1FF7  sub         rsp,0E8h
        00007FF7AEEC1FFE  lea         rbp,[rsp+20h]
        00007FF7AEEC2003  lea         rcx,[__392428BF_main@cpp (07FF7AEED5067h)]
        00007FF7AEEC200A  call        __CheckForDebuggerJustMyCode (07FF7AEEC14A6h)
        00007FF7AEEC200F  mov         rax,qword ptr [this]
        00007FF7AEEC2016  lea         rcx,[Base::`vftable' (07FF7AEECBC30h)]
        00007FF7AEEC201D  mov         qword ptr [rax],rcx   // vfptr <- vftable
        */
        cout << "Base()" << endl;
        clear();
    }
    virtual ~Base() { cout << "~Base()" << endl; }

    void clear() { memset(this, 0, sizeof(*this)); }
    virtual void show() { cout << "Base::show()" << endl; }
};
class Derive : public Base
{
public:
    Derive() { cout << "Derive()" << endl; }
    ~Derive() { cout << "~Derive()" << endl; }

    void show() { cout << "Derive::show()" << endl; }
};

int main()
{
    Base *pb = new Base();
    // clear函数将Base的vfptr清零
    pb->show();
    delete pb;

    Base *pb2 = new Derive();
    pb2->show();
    delete pb2;

    return 0;
}