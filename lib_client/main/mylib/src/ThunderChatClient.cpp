//Interface du client
#include <string>
#include <iostream>
#include "Message.hpp"
#include "ThunderChatClient.hpp"
#include<thread>

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

		//creating the socket
		sock_ = socket(AF_INET, SOCK_STREAM, 0);

		SOCKADDR_IN sin;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(8888);
		inet_pton(AF_INET, serverName_.c_str(), &sin.sin_addr);

		//conecting the socket
		if (connect(sock_, (SOCKADDR*)&sin, sizeof(sin)) < 0)
		{
			std::cout << "Connection error";
			return EXIT_FAILURE;
		}
		//on est co

		std::string e = std::to_string(team_);
		auto equipe = e.c_str();
		send(sock_, equipe, 1, 0); 

		shouldStop = false;
		loop = std::make_unique<std::thread>(&ThunderChatClient::run, this);

	}

	void ThunderChatClient::run() {
		while (!shouldStop) {
			std::array<char, 1024> buffer;
			memset(buffer.data(), '\0', 1024);
			if (int receivedBytes = recv(sock_, buffer.data(), 1024, 0) < 0)
			{
				std::cout << "ERROR RECEPTION FAIL " << std::endl;
			}
			else
			{
				std::cout << buffer.data() << std::endl;
			}
		}
	}

	void ThunderChatClient::OnMessage(const Message& msg)
	{
		Message copyMsg = msg;
		std::cout << copyMsg.getUsername() << " : " << copyMsg.getMsg() << std::endl;
	}

	void ThunderChatClient::OnDisconnect()
	{
		shouldStop = true;
	}

	void ThunderChatClient::SendToParty(const std::string& msg)
	{
		Message mess = Message(playerId_, 0, team_, msg);
		std::string m = mess.ToSend();
		auto message = m.c_str();
		send(sock_, message, sizeof(m), 0);
	}

	void ThunderChatClient::SendToTeam(const std::string& msg)
	{
		Message mess = Message(playerId_, 1, team_, msg);
		std::string m = mess.ToSend();
		auto message = m.c_str();
		send(sock_, message, sizeof(m), 0);
	}



