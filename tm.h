#include <unordered_set>
#include <vector>
enum next_state{
    N,L,R
};

struct instruction{
    instruction(std::string z,char g,std::string z_,char g_,next_state next){
        this->z = z;
        this->g = g;
        this->z_ = z_;
        this->g_ = g_;
        this->next = next;
    }
    std::string z;
    char g;
    std::string z_;
    char g_;
    next_state next;
};

class TM
{
private:
    std::unordered_set<std::string> Z = std::unordered_set<std::string>();
    std::unordered_set<char> Sigma = std::unordered_set<char>();
    std::unordered_set<char> Gamma = std::unordered_set<char>();
    std::vector<instruction> delta = std::vector<instruction>();
    std::string start;
    char empthy;
    std::unordered_set<std::string> E = std::unordered_set<std::string>();
public:
    TM(std::string path);
    /**
     * @brief Creates a touringmachine
     * @param  Z: the set of States
     * @param  Sigma: the input alphabet
     * @param  Gamma: the tape alphabet
     * @param  start: the start state
     * @param  empthy: the emphty symbol
     * @param  E: the set of end states
     * @retval 
     */
    TM(std::unordered_set<std::string> Z,
    std::unordered_set<char> Sigma,
    std::unordered_set<char> Gamma,
    std::vector<instruction> delta,
    std::string start,
    char empthy,
    std::unordered_set<std::string> E);
    ~TM();
    std::string run(std::string input);
    std::string run(std::string input,std::ostream &out);
    operator std::string();
};



