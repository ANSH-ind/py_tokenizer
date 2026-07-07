#include "tokenizer/merger.h"
#include <iostream>

merger::merger(const std::unordered_map<std::pair<std::string, std::string>, uint64_t, Pairhash> &best_freq_pair, const std::vector<std::vector<std::string>> &splited_whole_tokens) : best_freq_pair(best_freq_pair), splited_whole_tokens(splited_whole_tokens)
{
    std::pair<std::string, std::string> best_pair;
    size_t best_freq = 0;
    size_t splited_vector_size = splited_whole_tokens.size();
    
    if(best_freq_pair.empty()){
    return;
    }
    merged_token.reserve(splited_vector_size);
    for (const auto &[pair, freq] : best_freq_pair)
    {
        best_pair = pair;
        best_freq = freq;
    }
    for(const auto& [p, f] : best_freq_pair){
        std::cout<<"("<<p.first<<","<<p.second<<")"<<" : "<<f<<std::endl;
    }
    vocab_size = 0;

    std::vector<std::string> carrier;
    for (const auto &token_vector : splited_whole_tokens)
    {
        carrier.clear();
        for (size_t i{}; i < token_vector.size(); ++i)
        {
            if (i < token_vector.size() - 1 && token_vector[i] == best_pair.first && token_vector[i + 1] == best_pair.second)
            {
                carrier.push_back(token_vector[i] + token_vector[i + 1]);
                i++;
            }
            else
            {
                carrier.push_back(token_vector[i]);
            }
        }
        vocab_size += 1;
        merged_token.push_back(carrier);
    }
}

std::vector<std::vector<std::string>> merger::get_merged_tokens()
{
    return merged_token;
}

size_t merger::get_vocab()
{
    return vocab_size;
}

//int main(){
//    std::vector<std::vector<std::string>> wh_tk = {{"h","i","i",}};
//    std::unordered_map<std::pair<std::string, std::string>, uint64_t, Pairhash> word_freq;

//    word_freq[{"i","i"}] = 20;
//    merger Merger(word_freq, wh_tk);
//    size_t v = Merger.get_vocab();
//    std::cout<<v<<std::endl;
//}
