#include <stdio.h> // puts

class shape
{
public:
    virtual ~shape() {}
};

class circle : public shape
{
public:
    circle() { puts("circle()"); }
    ~circle() { puts("~circle()"); }
};

class triangle : public shape
{
public:
    triangle() { puts("triangle()"); }
    ~triangle() { puts("~triangle()"); }
};

class rectangle : public shape
{
public:
    rectangle() { puts("rectangle()"); }
    ~rectangle() { puts("~rectangle()"); }
};

class result
{
public:
    result() { puts("result()"); }
    ~result() { puts("~result()"); }
};

result process_shape(const shape &shape1, const shape &shape2)
{
    puts("process_shape()");
    return result();
}

int main()
{
    puts("main()");
    result&& res = process_shape(circle(), triangle()); //延长了临时对象result的生命周期
    // process_shape(circle(), triangle());
    puts("return from process_shape()");
}