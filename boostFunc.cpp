//下载boost，并解压到工程目录下
//在QT工程里的.pro里，添加一行：INCLUDEPATH += D:/MyCProject/boost_1_66_0
#include "boostFunc.h"

#include<iostream>
#include"boost/function.hpp"
using namespace std;

template<typename Func>
class CFuncDemo
{
public:
    CFuncDemo(int iValue):m_iValue(iValue) {}

    template<typename CallBackFunc>
    void acceptFunc(CallBackFunc FuncCall) {
        m_Func = FuncCall;
    }

    void ComRst()
    {
        m_Func(m_iValue);
    }

    template<typename T>
    void ClassMemberRst(T &t)
    {
        m_Func(t,m_iValue);
    }

    void FuncObjRst()
    {
        m_Func(m_iValue);
    }

private:
    Func m_Func;
    int m_iValue;
};

void CommonFunc(int iValue)
{
    cout << "CallBack Common Function" << endl;
    cout << "2 * iValue = " << 2 * iValue << endl;
}

class CMultiple
{
public:
    void ClassFunc(int iValue)
    {
        cout<<"callback class member Function"<<endl<<"3 * iValue="<<3*iValue<<endl;
    }
};

class CFuncObj
{
public:
    void operator()(int iValue)
    {
        cout << "CallBack Function Object" << endl;
        cout << "4 * iValue = " << 4 * iValue << endl;
    }
};


int main_Func()
{
    //普通函数
    CFuncDemo<boost::function<void(int)>> tFuncCommon(10);
    tFuncCommon.acceptFunc(CommonFunc);
    tFuncCommon.ComRst();

    //类成员函数
    CMultiple tMember;
    CFuncDemo<boost::function<void(CMultiple &, int)>> tFuncClassMember(10);
    tFuncClassMember.acceptFunc(&CMultiple::ClassFunc);
    tFuncClassMember.ClassMemberRst(tMember);

    //函数对象
    CFuncObj tObj;
    CFuncDemo<boost::function<void(int)>> tFuncObj(10);
    tFuncObj.acceptFunc(tObj);
    //function使用拷贝语义保存参数，使用ref它允许以引用的方式传递参数
    tFuncObj.acceptFunc(boost::ref(tObj));
    tFuncObj.FuncObjRst();

    return 0;
}

