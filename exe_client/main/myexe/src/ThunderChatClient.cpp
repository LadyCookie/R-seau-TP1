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

        if(connect(sock_, (SOCKADDR *)&sin, sizeof(sin))<0)
        {
            std::cout << "Connection error";
            return EXIT_FAILURE;
        }
        //on est co
        std::string e = std::to_string(team_); 
        auto equipe = e.c_str();
        send(sock_,equipe,sizeof(equipe),0)
        // on envoie le numéro de la team
       
    }

    void OnMessage(const Message& msg)
    {
        //L'afficher et c'est tout ?
        //On remet sous forme de JSON (Message) et si c'est pour la team : cout<< "Team : " << playerId << " : " <<msg
        //Et si c'est pour la Party, cout<< "Party : " << playerId << " : " <<msg
    }

    void OnDisconnect()
    {
        //Appel du destructeur ?
    }

    void SendToParty(const std::string& msg)
    {
        Message mess = Message(playerId_, 0, team_, msg);
        std::string m = mess.ToSend();
        auto message = m.c_str();
        send(sock_,message,sizeof(message),0);       
    }

    void SendToTeam(const std::string& msg)
    {
        Message mess = Message(playerId_, 1, team_, msg);
        std::string m = mess.ToSend();
        auto message = m.c_str();
        send(sock_,message,sizeof(message),0);
    }

};

ThunderChatClient::ThunderChatClient(std::string serverName,std::string playerId,int team)
{
    serverName_ = serverName;
    playerId_ = playerId;
    team_ = team;
    Connect();
}

ThunderChatClient::~ThunderChatClient()
{
}

