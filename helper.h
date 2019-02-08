#include <string>
#include <math.h>

namespace helper{
    std::string ltrim(const std::string& input){
        int index = input.find({' ','\t'});
        if(index <= 0){
            return input;
        }else
        {
            return input.substr(index);
        }
        
    }

    std::string rtrim(const std::string& input){
        int index = input.rfind({' ','\t'});
        if(index <= 0){
            return input;
        }else
        {
            return input.substr(0,index+1);
        }
        
    }

    std::string trim(const std::string& input){
        return rtrim(ltrim(input));
    }

    auto startwith = [](std::string str, std::string prefix) {
        return str.substr(0, prefix.length()) == prefix;
    };

    
    std::vector<std::string> split(const std::string& input,const std::string& seper){
        auto iterator = input.begin();
        std::vector<std::string> output;
        std::string current_string;
        while(iterator != input.end()){
            if(seper.find(*iterator)==-1){
                current_string.push_back(*iterator);
            }else if(current_string.size())
            {
                output.push_back(current_string);
                current_string = "";
                
            }
            
            iterator++;
        }
        output.push_back(current_string);
        return output;
    }
}