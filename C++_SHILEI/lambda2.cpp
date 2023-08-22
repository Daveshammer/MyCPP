#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

class Data
{
public:
    Data(int val1 = 10, int val2 = 20) : a(val1), b(val2) {}

    int a;
    int b;
};

int main()
{
    using FUNC = function<bool(Data&, Data&)>;
    priority_queue<Data, vector<Data>, FUNC> pq(
        [](Data& d1, Data& d2) -> bool { return d1.a < d2.a; }
    );
    pq.push(Data(10, 20));
    pq.push(Data(20, 10));
    pq.push(Data(30, 30));

    while (!pq.empty())
    {
        cout << pq.top().a << " " << pq.top().b << endl;
        pq.pop();
    }

    return 0;
}