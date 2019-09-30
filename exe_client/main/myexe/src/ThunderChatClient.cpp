//Interface du client
#include <string>
#include <iostream>
#include "Message.hpp"
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
class ThunderChatClient
{
private:
    std::string serverName_;
    std::string playerId_;
    int team_;
    SOCKET sock_;
public:

    /**/
    ThunderChatClient(/*args*/)
    {
        
    };
    ~ThunderChatClient()
    {
        //arrêter le client et déconnecter du serveur
    };



    bool Connect()
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
        
        sock_ = socket(AF_INET, SOCK_STREAM, 0);
        
        SOCKADDR_IN sin;
        sin.sin_family = AF_INET;
        sin.sin_port = htons(8888);
        sin.sin_addr.s_addr = inet_addr("0.0.0.0");
        //Ou inet_pton(AF_INET, "0.0.0.0", &sin.sin_addr); ??

        /*Si c'est un nom de domaine :
        
         if (sin.sin_addr.s_addr == INADDR_NONE)

        {

            host = gethostbyname(sin.sin_addr.s_addr);

            if (host == NULL)

            {

                printf("Unable to resolve server %s\n", sin.sin_addr.s_addr);

                return 1;

            }

            else

                printf("The hostname resolved successfully!\n");

    

            CopyMemory(&sin.sin_addr, host->h_addr_list[0], host->h_length);      // marche pas sur linux, faire un ifdef

        }
        
        */

        connect(sock_, (SOCKADDR *)&sin, sizeof(sin));
        
       
       
    }

    void OnMessage(const Message& msg)
    {
        //Partie JSON
    }

    void OnDisconnect()
    {
        //Appel du destructeur ?
    }

    void SendToParty(const std::string& msg)
    {
        /*
        WINDOWS :
        u_long nonBlocking = 1;
        ioctlsocket(s,FIONBIO,&nonBlocking);
        à mettre dans le main ?

        select-send

        */
    }

    void SendToTeam(const std::string& msg)
    {

    }

};

ThunderChatClient::ThunderChatClient(std::string serverName,std::string playerId,int team)
{
    serverName_ = serverName;
    playerId_ = playerId;
    team_ = team;
}

ThunderChatClient::~ThunderChatClient()
{
}

