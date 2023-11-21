#include <iostream>
#include <deque>

using namespace std;

template<typename T, typename Container=deque<T>>
class Stack
{
public:
    void push(const T &val) { _con.push_back(val); }
    void pop() { _con.pop_back(); }
    T top() const { return _con.back(); }
    bool empty() const { return _con.empty(); }
private:
    Container _con; // 相当于代理模式
};

int main()
{
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    return 0;
}