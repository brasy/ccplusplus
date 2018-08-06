#include <iostream>
#include <iterator>
using namespace std;

//new element of syntax
//1.nullptr, null pointer, not an integer
void foo(int) {cout<<"foo int"<<endl;}
void bar(int) {cout<<"bar int"<<endl;}
void bar(void *) {cout<<"bar void *"<<endl;}
void bar(nullptr_t) {cout<<"bar nullptr_t"<<endl;}

//2.raw string literals R"(..)"
std::string no_newlines=R"(\n\n)";
std::string cmd(R"(cd "d:\")");

//3.auto 初始化器推导类型,ref auto_elem.cpp

int main_test()
{
    int a2, b2, a3;
    int *c2 = &a2, *c3 = &a3, *d2 = &b2;
    std::cout << std::hex << c2 << " " << d2 << std::endl;
    std::cout << std::hex << std::distance(d2, c3) << std::endl;//std::distance返回的是迭代器的距离，而不是地址之差

    //1.nullptr
    foo(0); //call foo(int)
    foo(NULL); //call foo(int)
    //foo(nullptr); //compile fail
    bar(0);  //call bar(int)
    bar(NULL);  //call bar(int)
    bar(nullptr);  //call bar(nullptr_t)

    cout<<no_newlines<<cmd<<endl; //\n\ncd "d:\"

    return 0;
}

//enum
//enum默认类型是int，不允许隐私类型转换，必须使用cast；不同enum类型的对象之间不能比较，enum域必须前向声明
//The default type on which the enumeration is defined is int
//Scoped enums prevent from implicit type conversions, they convert to other types only with a cast
//It is not possible to compare objects of different enumeration types
//Scoped enums may always be forward-declared

enum class engin:char; //forward declaration
engin ee;
enum class engin:char{permit,disable,wait}; //enum element are in engin scope

int main_enum()
{
    ee = engin::permit;
    //ee = disable; //compile error, no disable in scope
    //ee = 2; //compile error
    ee = static_cast<engin>(2);
    //int index = engin::wait; //compile error
    cout<<static_cast<int>(ee)<<endl;

    return 0;
}

#include <array>
//constexpr常量表达式
/* 编译阶段就确认运行结果
 * 必须是int，float，enum泪痣
 * 不能有修改操作（+,?[],++）
 * 常函数
 * const初始化使用
 *
 * noexcepct ! say that this funcion is only SAFE!!
 * 如果noexcept函数抛出一个异常，程序立即终止
 */

constexpr int fconst(){return 0;}
//void swap(MyType &) noexcept;

int main_constex()
{
    constexpr int fconst1();
    constexpr bool b2 = noexcept(fconst());

    constexpr auto arraysize = 10;
    std::array<int,arraysize> data1;
    //If an exception will be throw from a noexcept function, the program immediately terminates

    int inum;
    //std::array<int,inum> data3; //编译阶段inum是未知的
    //constexpr auto arraysize2 = inum; //编译阶段inum是未知的
    const auto arraysize3 = inum;
    //std::array<int,arraysize3> data4; //编译阶段arraysize3不稳定

    return 0;
}
