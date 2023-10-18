#include <iostream>
#include <memory>
using namespace std;

/*
装饰器：主要是增加现有类的功能
*/

class Car
{
public:
    virtual void show() = 0;
};

// 三个实体的汽车类
class Bmw : public Car
{
public:
    void show() { cout << "Bmw:"; }
};
class Audi : public Car
{
public:
    void show() { cout << "Audi:"; }
};
class Benz : public Car
{
public:
    void show() { cout << "Benz:"; }
};

// 装饰器1 定速巡航
class ConcreteDecorator1 : public Car
{
public:
    // ConcreteDecorator1(Car* car) :pCar(car) {}
    ConcreteDecorator1(shared_ptr<Car> car) :pCar(car) {}
    void show() { 
        pCar->show(); 
        cout << "定速巡航 ";    
    }
private:
    // Car* pCar;
    shared_ptr<Car> pCar;
};
// 装饰器2 自动刹车
class ConcreteDecorator2 : public Car
{
public:
    // ConcreteDecorator2(Car* car) :pCar(car) {}
    ConcreteDecorator2(shared_ptr<Car> car) :pCar(car) {}
    void show() { 
        pCar->show(); 
        cout << "自动刹车 ";    
    }
private:
    // Car* pCar;
    shared_ptr<Car> pCar;
};
// 装饰器3 车道偏离
class ConcreteDecorator3 : public Car
{
public:
    // ConcreteDecorator3(Car* car) :pCar(car) {}
    ConcreteDecorator3(shared_ptr<Car> car) :pCar(car) {}
    void show() { 
        pCar->show(); 
        cout << "车道偏离 ";    
    }
private:
    // Car* pCar;
    shared_ptr<Car> pCar;
};



int main()
{
    // Car *p1 = new ConcreteDecorator1(new Bmw());
    // p1 = new ConcreteDecorator2(p1);
    // p1 = new ConcreteDecorator3(p1);
    // p1->show();
    
    shared_ptr<Car> p1 = make_shared<ConcreteDecorator1>(make_shared<Bmw>());
    p1 = make_shared<ConcreteDecorator2>(p1);
    p1 = make_shared<ConcreteDecorator3>(p1);
    p1->show();

    return 0;
}