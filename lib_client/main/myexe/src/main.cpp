#include <iostream>
#include "ThunderChatClient.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <WinSock2.h>
#include <WS2tcpip.h>


int main(void)
{
	std::string msg;
	std::string team;

	int whichTeam = -1;
	std::cout << "Dans quelle équipe voulez-vous jouer ? (0 = Team A, 1 = Team B)" << std::endl;
	while (whichTeam != 0 && whichTeam != 1) {
		std::cin >> whichTeam;
	}
	ThunderChatClient Client = ThunderChatClient("127.0.0.1", "Mazak", whichTeam);

	while (true) {
		std::cout << "A qui envoyer? (0=tout le monde, 1=votre équipe)" << std::endl;
		std::cin >> team;
		std::cout << "Message à envoyer: " << std::endl;
		std::cin >> msg;
		if (stoi(team) == whichTeam) {
			Client.SendToParty(msg);
		}
		else {
			Client.SendToTeam(msg);
		}
	}
}