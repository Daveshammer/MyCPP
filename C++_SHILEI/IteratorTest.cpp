#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> vec;
    for (int i = 0; i < 20; i ++)
    {
        vec.push_back(i);
    }
    auto it1 = vec.end();
    vec.pop_back();
    auto it2 = vec.end();
    cout << *it1 << endl;
    cout << *it2 << endl;

    return 0;
}