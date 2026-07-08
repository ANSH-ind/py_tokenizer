#pragma once
#include <vector>
#include <string>
#include "tokenizer/loader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstdint>

std::u32string utf8_decode(const std::string &input);

std::string utf8_encode(const std::u32string& input);

class provider{
    std::vector<std::vector<std::string>> whole_merged_tokens;    
    bool get_file_detail;
    size_t vocab_size;
    public:
    provider(const std::vector<std::vector<std::string>>& whole_merged_tokens, const std::vector<file_details>& file_detail, bool get_file_detail = true, const size_t vocab_size = 0);
};