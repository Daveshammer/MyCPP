#include <iostream>
#include <string>
#include <memory>
using namespace std;
/*
简单工厂模式：专门定义一个类来负责创建其他类的实例，被创建的实例通常都具有共同的父类

优点：
所有对象的创建不再通过new 类名称的方式进行了，而是把对象的创建都封装在了SimpleFactory类的createProduct方法当中，
通过传入一个事先设计好的枚举类型，然后返回一个对应的对象，既解耦了对象的创建，还不用再记忆那么多的类名。

问题：
createProduct这个函数做不到“开-闭”原则，即对原有代码修改关闭，对功能扩展开放，
这个函数随着新对象的添加，或者原有对象的删除，都会导致该函数的代码修改，而且有可能影响原来的功能
*/

/*1. 产品Product基类*/
// 产品类型
class Product
{
public:
	Product(string name) :_name(name) {}
	// 模拟产品对象的一个抽象方法
	virtual void show() = 0; 
protected:
	string _name;
};

/*2. 具体的产品Product派生类型*/
// 产品实体类型定义
class ProductA : public Product
{
public:
	ProductA(string name) :Product(name){}
	void show() { cout << "获取了一个ProductA对象:" << _name << endl; }
};
// 产品实体类型定义
class ProductB : public Product
{
public:
	ProductB(string name) :Product(name) {}
	void show() { cout << "获取了一个ProductB对象:" << _name << endl;
	}
};

/*3. 创建描述产品类型的枚举和简单工厂类*/
// 产类枚举类型定义
enum ProductType
{
	XIAOMI,
	HUAWEI,
};
// 简单工厂类
class SimpleFactory
{
public:
	// 通过传入的枚举类型，创建相应的对象，返回所有对象的基类指针
	Product* createProduct(ProductType type)
	{
		switch (type)
		{
		case XIAOMI:
			return new ProductA("小米手机");
		case HUAWEI:
			return new ProductB("华为手机");
		}
	}
};


int main()
{
	// 创建简单工厂实例
	SimpleFactory sf;

	// 使用智能指针自动释放堆内存
	unique_ptr<Product> p1(sf.createProduct(XIAOMI));
	unique_ptr<Product> p2(sf.createProduct(HUAWEI));

	p1->show();
	p2->show();

	return 0;
}
