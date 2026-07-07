#include "basic_engine.h"
#include <iostream>

basic_engine::basic_engine(const std::string& sentance, bool normilize, size_t epoch): sentance(sentance),normilize(normilize), epoch(epoch){
    
    splitter SPLITTER(sentance, normilize, false);
    std::vector<std::vector<std::string>> tokens = SPLITTER.get_splited_tokens();
    
    size_t vocab = 0;
    std::unordered_map<std::pair<std::string, std::string>,uint64_t, Pairhash> best_freq_pair;
    while(epoch != 0){
        
        finder FINDER(tokens);
        
        best_freq_pair = FINDER.get_freq_pair();
        
        merger MERGER(best_freq_pair, tokens);
        tokens.clear();
        tokens = MERGER.get_merged_tokens();
        vocab = MERGER.get_vocab();
       
        epoch--;
    }
    std::cout<<"\nvocab size: "<<vocab<<"\n"<<std::endl;
    size_t id = 0;
    for(const auto& vector_box : tokens){
        for(const auto& word : vector_box){
            std::cout<<word<<",";
        }
        std::cout<<" : "<<id<<std::endl;
        id++;
    }
}
