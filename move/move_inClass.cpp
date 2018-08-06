//在c++11中,定义Example类，c++编译系统将为Example类生成如下默认操作函数：
/* 1. 默认构造函数Example();
 * 2. 拷贝构造函数Example(const Example&);
 * 3. 拷贝赋值函数Example & operator=(const Example &);
 * 4. 移动构造函数Example(Example &&);
 * 5. 移动赋值函数Example & operator=(Example &&);
 * 6. 析构函数~Example();
 * Move function not move reference
*/
class Example
{
};
class MoveCl
{
public:
    MoveCl(){cout<<"constructor..............."<<endl;}
    MoveCl& operator = (MoveCl&&) {cout<<"move operator"<<endl;}
    MoveCl(const MoveCl&&){cout<<"move construct "<<endl;}

    MoveCl& operator = (const MoveCl&){cout<<"copy operator"<<endl;}
    MoveCl(const MoveCl&){cout<<"copy construct"<<endl;}
    ~MoveCl(){cout<<"destructor "<<endl;}
};

int processCons()
{
    MoveCl m1 = MoveCl(); //constructor
    MoveCl m3(m1); //copy construct

    MoveCl&& m5=MoveCl(); //constructor
    MoveCl m6=std::move(MoveCl()); //constructor, move construct, destructor
    m6=MoveCl(); //constructor, move operator, destructor
    m6=m5; //copy operator
    m6=std::move(m1); //move operator
    cout<<endl;
    return 0;
}
