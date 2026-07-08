#include "tokenizer/splitter.h"
#include "tokenizer/provider.h"
#include <thread>
#include <mutex>
#include <iostream>
#include <stdexcept>


splitter::splitter(const std::string &sentance, size_t cpu_count, bool use_thread) : sentance(sentance), cpu_count(cpu_count), use_thread(use_thread){
    auto codepoints = utf8_decode(sentance);
    if(use_thread) return;
    try{
        if(codepoints.size()>4000 && !use_thread){
            throw std::runtime_error("warning! use thread function of py_tokenizer for batter optimization and time complexity");
        }
    }
    catch (const std::runtime_error& e){
        std::cerr<<e.what()<<std::endl;
    }
    std::cout<<"running without thread\n"<<std::endl;
    std::vector<std::string> current_word;
    for(size_t i{0}; i<codepoints.size(); ++i){
        if(codepoints[i] ==' '){
            if(!current_word.empty()){
                current_word.push_back("</ws>");
                splited_sentance.push_back(current_word);
            }
            current_word.clear();
        }
        else{
            current_word.push_back(utf8_encode(std::u32string(1, codepoints[i])));
        }
    }
    if(!current_word.empty()){
        current_word.push_back("</ws>");
        splited_sentance.push_back(current_word);
        current_word.clear();
    }
}

void splitter::splitter_thread(const size_t id)
{
    if (sentance.empty())
        return;
        
    auto codepoint = utf8_decode(sentance);
    std::vector<Range> range;
    size_t chunk_size = codepoint.size() / cpu_count;
    for (size_t i{0}; i < cpu_count; ++i)
    {
        size_t start = i * chunk_size;
        size_t end = (i == cpu_count - 1) ? codepoint.size() : (i + 1) * chunk_size;

        range.push_back({start, end});
    }

    if (range[id].start > 0)
    {
        while (range[id].start < codepoint.size() && codepoint[range[id].start] != ' ')
        {
            range[id].start++;
        }
    }
    if (range[id].end < codepoint.size())
    {
        while (range[id].end < codepoint.size() && codepoint[range[id].end] != ' ')
        {
            range[id].end++;
        }
    }

    std::vector<std::string> local_token;
    std::vector<std::string> current_word;
    std::vector<std::vector<std::string>> whole_token;

    //size_t pos = data.find_last_of(" \t\n");
//    std::string word = data.substr(pos + 1);
    for (size_t i = range[id].start; i < range[id].end; ++i)
    {
        if (codepoint[i] == '-')
            continue;
        if (codepoint[i] == ' ')
        {
            if (!current_word.empty())
            {
                for (const auto &c : current_word)
                {
                    auto ct = utf8_decode(c);
                    local_token.push_back(utf8_encode(ct));
                }
                local_token.push_back("</ws>");
                current_word.clear();
            }
            whole_token.push_back(local_token);
            local_token.clear();
            current_word.clear();
        }
        else
        {
            current_word.push_back(utf8_encode(std::u32string(1, codepoint[i])));
        }
    }
    if (!current_word.empty())
    {
        for (const auto &c : current_word)
        {
            auto tk = utf8_decode(c);
            local_token.push_back(utf8_encode(tk));
        }
        local_token.push_back("</ws>");
        whole_token.push_back(local_token);
    }
    std::vector<std::string> token_carrier;

    global_token[id].push_back(whole_token);
    // std::cout<<"vector box: "<<id<<std::endl;
    for (size_t i{0}; i < global_token[id].size(); ++i)
    {
        //std::cout<<"vector start"<<std::endl;
        for (const auto &vector_tk : global_token[id][i])
        {
            for (const auto &word : vector_tk)
            {
                auto w = utf8_decode(word);
                token_carrier.push_back(utf8_encode(w));
            }
            std::lock_guard<std::mutex> lock(mtx);
            all_splited_token.push_back(token_carrier);
            token_carrier.clear();
        }
    }
}

std::vector<std::vector<std::string>> splitter::get_splited_tokens()
{
    if(!splited_sentance.empty()){
        return splited_sentance;
    }
    return all_splited_token;
}

void splitter::thread_runner(){
    global_token.assign(cpu_count, std::vector<std::vector<std::vector<std::string>>>());
    std::vector<std::thread> threads;
    for(size_t i{}; i<cpu_count; ++i){
        threads.push_back(std::thread(&splitter::splitter_thread, this,i));
    }
    
    for(size_t x{0}; x<cpu_count; ++x){
        threads[x].join();
    }
}

size_t splitter::get_cpu_count(){
    return cpu_count;
}

//int main(){
//    splitter Splitter("As he crossed toward the pharmacy at the corner he involuntarily turned his head because of a burst of light that had ricocheted from his temple and saw, with that quick smile with which we greet a rainbow or a rose a blindingly white parallelogram of sky being unloaded from the van—a dresser with mirrors across which, as across a cinema screen passed a flawlessly clear reflection of boughs sliding and swaying not arboreally, but with a human vacillation produced by the nature of those who were carrying this sky these boughs this gliding façade");
//    
//    auto tokens = Splitter.get_splited_tokens();
//    
//    for(const auto& vector : tokens){
//        for(const auto& word : vector){
//            std::cout<<word<<",";
//        }
//    }
//}
