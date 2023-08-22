#include<iostream>
#include<vector>
using namespace std;

int main()
{
    vector<int> vec;
    for (int i = 0; i < 20; i ++) vec.push_back(rand() % 100);

    auto it = vec.begin();
    while (it != vec.end()) //迭代器失效问题(erase, insert)
    {
        if (*it % 2 == 0) 
        {
            it = vec.erase(it);
            // ++ it; //迭代器失效，不能++
        }
        else
        {
            ++ it;
        }
    }

#if 0
    auto it = vec.begin();
    while (it != vec.end()) //迭代器失效问题(erase, insert)
    {
        if (*it % 2 == 0) vec.erase(it);
        ++it;
    }
#endif

    for (auto &e : vec) cout << e << " ";

    return 0;
}