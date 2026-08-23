#include "CacheStore.hpp"

void CacheStore::put(const std::string& key, const std::string& value) {
    store[key] = value;
}

std::string CacheStore::get(const std::string& key){
    auto it = store.find(key);

    if (it != store.end()){
        return it->second;
    }

    return "";
}

void CacheStore::remove(const std::string& key){
    store.erase(key);
}