#include <iostream>
using namespace std;

//initlizer
//使用{}-initializer lists 实现所有初始化
//可以对构造函数初始化列表，初始化动态数组
//c++11不允许使用对隐形转换使用背带初始化，因为会导致type变窄

#include <vector>
#include <array>
int var1{1};
const int var2{10};
std::vector<std::string> cities = {"beijing","shanghai"};

class s{
public:
    s(int x,int y, int z):a{x,y,z}{
        for(int i:a)
            cout<<i<<" ";
        cout<<endl;
    }
    s(int x, int y):x_{x},y_{y}{cout<<"class s: "<<x_<<" "<<y_<<endl;}
private:
    int a[3];
    int x_, y_;
};

int *buffer = new int[5] {1,3,-1,1+1,0};

std::array<int,3> arr_int = {1,3,6};

//std::initializer_list 初始化列表,在C++11中，可以用于初始化任何用户类型
/* 可用于数组，接收{}的函数
 * std::initializer_list<T>.
 * 1.所有元素必须是模板类型T，或者可转成T
 * 2.直接初始化和copy初始化不同由{}管
 */
void func_ini(initializer_list<int>){}
void func_const(const vector<double>&){}

int main_init()
{
    cout<<*(buffer+3)<<endl<<arr_int[2]<<endl;

    s vec1 {10,20};
    s vec2 {1,2,3};

    func_ini({});
    func_ini({23,45,1,4});

    vector<double> vd1(6);
    //vd1=7; //no convertible from int to vector
    //vector<double> vd2 = 8; //no convertible from int to vector
    vector<double> vd3{6};
    vd3={7};
    //func_const(9); //no convertible from int to vector
    func_const({9});


    return 0;
}
