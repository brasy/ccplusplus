#include "string.h"
//move效率测试
class Example4
{
    string *str;
public:
    Example4() : str(new string("")) {}
    Example4 (const string& istr) : str(new string(istr)) {}
    ~Example4 () {delete str;}

    Example4 (const Example4& x):str(new string(x.content())){/*cout<<"copy cons \n";*/}
    Example4 (Example4&& x) : str(x.str)  { x.str = nullptr; /*cout<<"move cons \n";*/}

    Example4& operator= (const Example4& x){
        if(this != &x){
            delete str;
            str = new string(x.content());
        }
        //cout<<"copy oper \n";
        return *this;
    }
    Example4& operator= (Example4&& x) {
        if(this != &x){
            delete str;
            str = x.str;
            x.str = nullptr;
        }
        //cout<<"move oper \n";
        return *this;
    }

    const string& content() const {return *str;}
};

#include<windows.h>
#define STDMOVE 1

int main_compareCopyWithMove()
{
    DWORD start = GetTickCount();
    cout<<start<<endl;

    Example4 ex("hello c++11");
    for(int i=0;i<1000000;++i){
#ifndef STDMOVE
        Example4 ex2(ex);
        Example4 ex3;
        ex3=ex2;
#else
        Example4 ex2(std::move(ex));
        Example4 ex3;
        ex3=std::move(ex2);
#endif
    }
    DWORD end = GetTickCount();
    cout<<end<<endl;
    cout<<end-start<<endl;

    return 0;
}
