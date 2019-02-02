#include "tm.h"
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    TM m = TM(
        std::unordered_set<std::string>({"z0","z1","z2"}),
        std::unordered_set<char>({'0','1'}),
        std::unordered_set<char>({'0','1','#'}),
        std::vector<instruction>({instruction("z0",'0',"z0",'1',R),
        instruction("z0",'1',"z0",'0',R),
        instruction("z0",'#',"z1",'#',L),
        instruction("z1",'0',"z1",'0',L),
        instruction("z1",'1',"z1",'1',L),
        instruction("z1",'#',"z2",'#',R)}),
        "z0",
        '#',
        std::unordered_set<std::string>({"z2"}));
    std::string tape;
    std::cout << ((std::string)m) << "\n";
    std::cout << "Insert Tape" << std::endl;
    std::cin >> tape;
    tape= m.run(tape,std::cout);
    std::cout << tape << std::endl;
    return 0;
}
