#ifndef THUNDERCHATSERVER_HEADER
#define THUNDERCHATSERVER_HEADER

#include <string>
#include<vector>
#include <functional>
#include <thread>
#include "Connection.hpp"

#ifdef _WIN32

#pragma comment(lib, "Ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <WinSock2.h>
#include <WS2tcpip.h>

#else

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>

using SOCKET = inet
#define SD_BOTH SHUT_RDWR
#define closesocket(s) close(s)

#endif

class ThunderChatServer{
    public:
    ThunderChatServer(std::string addr, int port);
    void OnConnect(std::function<void(const std::string& addrClient)> OCCB);
    void OnDisconnect(std::function<void(const std::string& addrClient)> ODCB);
    void Stop();

    private:
    void runner();
    std::unique_ptr<std::thread> loop;

    std::vector<Connection> all_sockets;

    sockaddr_in addrServer;
    int port;
    bool shouldStop;
    std::vector<std::function<void(const std::string& client)>> callbackOnConnect;
    std::vector<std::function<void(const std::string& client)>> callbackOnDisconnect;
};
#endif //thundrechatserver_header