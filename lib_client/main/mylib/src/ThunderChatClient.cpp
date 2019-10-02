//Interface du client
#include <string>
#include <iostream>
#include "Message.hpp"
#include "ThunderChatClient.hpp"

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



	ThunderChatClient::ThunderChatClient(std::string serverName, std::string playerId, int team)
	{
		serverName_ = serverName;
		playerId_ = playerId;
		team_ = team;
		Connect();
	}

	ThunderChatClient::~ThunderChatClient()
	{
		shutdown(sock_, SD_BOTH);
		closesocket(sock_);

#ifdef _WIN32
		WSACleanup();
#endif
	};



	bool ThunderChatClient::Connect()
	{
#ifdef _WIN32
		WORD versionRequested;
		WSADATA wsaData;
		versionRequested = MAKEWORD(2, 2);
		if (WSAStartup(versionRequested, &wsaData) < 0)
		{
			std::cout << "Error";
			return EXIT_FAILURE;
		}
#endif

		sock_ = socket(AF_INET, SOCK_STREAM, 0);

		SOCKADDR_IN sin;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(8888);
		//sin.sin_addr.s_addr = inet_addr(serverName_.c_str());
		inet_pton(AF_INET, serverName_.c_str(), &sin.sin_addr);

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

		if (connect(sock_, (SOCKADDR*)&sin, sizeof(sin)) < 0)
		{
			std::cout << "Connection error";
			return EXIT_FAILURE;
		}
		//on est co

		std::string e = std::to_string(team_);
		std::cout << e << std::endl;
		auto equipe = e.c_str();
		std::cout << equipe << std::endl;

		Message IWantThisTeam = Message(playerId_, 0, 1, "");
		std::string IWTT = IWantThisTeam.ToSend();

		std::cout << IWTT << std::endl;
		

		send(sock_, IWTT.c_str(), sizeof(IWTT.c_str()), 0);
		while (true);
		// on envoie le numéro de la team

	}

	void ThunderChatClient::OnMessage(const Message& msg)
	{
		//L'afficher et c'est tout ?
		//On remet sous forme de JSON (Message) et si c'est pour la team : cout<< "Team : " << playerId << " : " <<msg
		//Et si c'est pour la Party, cout<< "Party : " << playerId << " : " <<msg
	}

	void ThunderChatClient::OnDisconnect()
	{
		//Appel du destructeur ?
	}

	void ThunderChatClient::SendToParty(const std::string& msg)
	{
		Message mess = Message(playerId_, 0, team_, msg);
		std::string m = mess.ToSend();
		auto message = m.c_str();
		send(sock_, message, sizeof(message), 0);
	}

	void ThunderChatClient::SendToTeam(const std::string& msg)
	{
		Message mess = Message(playerId_, 1, team_, msg);
		std::string m = mess.ToSend();
		auto message = m.c_str();
		send(sock_, message, sizeof(message), 0);
	}



