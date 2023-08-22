#include <iostream>
using namespace std;

class MATX
{
public:
    MATX()
    {
        cout << "MATX::MATX()" << endl;
    }
};
class MBTX
{
public:
    int m_i;
    int m_j;
    MATX m_a;
    void funcj()
    {
        cout << "IAmVeryGood" << endl;
    }
};

int main()
{
    // “合成默认的构造函数”，只有在必要的时候，编译器才会为我们合成出来，而不是必然或者必须为我们合成出来。
    // 该类MBTX没有任何构造函数，但包含一个类类型（MATX）的成员变量m_a，所以编译器会为我们合成出一个默认的构造函数。
    MBTX mby;

	return 0;
}