#include "tokenizer/provider.h"
#include "tokenizer/json.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstdint>

std::u32string utf8_decode(const std::string &input)
{
    std::u32string result;

    size_t i = 0;
    while (i < input.size())
    {
        uint8_t byte = static_cast<uint8_t>(input[i]);
        char32_t codepoint = 0;

        if ((byte & 0x80) == 0)
        {
            codepoint = byte;
            i += 1;
        }
        else if ((byte & 0xE0) == 0xC0)
        {
            if (i + 1 >= input.size())
                break;

            codepoint =
                ((byte & 0x1F) << 6) |
                (static_cast<uint8_t>(input[i + 1]) & 0x3F);

            i += 2;
        }
        else if ((byte & 0xF0) == 0xE0)
        {
            if (i + 2 >= input.size())
                break;

            codepoint =
                ((byte & 0x0F) << 12) |
                ((static_cast<uint8_t>(input[i + 1]) & 0x3F) << 6) |
                (static_cast<uint8_t>(input[i + 2]) & 0x3F);

            i += 3;
        }
        else if ((byte & 0xF8) == 0xF0)
        {
            if (i + 3 >= input.size())
                break;

            codepoint =
                ((byte & 0x07) << 18) |
                ((static_cast<uint8_t>(input[i + 1]) & 0x3F) << 12) |
                ((static_cast<uint8_t>(input[i + 2]) & 0x3F) << 6) |
                (static_cast<uint8_t>(input[i + 3]) & 0x3F);

            i += 4;
        }
        else
        {
            ++i;
            continue;
        }

        result += codepoint;
    }

    return result;
}

std::string utf8_encode(const std::u32string& input) {
    std::string result;

    for (char32_t codepoint : input) {
        if (codepoint <= 0x7F) {
            result += static_cast<char>(codepoint);
        } 
        else if (codepoint <= 0x7FF) {
            result += static_cast<char>(0xC0 | ((codepoint >> 6) & 0x1F));
            result += static_cast<char>(0x80 | (codepoint & 0x3F));
        } 
        else if (codepoint <= 0xFFFF) {
            result += static_cast<char>(0xE0 | ((codepoint >> 12) & 0x0F));
            result += static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F));
            result += static_cast<char>(0x80 | (codepoint & 0x3F));
        } 
        else if (codepoint <= 0x10FFFF) {
            result += static_cast<char>(0xF0 | ((codepoint >> 18) & 0x07));
            result += static_cast<char>(0x80 | ((codepoint >> 12) & 0x3F));
            result += static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F));
            result += static_cast<char>(0x80 | (codepoint & 0x3F));
        }
    }

    return result;
}                                     

using json = nlohmann::json;


provider::provider(const std::vector<std::vector<std::string>> &whole_merged_tokens, const std::vector<file_details> &file_detail, bool get_file_detail, size_t vocab_size) : whole_merged_tokens(whole_merged_tokens), get_file_detail(get_file_detail), vocab_size(vocab_size)
{
    if (get_file_detail)
    {
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

        file << file_info.dump(4);
    }

    std::cout << "running process...";
    std::vector<std::string> checker;
    size_t id = 0;
    for (const auto &tk : whole_merged_tokens)
    {
        for (const auto &word : tk)
        {
            auto it = std::find(checker.begin(), checker.end(), word);
            if (it == checker.end())
            {
                checker.push_back(word);
            }
        }
    }

    for (const auto &w : checker)
    {
        std::cout << w << " : " << id++ << std::endl;
    }
    json vocabulary;

    size_t i = 0;
    for (const auto &tokens : whole_merged_tokens)
    {
        for (const std::string &token : tokens)
        {
            std::u32string process_text = utf8_decode(token);
            
            std::string ready_text = utf8_encode(process_text);
            
            if (!vocabulary.contains(ready_text))
            {
                vocabulary[ready_text] = i++;
            }
        }
    }

    std::ofstream output_file("vocabulary.json");
    output_file << vocabulary.dump(4);
}

