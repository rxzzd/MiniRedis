#if !defined(CACHESTORE_HPP)
#define CACHESTORE_HPP

#include <string>
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <mutex>


struct CacheEntry
{
    std::string value;
    std::chrono::steady_clock::time_point expires_at;
};

class CacheStore
{
private:
    std::unordered_map<std::string, CacheEntry> store;
    std::thread cleaner_thread;
    bool stop_cleaner = false;

    std::mutex mtx;


    void clean_expired_loop();
    

public:
    CacheStore();

    ~CacheStore();


    void put(const std::string &key, const std::string &value, int ttl_seconds);
    std::string get(const std::string &key);
    void remove(const std::string &key);
};

#endif // CACHESTORE_HPP
