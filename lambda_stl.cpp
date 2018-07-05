//lambda 表达式
//[capture_block](parameter) mutable exception_specification -> return_type {body}
//捕捉块(capture block):指定如何捕捉所在作用域中的变量，并供给lambda主体部分使用。
/* 参数(parameter):(可选)lambda表达式使用的参数列表。只有在不需要任何参数并且没有指定mutable、一个exception_specification和一个return_type的情况下可以忽略该列表。
 * 参数列表和普通函数的参数列表类似，区别如下:
 * 参数不能有默认值
 * 不允许变长参数列表
 * 不允许未命名的参数
*/
//mutable:(可选)如果所在作用域中的变量是通过值捕捉的，那么lambda表达式主体中可以使用这些变量的副本。这些副本默认标记为const，因此lambda表达式主体不能修改这些副本的值。
//如果lambda表达式标记为mutable，那么这些副本则不是const，因此主体可以修改这些本地副本。
//exception_specification:(可选)用于指定lambda表达式可以抛出的异常。
/* return_type:(可选)返回值的类型。如果忽略了return_type，那么编译器会根据以下原则判断返回类型:
 * 如果lambda表达式主体的形式为{ return expression;}，那么lambda表达式的return_type为expression的类型。
 * 其他情况下的return_type为void
 *
 * lambda表达式最后如果加()小括号,则表示立即执行, 类似普通函数func(),这时候的返回值就是函数返回值了
*/
#include <iostream>
#include <vector>
#include <functional>
using namespace std;


int lambdaBegin()
{
    []{cout<<"hello lambda"<<endl;}(); //()小括号保证立即执行
    string result = [](const string& str) -> string {return "hello " + str;} ("second lambda");
    cout<<result<<endl; //函数返回值
    auto funcptr = [](const string& str) -> string {return "hello " + str;};
    cout<<funcptr("call input")<<endl; //函数调用
}

//捕捉块
/* 两种方式来捕捉所在作用域中的所有变量:
 * [=]通过值捕捉所有变量
 * [&]通过引用捕捉所有变量
 * 空白的捕捉块[]表示不从所在作用域中捕捉变量
 *
 * [&x]只通过引用捕捉x，不捕捉其他变量
 * [x]只通过值捕捉x，不捕捉其他变量
 * [=,&x, &y]默认通过值捕捉，变量x和y是例外，这两个变量通过引用捕捉
 * [&, x]默认通过引用捕捉，变量x是例外，这个变量通过值捕捉
 * [&x, &x]非法，因为标识符不允许重复
 * 通过引用捕捉变量的时候，一定要保证当lambda表达式在执行的时候这个引用还是可用的
*/
int main_capture()
{
    int x = 2;
    int y = 3;
    auto f =[x, &y](){ return x * y; };
    cout << f() << '\n'; //2*3=6
    x = 5; y = 7;
    cout << f() << '\n'; //2*7=14
    return 0;
}

//lambda表达式用作返回值
/* <functional>
 * 函数命名：function<int(void)> functionname(){}
 * 返回值method1 : return [=/&]{return something;}
 * 返回值method2 : return [=]()->int{return something;};
*/

//lambda is used as return
function<double(int,int)> myWrapper;
function<int(void)> multipByLambda(int x)
{
    cout<<"multipByLambda"<<endl;
    //return [=]()->int{return 2*x;}; //method 1
    return [=]{return 2*x;}; //method 2
}
//这段代码不能正常工作,lambda表达式通过引用捕捉变量x。然而，lambda表达式会在程序后面执行，而不会在multiplyBy2Lambda()函数的作用域中执行，
function<int(void)> multipByLambda2(int x)
{
    cout<<"multipByLambda 2"<<endl;
    return [&]{return 2*x;}; //method 3 // fail
}

int lambdaAsReturn()
{
    function<int(void)> fn1 = multipByLambda(6); //call method 1
    auto fn2 = multipByLambda(3); //call method 2
    auto fn3 = multipByLambda2(90); //call method 3
    cout<<fn1()<<endl<<fn2()<<endl;
    return 0;
}

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
