#include <iostream>
using namespace std;

template<typename T>
void Swap(T& a, T& b)
{
    T temp = a;
    b=a;
    a = temp;
}
int main()
{
    return 0;
}
