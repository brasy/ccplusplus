// lambda 函数类型。 存储lambda为本地变量，并通过using传递给function
/*
 * set 三种构造函数, https://en.cppreference.com/w/cpp/container/set
 * insert操作
 * count和find操作
 * erase操作
 * set不支持下标操作符，而且没有定义mapped_type类型。在set容器中，value_type不是pair类型，而是与key_type相同的类型
 * set容器存储的键也必须唯一，且不能修改。以一段范围内的元素初始化set对象，或在set对象中插入一组元素时，对于每个键，事实上都只添加了一个元素
 */
#include <set>
#include <queue>
enum class e : char;
enum class e : char {
    hello,
    lambda
};

int lambdaFuncType()
{
    //1. auto-deduction mechanism
    auto comp = [](const unique_ptr<int>&a, const unique_ptr<int>& b){return *a < *b;};
    set<unique_ptr<int>, decltype(comp)>numbers (comp);

    int a=3,b=4;
    auto f = comp(std::make_unique<int>(a), std::make_unique<int>(b));
    cout<<f<<endl; //1
    numbers.insert(std::make_unique<int>(a));
    auto bv=numbers.insert(std::make_unique<int>(a)).second;
    cout<<numbers.size()<<"  "<<bv<<endl; //1  0

    //2.std::function ( be careful - type-erasure)
    queue<std::function<void()>> work_queue;
    work_queue.push([] { std::cout << "Start" << std::endl; });

    //3.for empty []  by pointer function
    using FunctionPtr = int(*)();
    FunctionPtr f1 = [] () -> int {return 2;};
    cout<<f1()<<endl; //2

    e ee;
    ee = e::hello;
    const auto fromStr = [ee](const auto& id) { cout<<"hello "<<static_cast<int>(ee)<<endl; return (static_cast<e>(id));};  //hello 0
    cout<<static_cast<int>(fromStr(e::lambda))<<endl; //1
    return 0;
}
