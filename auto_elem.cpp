#include <iostream>
#include <vector>
#include <map>
using namespace std;

//3.auto 初始化器推导类型
//auto允许两种初始化语法
//direct initialization  (= or () )
//copying syntax (class)

int i;
const auto* ptr_i = &i;
double f(){};
auto r1=f(); //r1: double
const auto& r2=f(); //r2: const double&
#include <set>
std::set<std::string> spellcheck;
const auto& ref_spellcheck = spellcheck; // const std::set<std::string>&

//copu initialization syntax
struct expl{
    expl(){}
    explicit expl(const expl&){} //明确的
};
expl e;
//auto c=e; //compile error, should be c(e)

template<class T> void printall(const vector<T>& v)
{
    for(auto p=v.begin(); p!=v.end(); ++p)
    {
        cout<<*p<<endl;
    }
}

template<class T,class U> void multiply(const vector<T>& vt, const vector<U>& vu)
{
    auto tmp = vt[i]*vu(i);
}

void do_something(int& x){}
void print(const int& x){}

void autoIter(){
    vector<int> vec = {1,2,3,4,5};
    for(auto it = vec.begin(); it!=vec.end(); ++it)
    {
        do_something(*it); //type of it - vector<int>::iterator
    }
    for(auto its = vec.cbegin(); its!=vec.cend(); ++its)
    {
        print(*its); //type of its - vector<int>::const_iterator
    }
}

//auto-deduction mechanism
//practically the same as for template parameters,区别是初始化列表定义不同
int func(double){return 10;}
auto f1 = func; //f1 : int(*)(double)
auto& f2 = func; //f2 : int(&)(double)

int main_auto()
{
    cout<<f1(2)<<endl<<f2(3.3)<<endl;
    return 0;
}

// decltype
template<typename T, typename U>
auto product(const T &t, const U &u) -> decltype (t * u)
{ return t * u; }
