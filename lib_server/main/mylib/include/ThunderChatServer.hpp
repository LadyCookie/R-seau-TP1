#include "Message.hpp"
#include <string>
#include<vector>

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
    void OnConnect(std::string addrClient);
    void Stop();

    private:
    std::vector<SOCKET> all_sockets;
};