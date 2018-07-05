
//lambda表达式用作返回值
/* <functional>
 * 函数命名：function<int(void)> functionname(){}
 * 返回值method1 : return [=/&]{return something;}
 * 返回值method2 : return [=]()->int{return something;};
*/
#include <iostream>
#include <functional>
using namespace std;

//lambda is used as return
function<double(int,int)> myWrapper;
function<int(void)> multipByLambda(int x)
{
    cout<<"multipByLambda"<<endl;
    //return [=]()->int{return 2*x;}; //method 1
    return [=]{return 2*x;}; //method 2
}

//这段代码不能正常工作,lambda表达式通过引用捕捉变量x。
//然而，lambda表达式会在程序后面执行，而不会在multiplyBy2Lambda()函数的作用域中执行，
function<int(void)> multipByLambda2(int x)
{
    cout<<"multipByLambda 2"<<endl;
    return [&]{return 2*x;}; //method 3
}

int lambdaAsReturn()
{
    function<int(void)> fn1 = multipByLambda(6); //call method 1
    auto fn2 = multipByLambda(3); //call method 2
    auto fn3 = multipByLambda2(90); //call method 3
    cout<<fn1()<<endl<<fn2()<<endl;
    return 0;
}
