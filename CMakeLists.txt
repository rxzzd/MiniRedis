cmake_minimum_required(VERSION 3.15)
project(MiniRedis VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(mini_redis
    src/main.cpp
    src/CacheStore.cpp
)

if (WIN32)
    target_link_libraries(mini_redis ws2_32)
endif()