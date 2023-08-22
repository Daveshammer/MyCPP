#include <iostream>
using namespace std;

#if 0
// 饿汉式单例模式：在程序启动时就实例化了该对象，并没有推迟到第一次使用该对象时再进行实例化
// 如果运行过程中没有使用到，该实例对象就被浪费掉了
class Singleton
{
public:
	static Singleton* getInstance() { return &single; } // 3.获取类的唯一实例对象的接口方法

private:
	static Singleton single; // 2.定义一个唯一的实例对象
	Singleton() { cout << "Singleton()" << endl; } // 1.构造函数私有化
	~Singleton() { cout << "~Cingleton()" << endl; }
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

};
Singleton Singleton::single; // 4.在类外定义并初始化唯一的实例对象

#endif

#if 1
/*
单例模式：保证一个类仅有一个实例，并且提供一个全局访问点。

懒汉式单例模式：唯一的实力对象知道第一次获取它时才被创建
*/ 
class Singleton
{
public:
	static Singleton* getInstance() { // 3.获取类的唯一实例对象的接口方法
        static Singleton single; // 2.定义一个唯一的实例对象 对于static静态局部变量的初始化，编译器会自动对它的初始化进行加锁和解锁控制，使静态局部变量的初始化成为线程安全的操作
        return &single; 
    } 

private:
	Singleton() { cout << "Singleton()" << endl; } // 1.构造函数私有化
	~Singleton() { cout << "~Singleton()" << endl; }
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

};
#endif

int main()
{
	Singleton* p1 = Singleton::getInstance();
	Singleton* p2 = Singleton::getInstance();
	Singleton *p3 = Singleton::getInstance();
	cout << p1 << " " << p2 << " " << p3 << endl;

	return 0;
}