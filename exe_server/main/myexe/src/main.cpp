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
#include <iostream>

int main(void)
{
    #ifdef _WIN32
    WORD versionRequested;
    WSADATA wsaData;
    versionRequested = MAKEWORD(2,2);
    if(WSAStartup(versionRequested, &wsaData) < 0)
    {
        std::cout << "Error";
        return EXIT_FAILURE;
    }
    #endif
}