#include <iostream>
#include "ThunderChatClient.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <WinSock2.h>
#include <WS2tcpip.h>


int main(void)
{

    ThunderChatClient Client = ThunderChatClient("127.0.0.1", "Mazak", 0);
	std::string msg;
	std::string team;
	while (true) {
		std::cout << "Quelle team? 0 : all  1 : my team" << std::endl;
		std::cin >> team;
		std::cout << "Message à envoyer: " << std::endl;
		std::cin >> msg;
		if (team == "0") {
			Client.SendToParty(msg);
		}
		else {
			Client.SendToTeam(msg);
		}
	}
}