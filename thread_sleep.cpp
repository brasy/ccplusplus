//https://en.cppreference.com/w/cpp/thread/sleep_until
/* std::chrono
 * std::this_thread::sleep_until
 * C++  Thread support library
 * Defined in header <thread>
 * (since C++11)
 * template< class Clock, class Duration >
   void sleep_until( const std::chrono::time_point<Clock,Duration>& sleep_time );
 * 阻止当前线程执行，直到指定sleep_time溢出
 * 参数sleep_time:阻塞时长，与时钟Clock相关联
 * 无返回值，异常由Clock或Duration抛出，若使用标准库里则不会抛出异常
 */


#include <iostream>
#include <thread>  //std::this_thread, include <chrono>
#include <ctime>  //std::time_t, std::tm, std::localtime, std::mktime
#include <iomanip>  //time_put::put to format time
#include <vector>

//get_id
std::thread::id main_thread_id = std::this_thread::get_id();
void mainthread()
{
    if (main_thread_id == std::this_thread::get_id())
        std::cout<<"main thread \n";
    else
        std::cout<<"no main thread \n";
}

//sleep_until
//now() 当前时间time_point
//to_time_t() time_point转换成time_t秒
//from_time_t() 从time_t转换成time_point

void infinite_sleep()
{
    std::this_thread::sleep_until(std::chrono::time_point<std::chrono::system_clock>::max());
}

//#pragma warning(disable:4996)
void sleepUntil()
{
    using std::chrono::system_clock;
    std::time_t timer = system_clock::to_time_t(system_clock::now());
    struct std::tm *ptm=std::localtime(&timer);
    std::cout<<"Current time: "<<std::put_time(ptm,"%X")<<std::endl;

    //std::cout << "Waiting for the next minute to begin...\n";
    //++ptm->tm_min;
    //ptm->tm_sec = 0;
    //std::this_thread::sleep_until(system_clock::from_time_t(mktime(ptm))); //有问题，需要check
    std::cout << std::put_time(ptm,"%X") << " reached!\n";
    //getchar();
}

//vector<time_point>
void time_pointVec()
{
    using std::chrono::time_point;
    using std::chrono::system_clock;
    time_point<system_clock> now = system_clock::now();
    std::vector<time_point<system_clock>> times {
        now - std::chrono::seconds(10),
        now - std::chrono::minutes(20),
        now + std::chrono::hours(1)
    };

    std::cout<< "all times: \n";
    for (const auto &time : times){
        std::time_t t =  system_clock::to_time_t(time);
        std::cout <<std::ctime(&t);
    }
}

//sleep_for
void sleepFor()
{
    std::cout<<"sleep for : \n";
    for (auto i : {10,9,8,7,6,5,4,3,2,1}){
        std::cout<<i;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout<<std::endl;
}

//duration
void duration()
{
    using std::chrono::system_clock;
    using std::chrono::microseconds;

    auto start = system_clock::now();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    auto end   = system_clock::now();
    auto duration = std::chrono::duration_cast<microseconds>(end - start);
    std::cout<<"duration: "<<double(duration.count())*microseconds::period::num/microseconds::period::den<<std::endl;
}

int main_thread()
{
    mainthread();  //main thread
    std::thread others (mainthread);
    others.join(); //no main thread

    infinite_sleep();

    sleepUntil(); //Current time: 18:22:58  \n  18:22:58 reached!

    time_pointVec();  //all times: ...

    sleepFor();

    duration(); //duration: 2.0002

    return 0;
}

