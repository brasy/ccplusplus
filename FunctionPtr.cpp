#include <iostream>
using namespace std;

class CEventQuery;

typedef bool (*ComFuncPoint)(void); //定义普通指针
typedef bool (CEventQuery::*ClassFuncPoint)(int); //定义类成员函数指针

bool ComFunc(void)
{
    cout<<"callbackfucntion common function call"<<endl;
    return true;
}

class CEventQuery
{
public:
    CEventQuery(ComFuncPoint eventFunc):m_Event(eventFunc) {}
    ~CEventQuery(){}

    void Query(void)
    {
        m_Event();
    }

    bool DoSomethings(int iValue)
    {
        cout<<"classfunction parament: "<<iValue<<endl;
        return true;
    }
private:
    ComFuncPoint m_Event;
};

int main()
{
    CEventQuery tEventQuery(ComFunc);
    tEventQuery.Query(); //callbackfucntion common function call

    ClassFuncPoint ClassFunc1 = &CEventQuery::DoSomethings;
    (tEventQuery.*ClassFunc1)(10); //类成员函数指针调用, classfunction parament: 10

    tEventQuery.DoSomethings(20); //类实例函数调用, classfunction parament: 20
    return 0;
}
