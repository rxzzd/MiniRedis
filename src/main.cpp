#include <iostream>
#include <sstream>
#include <winsock2.h>
#include "CacheStore.hpp"

int main()
{
    std::cout << "Starting Network Mini-Redis" << std::endl;
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cout << "Failed to initialize WSAStartup" << std::endl;
        return 1;
    };

    SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listen_socket == INVALID_SOCKET)
    {
        std::cout << "Invalid socket" << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(5555);

    int bind_result = bind(listen_socket, (sockaddr *)&server_addr, sizeof(server_addr));

    if (bind_result == SOCKET_ERROR)
    {
        std::cout << "Bind socket error" << std::endl;
        WSACleanup();
        return 1;
    }

    int listen_result = listen(listen_socket, SOMAXCONN);

    if (listen_result == SOCKET_ERROR)
    {
        std::cout << "Listen socket error" << std::endl;
        WSACleanup();
        return 1;
    }

    CacheStore cache;

    
    std::cout << "Server listening on 127.0.0.1:5555..." << std::endl;
    
    while (true)
    {
        SOCKET client_socket = accept(listen_socket, nullptr, nullptr);
        if (client_socket == INVALID_SOCKET)
        {
            std::cout << "Accept Failed" << std::endl;
        }
        else
        {
            std::cout << "Client connected successfully" << std::endl;
            char buffer[512];
            int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
            
            if (bytes_received > 0)
            {
                buffer[bytes_received] = '\0';
                std::string message(buffer);
                std::stringstream ss(message);
                
                std::string command;
                std::string key;
                std::string value;
                int ttl;
                
                ss >> command;
                if (command == "SET")
                {
                    ss >> key >> value >> ttl;
                    cache.put(key, value, ttl);
                    send(client_socket, "+OK\n", 4, 0);
                }
                else if (command == "GET")
                {
                    ss >> key;
                    std::string res = cache.get(key);
                    if (res.empty())
                    {
                        send(client_socket, "$-1\n", 4, 0);
                    } else{
                        send(client_socket, res.c_str(), res.length(), 0);
                    }
                }
                else if (command == "DEL")
                {
                    ss >> key;
                    cache.remove(key);
                    send(client_socket, "+OK\n", sizeof("+OK\n"), 0);
                }
            }
        }
        closesocket(client_socket);
    }

    closesocket(listen_socket);
    std::cout << "Cleaning up Winsock..." << std::endl;
    WSACleanup();
    std::cout << "Server stopped" << std::endl;

    return 0;
}