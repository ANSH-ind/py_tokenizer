#pragma once
#include "tokenizer/splitter.h"
#include "tokenizer/merger.h"
#include "tokenizer/freq_finder.h"
#include <string>
#include <vector>
#include <unordered_map>


class basic_engine{
    private:
    std::string sentance;
    bool normilize;
    size_t epoch;
    
    public:
    basic_engine(const std::string& sentance, bool normilize = false, size_t epoch = 5);
};
