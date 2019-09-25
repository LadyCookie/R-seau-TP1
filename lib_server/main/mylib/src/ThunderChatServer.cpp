#include "ThunderChatServer.hpp"
#include <thread>
#include <algorithm>

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

std::thread t;

ThunderChatServer::ThunderChatServer(std::string addr, int port){
    //initialization
    addrServer=*gethostbyname((const char *) &addr);
    port=htons(port);
    callbackOnConnect={};
    callbackOnDisconnect={};
    all_sockets.reserve(10);

    //running server
    std::thread t(&runner);
}

void ThunderChatServer::runner(){
    std::for_each(all_sockets.begin(),all_sockets.end(),[&](SOCKET & s) {
            //creating socket
            //binding socket
            //recv et send non bloquants
    });
}

void ThunderChatServer::OnConnect(std::function<void(const std::string& addrclient)> OCCB){
    callbackOnConnect=OCCB;
}

void ThunderChatServer::OnDisconnect(std::function<void(const std::string& addrClient)> ODCB){
    callbackOnDisconnect=ODCB;
}

void ThunderChatServer::Stop(){
    if(t.joinable()){
        t.join();
    }
}