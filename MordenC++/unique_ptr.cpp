#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <functional>
 
struct B {
    // B() { std::cout << "B::B\n";  }
    // virtual ~B() { std::cout << "B::~B\n"; };
    virtual ~B() = default;
    virtual void bar() { std::cout << "B::bar\n"; }
};
struct D : B
{
    D() { std::cout << "D::D\n";  }
    ~D() { std::cout << "D::~D\n";  }
    void bar() override { std::cout << "D::bar\n";  }
};
 
// 消费 unique_ptr 的函数能以值或以右值引用接收它
std::unique_ptr<D> pass_through(std::unique_ptr<D> p)
{
    p->bar();
    return p;
}
 
void close_file(std::FILE* fp) { std::fclose(fp); }

struct List
{
    struct Node
    {
        int data;
        std::unique_ptr<Node> next;
    };

    std::unique_ptr<Node> head;

    ~List()
    {
        int i = 0; // 用于计数删除到哪个节点
        while(head)
        {
            std::unique_ptr<Node> next = std::move(head->next);
            head = std::move(next);
            std::cout << "delete " << i++ << std::endl;
        }
    }

    void push(int data)
    {
        std::unique_ptr<Node> node(new Node{data});
        node->next = std::move(head);
        head = std::move(node);
    }
};
 
int main()
{
    // 转移所有权
    std::cout << "1) Unique ownership semantics demo\n";
    {
        std::unique_ptr<D> p = std::make_unique<D>(); // p 是占有 D 的 unique_ptr
        std::unique_ptr<D> q = pass_through(std::move(p)); 
        assert(!p); // 现在 p 不占有任何内容并保有空指针
    } // ~D

    // 多态
    std::cout << "\n" "2) Runtime polymorphism demo\n";
    {
        // Create a derived resource and point to it via base type
        std::unique_ptr<B> p = std::make_unique<D>();
        // Dynamic dispatch works as expected
        p->bar();
        // p.reset(new B());
    }

    // 设置删除器
    std::cout << "\n" "3) Custom deleter demo\n";
    std::ofstream("demo.txt") << 'x'; // prepare the file to read
    {
        using unique_file_t = std::unique_ptr<std::FILE, decltype(&close_file)>;
        unique_file_t fp(std::fopen("demo.txt", "r"), &close_file);
        if (fp)
            std::cout << char(std::fgetc(fp.get())) << '\n';
    } // `close_file()` called here (if `fp` is not null)

    // 自定义删除器
    std::cout << "\n" "4) Custom lambda-expression deleter and exception safety demo\n";
    try
    {
        std::unique_ptr<D, void(*)(D*)> p(new D, [](D* ptr)
        {
            std::cout << "destroying from a custom deleter...\n";
            delete ptr;
        });
 
        throw std::runtime_error(""); // `p` would leak here if it were a plain pointer
    }
    catch (const std::exception&)
    {
        std::cout << "Caught exception\n";
    }

    std::cout << "\n" "5) Array form of unique_ptr demo\n";
    {
        std::unique_ptr<D[]> p(new D[3]);
    } // `D::~D()` is called 3 times

    std::cout << "\n" "6) Linked list demo\n";
    {
        List wall;
        const int enough{10};
        std::cout << "push " << enough << " nodes\n";
        for (int beer = 0; beer != enough; ++beer)
            wall.push(beer);
 
        // std::cout.imbue(std::locale("en_US.UTF-8"));
        std::cout << enough << " bottles of beer on the wall...\n";
    } // destroys all the beers
}