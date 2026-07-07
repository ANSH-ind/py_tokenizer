#include "engine.h"
#include <iostream>
#include <unordered_map>
#include <utility>

engine::engine(const std::string& file_path, const size_t chunk_size, bool get_file_info, bool normilize, size_t epoch, size_t using_cpu, bool use_thread): file_path(file_path),chunk_size(chunk_size), get_file_info(get_file_info), normilize(normilize), epoch(epoch), using_cpu(using_cpu), use_thread(use_thread){
    
    std::vector<std::vector<std::string>> tokens;
    
    std::unordered_map<std::pair<std::string, std::string>, uint64_t, Pairhash> best_freq_pair;
    
    std::string sentance;
    
    loader DataLoader(file_path, chunk_size, normilize);
    
    sentance = DataLoader.get_sentance();
    
    splitter SPLITTER(sentance, using_cpu,use_thread);
    
    if(use_thread){
        SPLITTER.thread_runner();
    }
    tokens = SPLITTER.get_splited_tokens();
    
    std::vector<file_details> details = DataLoader.detail_provider();
    
    while(epoch>0){
        finder FINDER(tokens);
        best_freq_pair = FINDER.get_freq_pair();
        
        merger MERGER(best_freq_pair, tokens);
        
        
        tokens = MERGER.get_merged_tokens();
        
        vocab = MERGER.get_vocab();
        epoch--;
    }
    provider PROVIDER(tokens, details, get_file_info, vocab);
    
};
