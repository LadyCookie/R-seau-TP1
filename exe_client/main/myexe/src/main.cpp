#include <iostream>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <WinSock2.h>
#include <WS2tcpip.h>


int main(void)
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    SOCKET s = socket(AF_INET, SOCK_STREAM,0);
    if(s<0)
    {
        std::cout << "Error";
        return EXIT_FAILURE;

    }

    ThunderChatClient::ThunderChatClient Client;
    Client.Connect();

    #ifdef _Win32
    u_long nonBlocking = 1;
    ioctlsocket(Client.sock_,FIONBIO,&nonBlocking);
    #else
    int flags = fcntl(s, F_GETFL,0);
    flags =(flags | O_NONBLOCK);
    fcntl(s,F_SETFL,flags);
    #endif
    








    shutdown(s,SD_BOTH);
    closesocket(s);

    #ifdef _WIN32
    WSACleanup();
    #endif
}