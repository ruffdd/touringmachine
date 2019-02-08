#include "tm.h"
#include <exception>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <iostream>
#include <regex>
#include <exception>
#include <system_error>
#include "helper.h"

TM::TM(std::unordered_set<std::string> Z,
    std::unordered_set<char> Sigma,
    std::unordered_set<char> Gamma,
    std::vector<instruction> delta,
    std::string start,
    char empty,
   std::unordered_set<std::string> E){
        if(Z.empty()){
            throw "Z needs to be not empty";
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
    this->empty = empty;
    this->E = std::unordered_set<std::string>(E);
}

TM::TM(std::string path){
    std::regex delta_regex = std::regex("^(\\S+)[\\t ]+(\\S+)[\\t ]+(\\S+)[\\t ]+(\\S+)[\\t ]+(R|L|N)$");
    std::ifstream tm_file;
    tm_file.open(path);
    if(!tm_file){
        throw std::system_error::runtime_error("File ("+path+") empty or not existing");
    }


    std::string line;
    while(getline(tm_file,line)){
        line = helper::trim(line);
        if (helper::startwith(line, "start:")) {
            start = line.substr(line.find(":")+1);
        }else if (helper::startwith(line,"empty"))
        {
            empty = line[line.find(":")+1];
        }else if (helper::startwith(line,"end:"))
        {
            std::vector<std::string> ends = helper::split(line.substr(line.find(":")+1),{","});
            for(auto&& e : ends)
            {
                E.insert(e);
            }
            
        }else if(std::regex_match(line,delta_regex))
        {
            instruction new_instruction;
            std::vector<std::string> values=helper::split(line," \t");
            new_instruction.z = values[0];
            new_instruction.g = values[1][0];
            new_instruction.z_ = values[2];
            new_instruction.g_ = values[3][0];
            if(values[4][0]=='R'){
                new_instruction.next = R;
            }else if (values[4][0]=='L')
            {
                new_instruction.next = L;
            }else if (values[4][0]=='N')
            {
                new_instruction.next = N;
            }else{
                throw "Only Next Values LRN are allowed. not " + values[4];
            }
            Z.insert(new_instruction.z);
            Z.insert(new_instruction.z_);
            Sigma.insert(new_instruction.g);
            Sigma.insert(new_instruction.g_);
            delta.push_back(new_instruction);
        }
        Gamma = std::unordered_set<char>(Sigma);
        Gamma.insert(empty);
        
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
    input= empty + input +empty;
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
                        input.insert(input.end(),empty);
                        iterator = input.end();
                        iterator--;
                    }
                }else if (instr.next == L)
                {
                    iterator--;
                    if(iterator == input.begin()){
                        input.insert(input.begin(),empty);
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

