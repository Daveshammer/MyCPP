#include <iostream>
#include <string>
#include <memory>
using namespace std;

/*
工厂方法模式：定义一个用于创建对象的接口，让子类决定将哪一个类实例化。工厂方法模式使一个类的实例化延迟到子类。

工厂方法为每一种产品提供相应的实例工厂进行对象创建
通过产生具体的工厂创建具体的产品，做到了在扩充新产品时，能够达到软件设计的“开-闭”原则，
因为生产新的Product，只需要提供新的Factory类就可以了，不用修改原来的代码。

问题：
问题，就是每一个实例工厂负责生产一个实例产品，也就是一个产品对应一个工厂，一个工厂对应一个产品，
那么小米不仅仅生产手机，还生产耳机，智能手环，智能插座等等相关的小米产品簇，不可能给这每一个产品都创建一个工厂类，
那样的话代码中的类就太多了，不好维护，而且也不符合实际情况。
*/

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

// 具体的产品Product派生类型
class ProductA : public Product
{
public:
    ProductA(string name) :Product(name){}
    void show() { cout << "获取了一个ProductA对象:" << _name << endl; }
};
class ProductB : public Product
{
public:
    ProductB(string name) :Product(name){}
    void show() { cout << "获取了一个ProductB对象:" << _name << endl; }
};

// 工厂基类
class Factory
{
public:
    virtual Product* createProduct() = 0;
};

// 生产小米手机的工厂
class XiaomiFactory : public Factory
{
public:
    Product* createProduct() { return new ProductA("小米手机"); }
};
// 生产华为手机的工厂
class HuaweiFactory : public Factory
{
public:
    Product* createProduct() { return new ProductB("华为手机"); }
};

int main()
{
    // // 生产小米手机的工厂
    // Factory* xiaomiFactory = new XiaomiFactory();
    // // 生产华为手机的工厂
    // Factory* huaweiFactory = new HuaweiFactory();
    // // 生产小米手机
    // Product* xiaomi = xiaomiFactory->createProduct();
    // xiaomi->show();
    // // 生产华为手机
    // Product* huawei = huaweiFactory->createProduct();
    // huawei->show();
    // delete xiaomiFactory;
    // delete huaweiFactory;

    // 使用智能指针自动释放堆内存
    unique_ptr<Factory> xiaomiFactory(new XiaomiFactory());
    unique_ptr<Factory> huaweiFactory(new HuaweiFactory());
    // 通过工厂方法创建产品
    unique_ptr<Product> xiaomi(xiaomiFactory->createProduct());
    xiaomi->show();
    unique_ptr<Product> huawei(huaweiFactory->createProduct());
    huawei->show();

    return 0;
}
