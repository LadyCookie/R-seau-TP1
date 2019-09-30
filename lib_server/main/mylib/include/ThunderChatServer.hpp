#ifndef THUNDERCHATSERVER_HEADER
#define THUNDERCHATSERVER_HEADER

#include <string>
#include <array>
#include<vector>
#include <functional>
#include <thread>
#include "Connection.hpp"
#include <string>

#ifdef _WIN32

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
    ~ThunderChatServer();
    void OnConnect(std::function<void(const std::string& addrClient)> OCCB);
    void OnDisconnect(std::function<void(const std::string& addrClient)> ODCB);
    void Stop();

    private:
    int runner();
    std::thread loop;
    bool shouldStop;

    std::vector<Connection> connections;

    hostent addrServer;
    int port;
    std::vector<std::function<void(const std::string& client)>> callbackOnConnect;
    std::vector<std::function<void(const std::string& client)>> callbackOnDisconnect;
};
#endif //thundrechatserver_header