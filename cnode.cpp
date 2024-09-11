#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#pragma comment(lib, "ws2_32.lib")
#define PORT 8000

std::string getIp();
void send_messages(SOCKET sock, std::vector<Node> peers);
void rcv_messages(SOCKET sock);

struct Node 
{
    std::string name;
    std::string ip;
};

std::string ip = getIp();
std::vector<Node> peers = 
{
    {"p2p-node1", "172.18.0.2"}
};

int main()
{
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_TCP);
    sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, ip.c_str(), &my_addr.sin_addr);
    bind(sock, (sockaddr*)&my_addr, sizeof(my_addr));

    //std::thread(rcv_messages, sock).detach();
    send_messages(sock, peers);

    closesocket(sock);
    return 0;
}

std::string getIp()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    hostent* hostInfo = gethostbyname(hostname);
    std::string my_ip = inet_ntoa(*(struct in_addr*)*hostInfo->h_addr_list);
    WSACleanup();
}

void send_messages(SOCKET sock)
{
    while(true)
    {
        for(auto& it: peers)
        {
            time_t timer;
            time(&timer);
            std::string message = "hello at time " + std::to_string(timer) + "\n";
            sendto(sock, message.c_str(), message.size(), 0, (sockaddr*)&it, sizeof(it));
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

/*void rcv_messages(SOCKET sock)
{
    char buffer[1024];
    sockaddr_in from;
    int fromlen = sizeof(from);

    while (true) 
    {
        int bytes_received = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&from, &fromlen);
        std::cout << "Received message from " << from_ip << ": " << buffer << std::endl;
    }
}*/