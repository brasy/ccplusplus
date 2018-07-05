//lambda is used as input parameter
/* 实现回调函数 <functional>
 * 函数入参： const function<bool(int)>& callback
 * 使用入参： callback(inputparam)
 * 调用函数：[](inputParam){return something;}
 * <algorithm>
 * generate()算法要求传入一个迭代器范围，并将这个范围内的值替换为第3个参数传入的函数的返回值, 生成vector
 * for_each()算法对给定迭代器范围中的每个值调用第3个参数传入的函数
*/
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
int main_lamCl()
{
    LambdaClass lamObj;
    lamObj.callLambda(2);
    lamObj.callLambda();
    lamObj.callLambda([&]()->string{return "filepaths: d:/";});
}

//STL算法和lambda表达式结合使用
/* count_if()算法计算给定vector中满足特定条件的元素个数;
 * 1.lambda表达式的形式给出条件，通过值[=]捕捉所在作用域中的变量
 * 如果捕捉子句为空，即[]，那么在lambda表达式的主体内就无法访问变量值了
 * 2.按引用捕捉的一个变量，来计算lambda被调用的次数
 *
 * generate()算法可以通过特定值填充一个迭代器范围
 * for_each()算法可以对给定范围中的所有元素执行特定操作
*/
int main_stlfunc()
{
    vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    int callnumbers = 0;
    int cnt = count_if(vec.begin(), vec.end(), [=](int x){return x>3;});
    int cnt2 = count_if(vec.begin(), vec.end(), [=,&callnumbers](int x)->bool{++callnumbers;return x>5;});
    cout<<"count_if match "<<cnt<<" numbers."<<endl;
    cout<<"call lambda " <<callnumbers<<" to match "<<cnt2<<endl;

    vector<int> vecdyn(10);
    int value=0;
    generate(vecdyn.begin(), vecdyn.end(), [&value]{value*=2; return ++value;});
    int index=0;
    for_each(vecdyn.begin(), vecdyn.end(), [&index](int i){cout<<"["<<(index++)
                                                              <<"]:"<<i<< " ";});
    cout << endl;
}

//lambda和inline区别
//lambda 本身编译器会生成一个函数对象strunc fn{..operator(.)..}
//而inline 是没有函数的地址的
