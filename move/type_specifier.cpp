//type specifier
int x=22;
const int cx=x;
const int& rx=x;
//1.reference T&
template<typename T>
void f_ref(const T& param){}
const int* pcx=&x;
//2.point T*
template<typename T>
void f_point(T* param){}
//3.universal ref T&&，Reference collapsing yield type T& param
/* 万能类型 T&&,
 * 既可以左值&，也可以右值&&，根据传入的param决定
 * 如果初始化表达式是左值，则引用是左值
 * 如果初始化表达式是右值，则演绎成右值引用代替
*/
template<typename T>
void f_univ(T&& param){}

//4. no T， param is now passed by value
template<typename T>
void f_no(T param){}


int main_spec()
{
    f_ref(x); // T=int, param's type = const int&
    f_ref(cx); // T=const int, param's type = const int&
    f_ref(rx); // T=const int, param's type = const int&
    f_point(&x); //T=int, param's type = int *
    f_point(pcx); //T=const int,param's type = const int*
    f_univ(x); //x左值,T=int&,param's type=int&
    f_univ(cx); //cx左值, T=const int&,param's type=const int&
    f_univ(rx); //rx左值, T=const int&,param's type=const int&
    f_univ(23); //23是一个右值，T=int,param's type=int&&
    f_no(x); //T=int,param's type=int
    f_no(cx); //T=int,param's type=int
    f_no(rx); //T=int,param's type=int
    return 0;
}
