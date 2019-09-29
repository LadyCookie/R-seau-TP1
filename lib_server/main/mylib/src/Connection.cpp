#include "Connection.hpp"

#include <thread>
#include <functional>

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

Connection::Connection(SOCKET s,sockaddr clientAddr,socklen_t clientAddrLength){

}

void Connection::OnData(std::function<void(const std::string& client)> f) {
    OnDataEvent.push_back(f);
};

void Connection::run(){

}

void Connection::CloseConnection(){
    int err = shutdown(clientSocket, SD_BOTH);
    int err = closesocket(clientSocket);
}