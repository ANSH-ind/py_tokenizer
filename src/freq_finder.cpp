#include "tokenizer/freq_finder.h"
#include <iostream>

finder::finder(std::vector<std::vector<std::string>>& tokens): tokens(tokens){
    for(size_t i{}; i<tokens.size(); i++){
        for(size_t st{}; st+1<tokens[i].size(); ++st){
            std::pair<std::string, std::string> p = {tokens[i][st], tokens[i][st+1]};
            freq_pair[p] += 1;
        }
    }
    std::pair<std::string, std::string> best_pair;
    size_t best_freq = 0;
    for(const auto& [pair, freq] : freq_pair){
        if(best_freq<freq){
            best_freq = freq;
            best_pair = pair;
        }
    }
    best_freq_pair[best_pair] = best_freq;
}



std::unordered_map<std::pair<std::string, std::string>,uint64_t, Pairhash> finder::get_freq_pair(){
    return best_freq_pair;
};

std::unordered_map<std::pair<std::string, std::string>,uint64_t, Pairhash> finder::get_pairs(){
    return freq_pair;
}

//int main(){
//    std::vector<std::vector<std::string>> word = {{"h","i","i","</ws>"},{"i","</ws>"},{"a","m","</ws>"}};
//    finder Finder(word);
//}
