#include "tm.h"
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    std::string tm_file_path = "";
    for(int i = 1; i < argc; i++)
    {
        std::string param = std::string(argv[i]);
        std::cout << param << std::endl;
        if(*param.begin() != '-'){
            tm_file_path = param;
        }
    }
    if(tm_file_path == ""){
        std::cerr << "No tm file path provided";
        exit(1);
    }
    TM m = TM(tm_file_path);
    // m = TM(
    //     std::unordered_set<std::string>({"z0","z1","z2"}),
    //     std::unordered_set<char>({'0','1'}),
    //     std::unordered_set<char>({'0','1','#'}),
    //     std::vector<instruction>({instruction("z0",'0',"z0",'1',R),
    //     instruction("z0",'1',"z0",'0',R),
    //     instruction("z0",'#',"z1",'#',L),
    //     instruction("z1",'0',"z1",'0',L),
    //     instruction("z1",'1',"z1",'1',L),
    //     instruction("z1",'#',"z2",'#',R)}),
    //     "z0",
    //     '#',
    //     std::unordered_set<std::string>({"z2"}));
    std::string tape;
    //std::cout << ((std::string)m) << "\n";
    std::cout << "Input:" << std::endl;
    std::cin >> tape;
    tape= m.run(tape,std::cout);
    std::cout << tape << std::endl;
    return 0;
}
