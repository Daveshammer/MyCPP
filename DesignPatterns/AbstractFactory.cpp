#include <iostream>
#include <string>
#include <memory>
using namespace std;

/*
抽象工厂：提供一个创建一系列相关或相互依赖对象的接口，而无需指定具体的类。

抽象工厂模式把一个产品簇的产品放在一个工厂类中去创建，不仅大大减少了工厂类的个数，更符合现实中工厂生产产品的模式。
*/

// 产品簇手机类型
class ProductA
{
public:
	ProductA(string name) :_name(name) {}
	// 模拟产品对象的一个抽象方法
	virtual void show() = 0;
protected:
	string _name;
};
// 产品实体类型定义
class XiaomiPhone : public ProductA
{
public:
	XiaomiPhone(string name) :ProductA(name){}
	void show() { cout << "获取了一个小米手机:" << _name << endl; }
};
// 产品实体类型定义
class HuaweiPhone : public ProductA
{
public:
	HuaweiPhone(string name) :ProductA(name) {}
	void show() { cout << "获取了一个华为手机:" << _name << endl;
	}
};

// 产品簇智能手环类型
class ProductB
{
public:
	ProductB(string name) :_name(name) {}
	// 模拟产品对象的一个抽象方法
	virtual void show() = 0;
protected:
	string _name;
};
// 产品实体类型定义
class XiaomiCircle : public ProductB
{
public:
	XiaomiCircle(string name) :ProductB(name) {}
	void show() { cout << "获取了一个小米智能手环设备:" << _name << endl; }
};
// 产品实体类型定义
class HuaweiCircle : public ProductB
{
public:
	HuaweiCircle(string name) :ProductB(name) {}
	void show() {
		cout << "获取了一个华为智能手环设备:" << _name << endl;
	}
};

// 抽象工厂，创建通过一个产品簇的设备产品
class AbstractFactory
{
public:
	// 工厂里面创建手机的纯虚函数接口
	virtual ProductA* createPhone() = 0;
	// 工厂里面创建智能手环的纯虚函数接口
	virtual ProductB* createSmartCircle() = 0;
};

// 生产小米产品簇的工厂
class XiaomiFactory : public AbstractFactory
{
public:
	ProductA* createPhone()
	{
		// 小米工厂肯定生产小米手机
		return new XiaomiPhone("小米x9");
	}
	ProductB* createSmartCircle()
	{
		// 小米工厂肯定生产小米智能手环
		return new XiaomiCircle("小米智能手环2代时尚版");
	}
};
// 生产华为产品簇的工厂
class HuaweiFactory : public AbstractFactory
{
public:
	ProductA* createPhone()
	{
		// 华为工厂肯定生产华为手机
		return new HuaweiPhone("华为荣耀7x");
	}
	ProductB* createSmartCircle()
	{
		// 华为工厂肯定生产华为智能手环
		return new HuaweiCircle("华为智能手环B3青春版");
	}
};

int main()
{
	// 使用智能指针自动释放堆内存
	// 创建具体的工厂
	unique_ptr<AbstractFactory> f1(new XiaomiFactory);
	unique_ptr<AbstractFactory> f2(new HuaweiFactory);

	// 通过工厂方法创建手机产品
	unique_ptr<ProductA> p1(f1->createPhone());
	unique_ptr<ProductA> p2(f2->createPhone());
	p1->show();
	p2->show();

	// 通过工厂方法创建智能手环产品
	unique_ptr<ProductB> p3(f1->createSmartCircle());
	unique_ptr<ProductB> p4(f2->createSmartCircle());
	p3->show();
	p4->show();

	return 0;
}
