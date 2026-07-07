#pragma once
#include <string>
#include <vector>
#include <thread>
#include <mutex>


inline const size_t cpu = std::thread::hardware_concurrency();

struct Range
{
    size_t start;
    size_t end;
};
class splitter
{
  private:
    std::string sentance;
    std::vector<std::vector<std::string>> splited_sentance;

    size_t cpu_count;
    std::vector<std::vector<std::vector<std::vector<std::string>>>> global_token;
    std::vector<std::vector<std::string>> all_splited_token;
    std::mutex mtx;
    bool use_thread;

  public:
    splitter(const std::string &sentance, size_t cpu_count = cpu, bool use_thread = false);

    void splitter_thread(const size_t id);
    
    std::vector<std::vector<std::string>> get_splited_tokens();
    
    void thread_runner();
    size_t get_cpu_count();
};
