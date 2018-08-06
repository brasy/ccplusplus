//#include "transform.hpp" C++算法库都是这种写法，分离接口和算法实现
/* <algorithm>
 * 一元运算, 第三个入参是运算结果, 返回值_OutIter
 * template<typename _IIter, typename _OutIter, typename _UnaryOperation>
 *   _OutIter
 * transform(_IIter, _IIter, _OutIter, _UnaryOperation);
 *
 * 二元运算, 第四个是运算结果, 返回值_OutIter
 * template<typename _IIter1, typename _IIter2, typename _OutIter, typename _BinaryOperation>
 *   _OutIter
 * transform(_IIter1, _IIter1, _IIter2, _OutIter, _BinaryOperation);
 *
 * reference: http://en.cppreference.com/w/cpp/algorithm/transform
 *
 * std::for_each: ignores the return value of the function, guarantees execution order.
 * std::transform: assigns the return value to the iterator, donot guarantee execution order.
*/

#include <algorithm> // std::transform
#include <cctype> // std::toupper c++11
#include <functional> // std::plus c++14
#include <string>
#include <vector>
//back_inserter(_Container& __x)
#include <iostream>
using namespace std;

#include "boost/range/adaptor/transformed.hpp"


int main_transform()
{
    string str = "djwoJ*FALInxk.lfDF232Dg";
    transform(str.begin(),str.end(),str.begin(),[](char x){return tolower(x);});
    cout<<str<<endl;

    //有返回值
    transform(str.begin(),str.end(),str.begin(),::toupper);
    cout<<str<<endl;

    //没有返回值
    for_each(str.begin(), str.end(), [](char c) {tolower(c);});
    cout<<str<<endl;

    //vector + transform
    vector<string> vecStr = {"How", "are", "you!"};
    vector<size_t> strSize;
    transform(vecStr.begin(), vecStr.end(), back_inserter(strSize),[](string s){return s.size();});
    for(auto value : strSize)
        cout<<value<<" ";
    cout <<endl;

    //binary transform
    vector<int> vecIn;
    vector<int> vecOut;

    for (int i = 1; i<6; i++)
            vecIn.push_back(i * 10);
    vecOut.resize(vecIn.size()); // allocate

    transform(vecIn.begin(), vecIn.end(), vecOut.begin(), [](int i){return ++i;});
    transform(vecIn.begin(), vecIn.end(), vecOut.begin(), vecIn.begin(), plus<int>());

    cout << "vecIn contains:";
    for (vector<int>::iterator it = vecIn.begin(); it != vecIn.end(); ++it)
        cout <<*it<<" ";

    cout <<endl<< "vecOut contains:";
    for (auto i : vecOut)
        cout<<i<< " ";
    cout<<endl;

    //old methods
    char c;
    int i=0;
    while (str[i]) {
        c=std::tolower(str[i]);
        cout<<c<<" ";
        i++;
    }
    cout<<endl;
    //new method
    std::transform(str.begin(),str.end(),str.begin(),(int(*) (int))std::tolower);
    cout<<str<<endl;
    int(*fn)(int) = std::toupper;
    std::transform(str.begin(),str.end(),str.begin(),fn);
    cout<<str<<endl;

    std::transform(str.begin(),str.end(),str.begin(),[](char x){return std::tolower(x);});
    cout<<str<<endl;

    std::transform(str.begin(),str.end(),str.begin(),::toupper);
    cout<<str<<endl;

    const auto transformT = boost::adaptors::transformed([](const auto& x){return std::tolower(x); });

    return 0;
}
