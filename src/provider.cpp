#include "tokenizer/provider.h"
#include "tokenizer/json.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>

using json = nlohmann::json;

std::string escape_bytes(const std::string& s) {
    std::ostringstream out;

    for (unsigned char c : s) {
        if (c >= 32 && c <= 126 && c != '\\') {
            // Printable ASCII
            out << c;
        } else {
            // Escape everything else
            out << "\\x"
                << std::uppercase
                << std::hex
                << std::setw(2)
                << std::setfill('0')
                << (int)c;
        }
    }

    return out.str();
}


provider::provider(const std::vector<std::vector<std::string>>& whole_merged_tokens, const std::vector<file_details>& file_detail, bool get_file_detail, size_t vocab_size): whole_merged_tokens(whole_merged_tokens), get_file_detail(get_file_detail), vocab_size(vocab_size){
    if(get_file_detail){
        json file_info;
        
        file_info["file path"] = file_detail[0].file_path;
        file_info["file size"] = file_detail[0].file_size;
        file_info["file extension"] = file_detail[0].file_extension;
        file_info["normilize"] = file_detail[0].normilize;
        file_info["chunk size"] = file_detail[0].chunk_size;
        file_info["vocabulary size"] = vocab_size;
        file_info["using data type"] = "uint64_t";
        file_info["using json file"] = "nlohmann json";
        file_info["tokenize by"] = "py_tokenizer";
        file_info["model version"] = "1.0_v1";
        std::ofstream file("file_info.json");
        
        file<<file_info.dump(4);
    }
    
    std::cout<<"running process...";
    std::vector<std::string> checker;
    size_t id = 0;
    for(const auto& tk : whole_merged_tokens){
        for(const auto& word : tk){
            auto it = std::find(checker.begin(), checker.end(), word);
            if(it == checker.end()){
                checker.push_back(word);
            }
        }
    }
    
    for(const auto& w : checker){
        std::cout<<w<<" : "<<id++<<std::endl;
    }
    json vocabulary;
    
    
    size_t i = 0;
    for(const auto& tokens : whole_merged_tokens){
        for(const std::string& token : tokens){
            if(!vocabulary.contains(escape_bytes(token))){
                vocabulary[escape_bytes(token)] = i++;
            }
        }
    }
    
    std::ofstream output_file("vocabulary.json");
    output_file<<vocabulary.dump(4);
}
