#include "CacheStore.hpp"

CacheStore::CacheStore()
{
    stop_cleaner = false;

    cleaner_thread = std::thread(&CacheStore::clean_expired_loop, this);
};

CacheStore::~CacheStore()
{
    stop_cleaner = true;

    if (cleaner_thread.joinable())
    {
        cleaner_thread.join();
    }
}

void CacheStore::clean_expired_loop()
{
    while (!stop_cleaner)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        auto now = std::chrono::steady_clock::now();

        {
            std::lock_guard<std::mutex> lock(mtx);

            for (auto it = store.begin(); it != store.end();)
            {
                if (now > it->second.expires_at)
                {
                    it = store.erase(it);
                    std::cout << "[Cleaner] Scanned and purged..." << std::endl;
                }
                else
                {
                    it++;
                }
            }
        }
    }
}

void CacheStore::put(const std::string &key, const std::string &value, int ttl_seconds)
{
    std::lock_guard<std::mutex> lock(mtx);
    auto expire_time = std::chrono::steady_clock::now() + std::chrono::seconds(ttl_seconds);
    store[key] = {value, expire_time};
}

std::string CacheStore::get(const std::string &key)
{
    std::lock_guard<std::mutex> lock(mtx);
    auto it = store.find(key);

    if (it != store.end())
    {
        if (std::chrono::steady_clock::now() > it->second.expires_at)
        {
            store.erase(it);
            return "";
        }
        return it->second.value;
    }

    return "";
}

void CacheStore::remove(const std::string &key)
{
    std::lock_guard<std::mutex> lock(mtx);
    store.erase(key);
}
