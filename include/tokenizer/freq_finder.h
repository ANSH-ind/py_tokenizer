#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <utility>

struct Pairhash{
    template<typename T1, typename T2>
    size_t operator()(const std::pair<T1,T2>& p)const{
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1^(h2+0x9e3779b97f4a7c15+(h1<<6)+(h1>>2));
    }
};

class finder{
    private:
    std::vector<std::vector<std::string>> tokens;
    std::unordered_map<std::pair<std::string, std::string>, uint64_t, Pairhash> freq_pair;
    std::unordered_map<std::pair<std::string, std::string>, uint64_t, Pairhash> best_freq_pair;
    public:
    finder(std::vector<std::vector<std::string>>& tokens);
    
    std::unordered_map<std::pair<std::string,std::string>,uint64_t,Pairhash> get_freq_pair();
    std::unordered_map<std::pair<std::string, std::string>,uint64_t, Pairhash> get_pairs();
};
    
    
