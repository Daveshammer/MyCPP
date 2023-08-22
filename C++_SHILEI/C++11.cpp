#include <iostream>
using namespace std;

/*
C++11 标准相关的内容 总结一下
一：关键字和语法
auto：可以根据右值，推导出右值的类型，然后左边变量的类型也就确定了
nullptr：给指针专用（能够和整数进行区分） #define NULL 0
foreach：可以遍历数组，容器等
for (Type Val : container) => 底层就是通过指针或者迭代器来实现的
右值引用：move语义函数和forward类型完美转发函数
模板的一个新特性：typename... A 表示可变参（类型参数）

二：绑定器和函数对象
function：函数对象
bind：绑定器    bind1st和bind2nd + 二元函数对象 =》 一元函数对象

三：智能指针
shared_ptr和weak_ptr

四：容器
set和map：红黑树 O(logN)
unordered_set和unordered_map：哈希表 O(1)
array：数组 vector
forward_list：单向链表 list
*/

int main()
{

    return 0;
}