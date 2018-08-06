#include <string>
#include <stdlib.h>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

using IdNameMap = std::map<std::string, std::string>;
char dlName[128] = "../practiseC1114/filepath/Files.txt.gz";

int main_str()
{
    IdNameMap idList = { {"plan1","push the version"}, {"plan2","rm -rf filenames"}};
    auto it = idList.find("plan1");
    if (it == idList.end())
        cout<<"cannot find id: pland1"<<endl;

    (*it).second.clear();
    std::for_each(idList.begin(), idList.end(), [](IdNameMap::reference a){
        std::cout << a.first << "  " << a.second << "\n";
    });

    //cout<<system("dir")<<endl;

    char listzip[128] = "";
    sprintf(listzip,"tar -tvf %s",static_cast<char *>(dlName));
    cout<<"listzip: "<<listzip<<endl;

    int ret = system(listzip);
    cout<<"after system: "<<listzip<<"   "<<ret<<endl;

    char unzip[128] = "";
    sprintf(unzip,"tar -zxf %s",static_cast<char *>(dlName));
    cout<<"unzip1: "<<unzip<<endl;
    ret = system(unzip);
    cout<<"after system unzip: "<<unzip<<"   "<<ret<<endl;

    char removeFile[128] = {0};
    sprintf(removeFile,"rm -f %s",static_cast<char *>(dlName));
    cout<<"removeFile: "<<unzip<<endl;

    std::string xmlfileName = dlName;
    xmlfileName.erase(xmlfileName.end()-3,xmlfileName.end());
    (*it).second.assign(xmlfileName);
    cout<<xmlfileName<<endl;

    /* 给定全路径文件，进行解压缩处理，并传给去文件名
     * 首先是要system函数获取当前工作路径，设置好要解压的文件
     * 1.list文件，2.解压缩，3.删除 压缩包
     * 4.处理全路径文件名称，并输出文件全称
     * 最后得过解压缩的文件，解压缩文件的(path+filename)=xmlfileName
     */

    return 0;
}
