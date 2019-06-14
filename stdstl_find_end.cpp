//std::find()函数使用方法，转自http://blog.csdn.net/zhangweijiqn/article/details/9107571
#include <iostream>
#include <vector>
#include <algorithm>//注意要包含该头文件
using namespace std;
int arrayFind();
int vectorFind();

int main_find()
{
    arrayFind();
    vectorFind();
    return 0;
}
int arrayFind()
{
    int nums[] = { 3, 1, 4, 1, 5, 9 };
    int num_to_find = 5;
    int start = 0;
    int end = 5;
    int* result = find( nums + start, nums + end, num_to_find );
    if( result == nums + end )
    {
        cout<< "Did not find any number matching " << num_to_find << endl;
    }
    else
    {
         cout<< "Found a matching number: " << *result << endl;
    }
    return 0;
}

int vectorFind()
{
    vector<int> v;
    int num_to_find=25;//要查找的元素,类型要与vector<>类型一致
    for(int i=0;i<10;i++)
        v.push_back(i*i);
    vector<int>::iterator iter=std::find(v.begin(),v.end(),num_to_find);//返回的是一个迭代器指针
    if(iter==v.end())
        cout<<"ERROR!"<<endl;
    else               //注意迭代器指针输出元素的方式和distance用法
        cout<<"the index of value "<<(*iter)<<" is " << std::distance(v.begin(), iter)<<std::endl;
    return 0;
}
