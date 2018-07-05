//STL算法和lambda表达式结合使用
/* count_if()算法计算给定vector中满足特定条件的元素个数;
 * 1.lambda表达式的形式给出条件，通过值[=]捕捉所在作用域中的变量
 * 如果捕捉子句为空，即[]，那么在lambda表达式的主体内就无法访问变量值了
 * 2.按引用捕捉的一个变量，来计算lambda被调用的次数
 *
 * generate()算法可以通过特定值填充一个迭代器范围
 * for_each()算法可以对给定范围中的所有元素执行特定操作
*/
#include <iostream>
using namespace std;
#include <ctype.h>
#include <algorithm>

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
  
    std::string str = "djwoJ*FALInxk.lfDF232Dg";
    std::transform(str.begin(),str.end(),str.begin(),[](char x){return std::tolower(x);});
    cout<<str<<endl;

    std::transform(str.begin(),str.end(),str.begin(),::toupper);
    cout<<str<<endl;
}

//lambda和inline区别
//lambda 本身编译器会生成一个函数对象strunc fn{..operator(.)..}
//而inline 是没有函数的地址的
