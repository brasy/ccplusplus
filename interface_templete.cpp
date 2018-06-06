//use interface
struct AInterface
{
    virtual void f() = 0;
};

struct A : public AInterface
{
    void f(){std::cout<<"A::f()"<<std::endl;}
};

struct UseAInterface
{
    UseAInterface(AInterface* a) : _a(a){std::cout<<"UseAInterface::f() cont"<<std::endl;}
    void f(){_a->f();std::cout<<"UseAInterface::f()"<<std::endl;}

    AInterface* _a;
};

//use templates
struct B
{
    void f(){std::cout<<"B::f()"<<std::endl;}
};

template<class T>
struct UseB
{
    UseB(T* a) : _a(a){std::cout<<"UseB::f() cont"<<std::endl;}
    void f(){_a->f();std::cout<<"UseB::f()"<<std::endl;}

    T* _a;
};

extern bool ComFunc(void);

int main(int argc, char *argv[])
{
    A ai;
    ai.f(); //A::f()
    UseAInterface a(&ai);//UseAInterface::f() cont
    a.f();//A::f(), UseAInterface::f()

    B bi;
    bi.f();//B::f()

    int in = 2;
    UseB<int> b(&in);//UseB::f() cont
    std::cout << *(b._a)<<std::endl; //2

    UseB<bool()> b1(ComFunc); //UseB::f() cont
    std::cout << !(b1._a)<<std::endl; //false

    UseB<B> b2(&bi); //UseB::f() cont
    b2.f();//B::f(), UseB::f()

    return 0;
}

