#include "tm.h"
#include <exception>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <iostream>
#include <regex>

TM::TM(std::unordered_set<std::string> Z,
    std::unordered_set<char> Sigma,
    std::unordered_set<char> Gamma,
    std::vector<instruction> delta,
    std::string start,
    char empthy,
    std::unordered_set<std::string> E){
        if(Z.empty()){
            throw "Z needs to be not empthy";
        }
        // {
        //     std::unordered_set<char> output;
        //     std::set_intersection(Z.begin(),Z.end(),Sigma.begin(),Sigma.end(),output.begin());
        //     if(output.size() != 0){
        //         throw "Z and Sigma must be disjoint";

        //     }
        // }
        // {
        //     std::unordered_set<char> output;
        //     std::set_intersection(Z.begin(),Z.end(),Gamma.begin(),Gamma.end(),output.begin());
        //     if(output.size() != 0){
        //         throw "Z and Gamma must be disjoint";

        //     }
        // }
        {
            auto iter = Sigma.begin();
            while(iter != Sigma.end()){
                if(Gamma.find(*iter) == Gamma.end()){
                    throw "Sigma must be a Subset of Gamma";
                }
                iter++;
            }
            
        }
    this->Z = Z;
    this->Sigma = std::unordered_set<char>(Sigma);
    this->Gamma = std::unordered_set<char>(Gamma);
    this->delta = std::vector<instruction>(delta);
    this->start = start;
    this->empthy = empthy;
    this->E = std::unordered_set<std::string>(E);
}

TM::TM(std::string path){
    std::regex delta_regex = std::regex("^(\\S+)[\\t ]+(\\S+)[\\t ]+>[\\t ]+(\\S+)[\\t ]+(\\S+)[\\t ]+(R|L|N)$");
    std::ifstream tm_file;
    try
    {
        tm_file.open(path);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::string line;
    while(getline(tm_file,line)){
        if(std::regex_match(line,delta_regex)){
            auto iter = std::sregex_token_iterator(line.begin(),line.end(),delta_regex,0);
            std::sregex_token_iterator end;
            while(iter!=end){
                std::cout << iter->str() << std::endl;
                iter++;
            }
            
        }
    }

    tm_file.close();
}

TM::~TM(){

}
std::string TM::run(std::string input){
    std::stringstream nullstream;
    return run(input,nullstream);
}
std::string TM::run(std::string input,std::ostream &out){
    input= empthy + input +empthy;
    auto iterator = input.begin();
    iterator++;
    std::string state = start;
    while(E.count(state)== 0){
        out << input << "\n";
        for(auto instr_iter = delta.begin();;instr_iter++){
            instruction instr = *instr_iter;
            if(instr.z == state && instr.g == *iterator){
                state = instr.z_;
                *iterator = instr.g_;
                if(instr.next == R){
                    iterator++;
                    if(iterator == input.end()){
                        input.insert(input.end(),empthy);
                        iterator = input.end();
                        iterator--;
                    }
                }else if (instr.next == L)
                {
                    iterator--;
                    if(iterator == input.begin()){
                        input.insert(input.begin(),empthy);
                        iterator = input.begin();
                        iterator++;
                    }
                }
                break;
            }
        }
    }
    
    return input;
}

TM::operator std::__cxx11::string(){
    return "";
}

