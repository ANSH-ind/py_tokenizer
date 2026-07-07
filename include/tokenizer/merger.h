#pragma once
#include "tokenizer/freq_finder.h"
#include <unordered_map>
#include <utility>
#include <string>
#include <vector>

class merger{
    private:
    std::unordered_map<std::pair<std::string, std::string>, uint64_t, Pairhash> best_freq_pair;

    std::vector<std::vector<std::string>> splited_whole_tokens;    
    std::vector<std::vector<std::string>> merged_token;
    size_t vocab_size;
    public:
    merger(const std::unordered_map<std::pair<std::string, std::string>,uint64_t, Pairhash>& best_freq_pair,const std::vector<std::vector<std::string>>& splited_whole_tokens);
    std::vector<std::vector<std::string>> get_merged_tokens();
    size_t get_vocab();
    
};