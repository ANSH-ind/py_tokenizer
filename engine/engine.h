#pragma once
#include <string>
#include <vector> 
#include "tokenizer/loader.h"
#include "tokenizer/freq_finder.h"
#include "tokenizer/merger.h"
#include "tokenizer/splitter.h"
#include "tokenizer/provider.h"
#include <thread>

inline const size_t cpu_count = std::thread::hardware_concurrency();
class engine{
    std::string file_path;
    size_t chunk_size;
    bool get_file_info;
    bool normilize;
    size_t epoch;
    size_t using_cpu;
    size_t vocab;
    bool use_thread;
    public:
    engine(const std::string& file_path,const size_t chunk_size, bool get_file_info = false, bool normilize = false, size_t epoch = 5, size_t using_cpu = cpu_count, bool use_thread = true);
};