#include "ThunderChatServer.hpp"
#include <iostream>
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


int ThunderChatServer::runner(){
    int nb_connected=0;
    
    #ifdef _WIN32
    WORD versionRequested;
    WSADATA wsaData;
    versionRequested = MAKEWORD(2,2);
    if(WSAStartup(versionRequested,&wsaData)<0){
        std::cout << "ERROR";
        return EXIT_FAILURE;
    }
    #endif 


    //creation of the socket
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if(s<0){
        std::cout << "ERROR";
        return EXIT_FAILURE;
    }

    //non-blockink behavior
    #ifdef _WIN32
    u_long nonBlocking=1;
    ioctlsocket(s,FIONBIO,&nonBlocking);
    #else
    int flags = fcntl(s, F_GETFL,0);
    flags = (flags | O_NONBLOCK);
    fcntl(s, F_SETFL, flags);
    #endif

    //creation of the distant address
    sockaddr_in addrv4;
    addrv4.sin_family = AF_INET;
    addrv4.sin_port = htons(8888);
    if(inet_pton(AF_INET, "0.0.0.0", &addrv4.sin_addr)<0){
        std::cout << "ERROR";
        return EXIT_FAILURE;
    }

    //Binding
    if(bind(s,(sockaddr*)&addrv4,sizeof(sockaddr))<0){
        std::cout << "ERROR";
        closesocket(s);
        return EXIT_FAILURE;
    }

    //listening for new connections
    if(listen(s,10)<0){
        std::cout << "ERROR";
        return EXIT_FAILURE;
    }



    sockaddr clientAddr;
    socklen_t clientAddrLength;

    //main loop
    while(!shouldStop){
        if(nb_connected < 9)
            if(int clientSocket =accept(s, &clientAddr, &clientAddrLength)<0){
                std::cout << "ERROR";   
            }
            else{
                auto client = new Connection(s, clientAddr, clientAddrLength);
                all_sockets[nb_connected]=*client;
                for(std::function<void(const std::string& clientA)> f : callbackOnConnect)
                {
                    char str[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &clientAddr, str, INET_ADDRSTRLEN);
                    f(str);
                };
                nb_connected++;
            }
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
    callbackOnConnect.push_back(OCCB);
}

void ThunderChatServer::OnDisconnect(std::function<void(const std::string& addrClient)> ODCB){
    callbackOnDisconnect.push_back(ODCB);
}

void ThunderChatServer::Stop(){
    shouldStop=true;
    //waiting main thread to stop
    if(loop.joinable()){
        loop.join();
    }

    //closing all connexions
    std::for_each(all_sockets.begin(),all_sockets.end(), [&](Connection & c) {c.CloseConnection();});

    //closing windows library
    #ifdef _WIN32
    WSACleanup();
    #endif
}
