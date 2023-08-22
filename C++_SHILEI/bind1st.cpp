#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

template<typename Container>
void showContainer(Container &con)
{
    typename Container::iterator it = con.begin();
    for (; it != con.end(); ++ it)
    {
        cout << *it << " ";
    }
    cout << endl;
}

template<typename Iterator, typename Compare>
Iterator my_find_if(Iterator first, Iterator last, Compare comp) 
{
    for (; first != last; ++ first) // 4
    {
        if (comp(*first)) // 6
        {
            return first;
        }
    }
    return last;
}

template<typename Compare, typename T>
class _mybind1st
{
public:
    _mybind1st(Compare comp, const T &val)
        : _comp(comp), _val(val) // 2
    {
    }
    bool operator()(const T &second)
    {
        // second就是my_find_if中的*first
        return _comp(_val, second); // 7
    }
private:
    Compare _comp;
    T _val;
};

// mybind1st(greater<int>(), 70)
template<typename Compare, typename T>
_mybind1st<Compare, T> mybind1st(Compare comp, const T &val)
{
    // 直接使用函数模板，好处是，可以进行类型的推演
    return _mybind1st<Compare, T>(comp, val); // 1
} // 3

int main()
{
    vector<int> vec;
    srand(time(nullptr));
    for (int i = 0; i < 20; ++ i) 
    {
        vec.push_back(rand() % 100 + 1);
    }
    showContainer(vec);
    sort(vec.begin(), vec.end(), greater<int>()); // sort in descending order
    showContainer(vec);

    // 把70按顺序插入到vec容器中    找第一个小于70的数字
    // 绑定器 + 二元函数对象 = 一元函数对象
    // std::vector<int>::iterator my_find_if<std::vector<int>::iterator, _mybind1st<std::greater<int>, int>>(std::vector<int>::iterator first, std::vector<int>::iterator last, _mybind1st<std::greater<int>, int> comp)
    // _mybind1st<std::greater<int>, int> mybind1st<std::greater<int>, int>(std::greater<int> comp, const int &val)
    auto it1 = my_find_if(vec.begin(), vec.end(), mybind1st(greater<int>(), 70));
    if (it1 != vec.end())
    {
        vec.insert(it1, 70);
    }
    showContainer(vec);

    return 0;
}