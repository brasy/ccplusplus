//lambda mutable, 破除lambda表达式const类型, 修改捕捉到的上下文中的内容
#include"boost/function.hpp"
#include <vector>
#include <iostream>
using namespace std;

std::function<vector<int>()> vector_generator()
{
    vector<int> items {1, 2, 3, 4, 5};
    return [items] () mutable {
        for (int& item : items) ++item;
            return items;
    };
}

int lambdaMutable()
{
    auto vec_gen = vector_generator();
    for(auto vec : vec_gen())
        cout<<vec<<" "; //2, 3, 4, 5, 6
    cout<<endl;
    for(auto vec : vec_gen())
        cout<<vec<<" "; //3, 4, 5, 6, 7
    //assert(vec_gen() == vector<int>{2, 3, 4, 5, 6});
    //assert(vec_gen() == vector<int>{3, 4, 5, 6, 7});
    return 0;
}
