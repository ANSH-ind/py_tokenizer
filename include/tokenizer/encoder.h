#pragma once
#include "tokenizer/provider.h"
#include <fstream>
#include <iostream>
#include <string>

class encoder{
    private:
    std::string file_path;
    std::string word;
    public:
    encoder(const std::string& file_path = "vocabulary.json", const std::string& word = "");
    
    static int get_encode(const std::string& file_path, const std::string& tk);
};

class decoder{
    private:
    std::string file_path;
    size_t id;
    public:
    decoder(std::string file_path = "vocabulary.json", const size_t id = 0);
    
    std::string decode(const size_t id);
};