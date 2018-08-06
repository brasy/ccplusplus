//range-based for loop
/* allows you to iterate through a “range”,
 * which is anything you can iterate through like an STL-sequence defined by a begin() and end().
 * It is compatible with:
 * All standard containers can be used as a range,
 * a std::string, native C-arrays
 * an initializer list,
 * an array,
 * anything for which you define begin() and end(), e.g. an istream
 */
// for范围循环，使用迭代的begin()/end()
//类似begin()/end()定义的STL序列
//所有标准容器，字符串，数组，初始化列表，istream等等，只要定义了begin()/end()，都可以使用这样的语法for范围循环。
//循环中cp元素会降低性能(string, shared_ptr)，或者不允许(unique_ptr)
#include <vector>
#include <iostream>
using namespace std;

void f_range(vector<int>& v){
    for(auto x:v)cout<<x<<" ";
    cout<<endl;
    for(auto& x:v)++x;
    for(auto x:v)cout<<x<<" ";
    cout<<endl;
}
int main_range()
{
    for(const auto x:{1,2,33,24,5,61,7,48,94})cout<<x<<" "; //初始化列表数据/数组可以使用for
    cout<<endl;
    vector<int> vec = {34,42,13,5,62,2};
    for(int item:vec)cout<<item<<" "; //vector可以使用
    cout<<endl;
    for(int& item:vec)item*=2;  //还可以增加其他操作
    f_range(vec);
    return 0;
}
