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

class Connection{
    public:
    Connection(SOCKET);
    void OnData(std::function<void(const std::string& client)> f) {
        OnDataEvent.push_back(f);
    });
    //OnConnect();
    private:
    void run(){
        while(!stop){
            buffer
            recv buffer //à faire en non-bloquant
            for auto (f : onDataEvent) {
                f(buffer)
            }
                
        }
    };
    std::vector<std::function<void(const std::string& client)>> OnDataEvent;
};