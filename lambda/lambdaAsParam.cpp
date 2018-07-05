//lambda is used as input parameter
/* 实现回调函数 <functional>
 * 函数入参： const function<bool(int)>& callback
 * 使用入参： callback(inputparam)
 * 调用函数：[](inputParam){return something;}
 * <algorithm>
 * generate()算法要求传入一个迭代器范围，并将这个范围内的值替换为第3个参数传入的函数的返回值, 生成vector
 * for_each()算法对给定迭代器范围中的每个值调用第3个参数传入的函数
*/

#include <iostream>
#include <vector>
#include <functional>
using namespace std;


void testCallback(const vector<int>& vec,
                  const function<bool(int)>& callback)
{
    // Using range-based for loop
    for(auto i : vec){
        if(!callback(i))
            continue;
        cout<<i<<" ";
    }
    cout << endl;
}

#include <algorithm>
int main_inparam()
{
    vector<int> vec = {1,2,3,4,5};
    testCallback(vec, [](int x){return x>2;});

    vector<int> vecdyn(10);
    int index = 0;
    generate(vecdyn.begin(), vecdyn.end(), [&index]{return ++index;});
    for_each(vecdyn.begin(), vecdyn.end(), [](int i){cout << i << " ";});
    cout << endl;
    testCallback(vecdyn,[](int x){return x>6;});
    return 0;
}

//example 2
std::string getStr()
{
    return "filepaths: default c:/";
}
class LambdaClass
{
    using TCallback = std::function<bool(int &)>;
public:
    LambdaClass() = default;
    void callLambda(int d);
    void callLambda(std::function<std::string()> = getStr);
private:
    void testClassCallback(const vector<int>&, const TCallback&callFn);
};
void LambdaClass::testClassCallback(const vector<int> &vec, const TCallback& callFn)
{
    // Using range-based for loop
    for(auto i : vec){
        if(!callFn(i))
            continue;
        cout<<i<<" ";
    }
    cout << endl;
}
void LambdaClass::callLambda(int d)
{
    cout<<"callLambda int "<<d<<endl;
}
void LambdaClass::callLambda(std::function<string()> getString)
{
    cout<<getString()<<endl;
    auto funcptr = [this](int& p){return p>5;};
    vector<int> vec = {1,5,6,9,4};
    testClassCallback(vec,funcptr);
}
void main_lamCl()
{
    LambdaClass lamObj;
    lamObj.callLambda(2);
    lamObj.callLambda();
    lamObj.callLambda([&]()->string{return "filepaths: d:/";});
}
