#include <iostream>
using namespace std;
double func(int a, double b, const char *c, float d, short e, long f)
{
    cout << "a= " << a << " b= " << c << " c= " << d << " d= " << b << "e= " << e << " f= " << f << endl;
    return 5.5;
}
int main()
{
    double (*pf1)(int a, double b, const char *c, float d, short e, long f); // 声明函数指针
    pf1 = func;
    pf1(1, 2, "西施", 3, 4, 5);
    auto pf2 = func; //使用auto变量
    pf1(1, 2, "西施", 3, 4, 5);
    return 0;
}
