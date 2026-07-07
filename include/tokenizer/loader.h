#pragma once
#include <string>
#include <vector>

struct file_details{
    std::string file_path;
    long double file_size;
    std::string file_extension;
    bool normilize;
    size_t chunk_size;
    std::string tokenize_by = "py_tokenizer";
};

class loader{
    private:
    std::string file_path;
    size_t chunk_size;
    bool normilize;
    std::string file_extension;
    long double file_size;
    std::string sentance;
    public:
    loader(const std::string& file_path, const size_t chunk_size, bool normilize = false);
    
    std::string get_sentance();
    std::vector<file_details> detail_provider();
};