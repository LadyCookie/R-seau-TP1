#include <string>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#else

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>

using SOCKET = int;
#define SD_BOTH SHUT_RDWR
#define closesocket(s) close(s)
#endif

#include <array>
#include <vector>
#include <iostream>

class ThunderChatServer
{
private:
    /* data */
public:
    ThunderChatServer(/* args */);
    ~ThunderChatServer();

    void onConnect(std::string addr, int port)
    {
        sockaddr clientAddr;
        socklen_t clientAddrSize = sizeof(sockaddr);
        SOCKET client = accept(s, &clientAddr, &clientAddrSize);

        if(client < 0)
        {
            std::cout << "Error";
            closesocket(s);
            return EXIT_FAILURE;
        }

        std::array<char, 512> ipClientStr;
        std::cout << "Client " << inet_ntop(clientAddr.sa_family , &clientAddr, ipClientStr.data(), 512) << " is connected" << std::endl;

    }

    void Stop()
    {
        
    }
};

ThunderChatServer::ThunderChatServer(std::string addr, int port)
{

/*FAIRE UN ARRAY DE SOCKET (SERVEUR, UN SOCKET PAR CLIENT)*/

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0)
    {
        std::cout << "Error";
        return EXIT_FAILURE;
    }

    sockaddr_in addrv4;
    addrv4.sin_family = AF_INET;
    addrv4.sin_port = htons(8888);
    if(inet_pton(AF_INET, "0.0.0.0", &(addrv4.sin_addr)) < 0)  //0.0.0.0 = INADDR_ANY
    {
        std::cout << "Error";
        return EXIT_FAILURE;
    }

    if(bind(s, reinterpret_cast<sockaddr*>(&addrv4), sizeof(sockaddr)) < 0)
    {
        std::cout << "Error";
        closesocket(s);
        return EXIT_FAILURE;
    }

}

ThunderChatServer::~ThunderChatServer()
{
}

