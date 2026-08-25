#include <iostream>
#include <thread>
#include <chrono>
#include "CacheStore.hpp"

int main() {
    CacheStore cache;

    std::cout << "---- Active deletion test ----" << std::endl;

    cache.put("temp_key", "Hello (TTL 1 sec)", 1);
    
    std::cout << "Main Thread sleeping for 3 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    std::cout << "temp_key " << cache.get("temp_key") << std::endl;

    std::cout << "---- End of Testing ----" << std::endl;

    return 0;
}