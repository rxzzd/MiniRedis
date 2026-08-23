#if !defined(CACHESTORE_HPP)
#define CACHESTORE_HPP

#include <string>
#include <unordered_map>

class CacheStore {
    private:
        std::unordered_map<std::string, std::string> store;
    
    public:
        CacheStore() = default;

        void put(const std::string& key, const std::string& value);
        std::string get(const std::string& key);
        void remove(const std::string& key);
};


#endif // CACHESTORE_HPP
