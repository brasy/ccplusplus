//string conversion, between string, int, float, bool, long..
#include <string>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>

namespace utils {

std::string to_string(bool value)
{
    return value? "true" : "false";
}

std::string to_string(const unsigned char* uscValue)
{
    return reinterpret_cast<const char*>(uscValue);
}

std::string cString2String(uint32_t length, uint32_t maxLength, const uint8_t* cstring)
{
    uint32_t boundary = (length < maxLength)? length : maxLength;
    if(length == 0)
        return "";
    else{
        const auto* chs = reinterpret_cast<const char*>(cstring);
        return (std::string(chs, boundary));
    }
}

bool to_bool(const std::string&);
int safeStoI(const std::string& value, boost::optional<int> defaultValue = boost::none, int base = 10)
{
    try{ //stoi(const wstring& __str, size_t* __idx = 0, int __base = 10)
        return std::stoi(value, nullptr, base);
    }
    catch(const std::logic_error&)
    {
        if (not defaultValue){defaultValue=0;}
        return *defaultValue;
    }
}

long safeStoL(const std::string& value, boost::optional<long> defaultValue = boost::none, int base = 10)
{
    try{
        return std::stol(value, nullptr, base);
    }
    catch(const std::logic_error&){
        if (not defaultValue){defaultValue = 0;}
        return *defaultValue;
    }
}

float safeStoF(const std::string& value, float defaultValue = 0.0)
{
    try{
        return std::stof(value, nullptr);
    }
    catch(const std::logic_error&){
        return defaultValue;
    }
}

unsigned int safeStoU(const std::string& value, unsigned int defaultValue=0u)
{
    try{
        return boost::lexical_cast<unsigned int>(value);
    }
    catch(const boost::bad_lexical_cast&){
        return defaultValue;
    }
}

}

#include <iostream>
struct ParamVal
{
    int Type;
    int Value;
};
int main_strcov()
{
    std::string mystr = "1234";
    int intNum = utils::safeStoI(mystr,-1);
    int lNum = utils::safeStoL(mystr,-1);
    int fNum = utils::safeStoF(mystr, 1.0);

    std::cout<<mystr.c_str()<<std::endl
            <<"str to int: "<<intNum<<std::endl
            <<"str to long: "<<lNum<<std::endl
           <<"str to float: "<<fNum<<std::endl;

    const uint8_t cstring = 56;
    std::string ret = utils::cString2String(2,3,&cstring);
    std::cout<<ret.c_str()<<std::endl;

    std::vector<ParamVal> paramVal;
    paramVal.push_back({1,1});
    paramVal.push_back({2,4});
    paramVal.push_back({3,9});
    for(auto i : paramVal)
        std::cout<<i.Type<<": "<<i.Value<<std::endl;
    std::cout<<paramVal[1].Type<<std::endl;

    return 0;
}
