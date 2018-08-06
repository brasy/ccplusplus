//using, 更可读的类型别名
//using  - more readable aliases of type than typedef
#include <map>
#include <iostream>
using namespace std;

using carId = int;
using funcs=int(*)(double,double);
using dirctorDesc = std::map<std::string,std::string,std::greater<std::string>>;

template<typename T>
using StrKeyMap = std::map<std::string, T>;
StrKeyMap<int> my_map; //std::map<std::string,int>

template<std::size_t N>
using StrArray = std::array<std::string,N>;
StrArray<4> arr1; //std::array<std::string,4>

int main_emplace()
{
    my_map.emplace(std::make_pair("3", 4));
    cout<<my_map["3"]<<endl;
    cout<<sizeof(arr1)<<endl;
    return 0;
}
