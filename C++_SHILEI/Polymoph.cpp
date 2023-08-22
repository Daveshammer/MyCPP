#include <iostream>
#include <typeinfo>
#include <string>
using namespace std;

/*
如何解释多态？
静态（编译时期）的多态：函数重载、模板
动态（运行时期）的多态：
在继承结构中，基类指针（引用）指向派生类对象，通过该指针（引用）调用同名覆盖方法（虚函数），
基类指针指向哪个派生类对象，就会调用哪个派生类对象的同名覆盖方法（虚函数），成为多态
pbase->show();
多态底层是通过动态绑定来实现的，pbase =》 访问谁的vfptr =》 继续访问谁的vftable =》 调用对应的派生类对象的方法

继承的好处是什么？
1.可以做代码的复用
2.在基类中提供统一的虚函数接口，让派生类进行重写，然后就可以使用多态了
*/

/*
抽象类和普通类有什么区别？
一般把什么类设计成抽象类？
*/

/*
定义Animal的初衷，并不是让Animal抽象某个实体的类型
1.string _name; 让所有的动物实体类通过继承Animal直接复用该属性
2.bark()；给所有的派生类保留统一的覆盖/重写接口

拥有纯虚函数的类，叫做抽象类；抽象类不能再实例化对象了，但是可以定义指针和引用变量
*/

// 动物抽象基类
class Animal
{
public:
    Animal(string name) : _name(name) { cout << "Animal()" << endl; }
    virtual ~Animal() { cout << "~Animal()" << endl; }

    virtual void bark() = 0;

protected:
    string _name;
};

class Cat : public Animal
{
public:
    Cat(string name) : Animal(name) { cout << "Cat()" << endl; }
    ~Cat() { cout << "~Cat()" << endl; }

    void bark() { cout << _name << "Cat::speak()" << endl; }
};
class Dog : public Animal
{
public:
    Dog(string name) : Animal(name) { cout << "Dog()" << endl; }
    ~Dog() { cout << "~Dog()" << endl; }

    void bark() { cout << _name << "Dog::speak()" << endl; }
};
class Pig : public Animal
{
public:
    Pig(string name) : Animal(name) { cout << "Pig()" << endl; }
    ~Pig() { cout << "~Pig()" << endl; }

    void bark() { cout << _name << "Pig::speak()" << endl; }
};
void bark(Animal &animal) // 给外部提供一个统一的接口，让外部调用者传入不同的动物对象
{
    animal.bark(); // Animal::bark()虚函数，动态绑定
}

int main()
{
#if 0
    Cat cat("猫咪");
    Dog dog("旺财");
    Pig pig("佩奇");

    bark(cat);
    bark(dog);
    bark(pig);
#endif

#if 1
    Animal *p1 = new Cat("加菲猫");
    Animal *p2 = new Dog("二哈");

    int *p11 = (int *)p1;
    int *p22 = (int *)p2;
    int tmp = p11[0]; // p11[0]是Cat的前四个字节，也就是vfptr
    p11[0] = p22[0]; // vfptr -> Dog的vftable
    p22[0] = tmp;   // vfptr -> Cat的vftable

    p1->bark(); // 加菲猫Dog::speak()
    p2->bark(); // 二哈Cat::speak()

    delete p1;
    delete p2;
#endif

    return 0;
}