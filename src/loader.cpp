#include "tokenizer/loader.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <cmath>

loader::loader(const std::string& file_path, const size_t chunk_size, bool normilize): file_path(file_path), chunk_size(chunk_size), normilize(normilize)
{
    
    std::ifstream file(file_path, std::ios::binary);
    if(!file.is_open()){
       throw std::runtime_error("file dosen't exist please check and retry");
    }
    
    std::filesystem::path path(file_path);
    file_extension = path.extension().string();
    file_size = std::filesystem::file_size(file_path)/1024.0;
    file_size = std::round(file_size*1000.0)/1000.0;
    
    if(file_extension != ".txt"){
        throw std::runtime_error("file format must be .txt, sorry for this website are working on it and adding more features for more file formats");
    }
    uintmax_t bytes = chunk_size*1024;
    std::string chunk;
    std::string carry;
    std::vector<char> buffer(bytes);
    
    while(file){
        file.read(buffer.data(), buffer.size());
        
        uintmax_t bytes_read = file.gcount();
        std::string data = carry;
        data.append(buffer.data(), bytes_read);
        //std::cout<<data<<std::endl;
        if(bytes == 0) break;
        
        size_t pos = data.find_last_of(" \t\n");
        if(pos == std::string::npos){
            carry = data;
            continue;
        }
        carry = data.substr(pos+1);
        chunk += data.substr(0, pos+1);
    }
    sentance = chunk;
            
}

std::string loader::get_sentance(){
    return sentance;
}

std::vector<file_details> loader::detail_provider(){
    std::vector<file_details> File_Detail;
    File_Detail.push_back({file_path,file_size,file_extension,normilize, chunk_size});
    return File_Detail;
}

//int main(){
//    loader LOADER("/storage/emulated/0/story.txt",4, false);
//    std::vector<file_details> file_info = LOADER.detail_provider();
//    std::cout<<"file name: "<<file_info[0].file_path<<" file size: "<<file_info[0].file_size<<" kb"<<std::endl;
//}
