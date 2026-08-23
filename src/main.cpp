#include <iostream>
#include "CacheStore.hpp"

int main() {
    CacheStore cache;

    std::cout << "---- CacheStore Testing ----" << std::endl;

    cache.put("user_1", "TEST_USER_1");
    cache.put("user_2", "TEST_USER_2");

    std::cout << "User 1 " << cache.get("user_1") << std::endl;

    std::cout << "Removing user_1...." << std::endl;
    cache.remove("user_1");

    std::cout << "User_1" << cache.get("user_1") << std::endl;

    std::cout << "User_2 " << cache.get("user_2") << std::endl;

    std::cout << "---- End of Testing ----" << std::endl;

    return 0;
}