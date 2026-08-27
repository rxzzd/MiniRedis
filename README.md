# MiniRedis

A thread-safe, in-memory key-value cache store with a built-in TCP server in C++17, including a Python test client.

## Features

- **In-Memory Cache:** Core `CacheStore` class utilizing `std::unordered_map` for O(1) operations.
- **Time-to-Live (TTL):** Key expiration management using `std::chrono::steady_clock` with hybrid cleanup (asynchronous background thread + lazy deletion on read).
- **Thread Safety:** Synchronization using `std::mutex` and `std::lock_guard` (RAII) to prevent data races.
- **TCP Server:** Sockets-based server listening on port 5555 (using Winsock2 on Windows) to parse and execute `SET`, `GET`, and `DEL` commands.
- **Python Client:** A lightweight test script to communicate with the C++ server over TCP.

## Project Structure

- `include/CacheStore.hpp`: Cache class definition.
- `src/CacheStore.cpp`: Cache methods implementation.
- `src/main.cpp`: TCP socket server and event loop.
- `src/client.py`: Python client for testing.
- `CMakeLists.txt`: CMake build configuration.

## Build and Run

### 1. Build the C++ Server
```bash
cmake -G "MinGW Makefiles" -B build
cmake --build build
./build/mini_redis.exe
