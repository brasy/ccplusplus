#include <iostream>
#include <iterator>
using namespace std;

//std::distance返回的是迭代器的距离，而不是地址之差

void iteratorDistance()
{
    int a2, b2, a3;
    int *c2 = &a2, *c3 = &a3, *d2 = &b2;
    std::cout << std::hex << c2 << " " << d2 << std::endl;
    std::cout << std::hex << std::distance(d2, c3) << std::endl;
}
