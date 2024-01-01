#include <iostream>
using namespace std;

class GGbonds
{
public:
    template <typename T>
    GGbonds(T a)
    {
        cout << "a:" << a << endl;
    }
    template <typename T>
    void show(T b)
    {
        cout << "b:" << b << endl;
    }

    // virtual void show2(T c)
    // {
    //     cout << "c:" << c << endl;
    // }
};
int main()
{
    GGbonds g("蜘蛛侠");
    g.show(3);
    return 0;
}
