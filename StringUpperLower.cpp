#include <iostream>
#include <iterator>
using namespace std;

#include <ctype.h>
#include <algorithm>

//1.raw string literals R"(..)"
std::string no_newlines=R"(\n\n)";
std::string cmd(R"(cd "d:\")");
//2.string to upper, or to lower
std::string str = "djwoJ*FALInxk.lfDF232Dg";

int stringPro()
{
    int a2, b2, a3;
    int *c2 = &a2, *c3 = &a3, *d2 = &b2;
    std::cout << std::hex << c2 << " " << d2 << std::endl;
    std::cout << std::hex << std::distance(d2, c3) << std::endl;//std::distance返回的是迭代器的距离，而不是地址之差

    cout<<no_newlines<<cmd<<endl; //\n\ncd "d:\"

    //old methods
    char c;
    int i=0;
    while (str[i]) {
        c=std::tolower(str[i]);
        cout<<c;
        i++;
    }
    cout<<endl;

    //new method
    std::transform(str.begin(),str.end(),str.begin(),(int(*) (int))std::tolower);
    cout<<str<<endl;
    
    int(*fn)(int) = std::toupper;
    std::transform(str.begin(),str.end(),str.begin(),fn);
    cout<<str<<endl;

    std::transform(str.begin(),str.end(),str.begin(),[](char x){return std::tolower(x);});
    cout<<str<<endl;

    std::transform(str.begin(),str.end(),str.begin(),::toupper);
    cout<<str<<endl;

    return 0;
}
