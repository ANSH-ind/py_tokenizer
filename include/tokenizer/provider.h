#pragma once
#include <vector>
#include <string>
#include "tokenizer/loader.h"

class provider{
    std::vector<std::vector<std::string>> whole_merged_tokens;    
    bool get_file_detail;
    size_t vocab_size;
    
    public:
    provider(const std::vector<std::vector<std::string>>& whole_merged_tokens, const std::vector<file_details>& file_detail, bool get_file_detail = true, const size_t vocab_size = 0);

};