//Motivation:移动语义，增强性能，资源拥有者转换并且不需要copy
//Performance Optimalization
//Possibility to implement objects that should not be copied, but allow transfer of ownership to the resource

// C++ 11 introduce : 左值（对象有一个名字，可以获取地址），右值（地址不可得，通常是未命名的临时对象，转换状态但是未定义状态）
/* lvalue
 * object has a name
 * could get address of object
//rvalue
 * the address can not be retrieved
 * usually an unnamed temporary object( e.g. returned from function)
 * from rvalue we can transfer state leaving it in a correct, but undefined state
*/
#include <iostream>
using namespace std;

std::string foo(std::string str) // foo and str are lvalues
{
    return str;
} // foo's return is rvalue
void incr(int& a) { ++a; } //incr and 入参a 都是 lvalue

//右值引用
//&&暗示右值引用，右值引用可以绑定一个右值，但是不能绑定左值
//右值引用必须初始化，并且不能改变绑定
//右值引用暗示操作都是指向move
//函数和入参都是左值，函数返回值是左值

template <typename T>
class vector
{
public:
    void push_back(const T& item){std::cout<<"this is const copy cons"<<std::endl;} //拷贝item
    void push_back(T& item){std::cout<<"this is copy cons"<<std::endl;} //拷贝item
    void push_back(T&& item){std::cout<<"this is move cons"<<std::endl;}  //move rvalue item to container
};

void create_and_inset(vector<std::string>& coll)
{
    std::string str = "string";
    coll.push_back(str); // insert a copy of str str is used later

    coll.push_back(str+str); //rvalue binds to //push_back(string&&) temp is moved into container
    coll.push_back("str+str"); //rvalue binds to //push_back(string&&) tries to move temporary object
    coll.push_back(std::move(str));  // tries to move str object into container str is no longer used
}

//右值引用可以被绑定到const 左值引用，即上面所有右值都可以绑定到push_back(const T& item)
//左值不能绑定到右值引用，即上面coll.push_back(str)不能绑到push_back(T&& item)
//右值不能绑定到非const 限定的左值引用, 即当没有push_back(T&& item)的时候，右值的只会调push_back(const T& item)
//左值引用不能被绑定到const左值引用

int move()
{
    double dx;
    double* ptr; // dx and ptr are lvalues

    foo("Hello"); // temp string created for call is rvalue

    int&& rv =1;
    int i=1;
    //int&& rv2 = i; //error, i是左值，不能绑到rv2右值上
    incr(i);
    //incr(1); //error, 1不是左值,是右值
    vector<std::string> coll;
    create_and_inset(coll);

    return 0;
}
