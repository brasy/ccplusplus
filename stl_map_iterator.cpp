#include <iostream>
#include <map>
#include <string>
#include <vector>

//关联式容器，调用erase后，当前迭代器已经失效, 不应再for使用, 否则导致访问不可访问的内存 addr8 error

using namespace std;

int main_MAP()
{
    map<int, string> m;
    m.insert(make_pair<int, string>(1,"marry"));
    m.insert(make_pair<int, string>(2,"bob"));
    m.insert(make_pair<int, string>(3,"kate"));
    m.insert(make_pair<int, string>(4,"lily"));

    map<int, string>::iterator itor = m.begin();

    /*
    //错误写法，没有理解iterator
    for (; itor != m.end(); ++itor)
    {
        if (itor->second == "kate")
        {
            m.erase(itor); // map是关联式容器，调用erase后，当前迭代器已经失效, 不应再for使用, 否则导致访问不可访问的内存 addr8 error
        }
    }
    */


    //正确写法1, find
    int key = 2;
    auto iter = m.find(key);
    m.erase(iter);

    for(auto it = m.begin(); it != m.end(); ++it)
        cout << it->first << ": " << it->second <<endl;

    /*
    //正确写法2, clear all
    map<int, string>::iterator l_itErase;
    while (itor != m.end()) {
        l_itErase = itor;
        itor++;
        m.erase(l_itErase);
    }

    for(auto it = m.begin(); it != m.end(); ++it)
        cout << it->first << ": " << it->second <<endl;

    //正确写法3: 使用删除之前的迭代器定位下一个元素。STL建议的使用方式
    while (itor != m.end()) {
        cout << itor->first << ": " << itor->second <<endl;
        m.erase(itor++); //旧版的有效
    }

    //正确写法4: erase()成员函数返回下一个元素的迭代器, 注意，有些版本的stl-map没有返回值，比如SGI版，但vc版的有
    for (; itor != m.end();)
    {
        cout << itor->first << ": " << itor->second <<endl;
        itor = m.erase(itor);  //支持返回值版本，c++11 有效
    }
    */

    std::vector<int> a = {1,2,3,4,5,6,7,8};
    for (std::vector<int>::iterator iter = a.begin(); iter != a.end();)
    {
        if (*iter % 2 == 0)
        {
            iter = a.erase(iter); //STL中有要求vector的erase函数要返回指向被erase的迭代器的下一个位置，写成it=intVec.erase(it)是万无一失的，
        }
        else
        {
            ++iter;
        }
    }

    for (auto it = a.begin(); it != a.end(); ++it)
    {
        cout << *it <<endl;
    }

    return 0;

}
