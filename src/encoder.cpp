#include "tokenizer/encoder.h"
#include "tokenizer/json.hpp"
#include <stdexcept>
#include <unordered_map>
using json = nlohmann::json;

encoder::encoder(const std::string& file_path,const std::string& word): file_path(file_path), word(word){
    json j;
    std::ifstream file(file_path);
    try{
        if(!file){
            throw std::runtime_error("json file dosen't opened please check the file path of you vocabulary.json and pass this into encoder class");
        }
    }
    catch(const std::runtime_error e){
        std::cerr<<e.what();
    }  
    file>>j;
    
    std::cout<<word<<" : "<<j[word]<<std::endl;
}

int encoder::get_encode(const std::string& file_path, const std::string& tk){
    json file_json;
    std::ifstream json_file(file_path);
    if(!json_file){
        throw std::runtime_error("json file dosen't opened please check the file path of you vocabulary.json and pass this into encoder class");
    }
    json_file>>file_json;
    
    if(file_json[tk].is_null()){
        std::cout<<tk<<" not found in your vocabulary"<<std::endl;
        return -1;
    }
    
    size_t id = file_json[tk];
    return id;
}

decoder::decoder(const std::string file_path, const size_t id): file_path(file_path), id(id){
    json json_file;
    
    std::ifstream file(file_path);
    if(!file){
        throw std::runtime_error("json file dosen't exist to decode the id");
    }    
}

std::string decoder::decode(const size_t id){
    
    std::ifstream file("vocabulary.json");
    if(!file){
        throw std::runtime_error("json file not found so that it can't iterate your json and gave you token's value");
    }
    json json_file;
    file>>json_file;
    
    std::unordered_map<size_t, std::string> words;
    for(const auto& [word , count] : json_file.items()){
        words[count] = word;
    }    
    auto it = words.find(id);
    if(it != words.end()){
        return words[id];
    }
    else{
        std::cerr<<"id's word not found!";
    }
    return "";
}