#include "ThunderChatServer.hpp"
#include <thread>

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


void ThunderChatServer::runner(){
    SOCKET s;
    while(!shouldStop){
        s=accept;
        auto client = new Connection(s); //si possible enlever le new
        
    }
}

ThunderChatServer::ThunderChatServer(std::string addr, int port){
    //initialization
    addrServer=*gethostbyname((const char *) &addr);
    port=htons(port);
    shouldStop=false;
    //launching server
    std::thread loop(&runner);
}

void ThunderChatServer::OnConnect(std::function<void(const std::string& addrclient)> OCCB){
    //callbackOnConnect=OCCB;
}

void ThunderChatServer::OnDisconnect(std::function<void(const std::string& addrClient)> ODCB){
    //callbackOnDisconnect=ODCB;
}
