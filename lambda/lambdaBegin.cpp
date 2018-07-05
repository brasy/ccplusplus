#include <iostream>
using namespace std;
//捕捉块
/* 两种方式来捕捉所在作用域中的所有变量:
 * [=]通过值捕捉所有变量
 * [&]通过引用捕捉所有变量
 * 空白的捕捉块[]表示不从所在作用域中捕捉变量
*/

int lambdaBegin()
{
    []{cout<<"hello lambda"<<endl;}(); //()小括号保证立即执行
    string result = [](const string& str) -> string {return "hello " + str;} ("second lambda");
    cout<<result<<endl; //函数返回值
    auto funcptr = [](const string& str) -> string {return "hello " + str;};
    cout<<funcptr("call input")<<endl; //函数调用

    //捕捉值和捕捉引用差异
    int x = 2;
    int y = 3;
    auto f =[x, &y](){ return x * y; };
    cout << f() << '\n'; //2*3=6
    x = 5; y = 7;
    cout << f() << '\n'; //2*7=14  
    return 0;
}
