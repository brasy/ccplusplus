
/* 调用拷贝构造函数：
 * Example2(const Example2& x)
 *
 * 1一个对象以值传递的方式传入函数体
 * 2一个对象以值传递的方式从函数返回
 * 3一个对象需要通过另外一个对象进行初始化
 *
 * 类中没有显式地声明一个拷贝构造函数，编译器自动生成一个默认的拷贝构造函数，完成对象之间的位拷贝/浅拷贝
 * 如果一个类拥有资源，当类的对象发生复制时，资源重新分配，这个过程就是深拷贝，反之，没有重新分配资源，就是浅拷贝
 * 自定义拷贝构造函数是一种良好的编程风格，它可以阻止编译器形成默认的拷贝构造函数，提高源码效率。
 * 深拷好还是浅拷好？
 * 如果实行位拷贝，也就是把对象里的值完全复制给另一个对象，如A=B。这时，如果B中有一个成员变量指针已经申请了内存，那A中的那个成员变量也指向同一块内存。这就出现了问题：当B把内存释放了（如：析构），这时A内的指针就是野指针了，出现运行错误。
 */
// 拷贝构造函数: 深复制

//对象的拷贝复制操作是操作符“=“的一种重载形式。返回值是*this指针的引用
//Example2& operator= (const Example2& x)
//同拷贝构造，编译器自动生成的拷贝赋值也是浅拷贝，自定义更好，避免内存泄漏。

class Example2 {
    string* ptr;
public:
    Example2(const string& str):ptr(new string(str)){cout<<"cons \n";}
    ~Example2() {delete ptr;}

    // 拷贝构造函数:
    Example2(const Example2& x):ptr(new string(x.content())) {cout<<"copy cons \n";}

    Example2& operator= (const Example2& x) {
        delete ptr;    // 删除现在指向的字符串
        // 为新字符串分配存储空间，并拷贝
        ptr = new string (x.content());
        cout<<"copy oper \n";
        return *this;
    }

    // 访问类的字符串:
    const string& content() const {return *ptr;}
};

int main_copy_oper()
{
  Example2 foo ("Example");  //cons
  Example2 bar = foo;  //copy cons
  bar = foo; //copy oper
  cout << "bar's content: " << bar.content() << '\n';
  return 0;
}



//移动构造函数和移动赋值的语法，它们的返回类型都是class类自身。
/* MyClass (MyClass&&);             // move-constructor, 对比拷贝构造没有const
 * MyClass& operator= (MyClass&&);  // move-assignment
 */

class Example3 {
    string* ptr;
public:
    Example3 (const string& str) : ptr(new string(str)) {cout<<"cons \n";}
    ~Example3 () {delete ptr;}
    // 移动构造函数，参数x不能是const Pointer&& x, 因为要改变x的成员数据的值；
    // C++98不支持，C++1x（C++11）支持
    Example3 (Example3&& x) : ptr(x.ptr)  { x.ptr = nullptr; cout<<"move cons \n";}
    // move assignment
    Example3& operator= (Example3&& x)
    {
        delete ptr;
        ptr = x.ptr;
        x.ptr=nullptr;
        cout<<"move oper \n";
        return *this;
    }
    // access content:
    const string& content() const {return *ptr;}
    // addition:
    Example3 operator+(const Example3& rhs)
    {
        cout<<"+ oper \n";
        return Example3(content()+rhs.content());
    }
};
int main_move_oper ()
{
    Example3 foo("Exam");           // 构造函数
    Example3 bar = std::move(Example3("ple")); // 移动构造函数
    foo = foo + bar;                // +oper, cons,移动赋值
    cout << "foo's content: " << foo.content() << '\n';
    return 0;
}
//关键字default定义的成员函数不等于默认构造函数

