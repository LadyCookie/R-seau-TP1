#include <iostream>
#include <nlohmann/json.hpp>
#include "ThunderChatServer.hpp"

#include <WinSock2.h>
#include <WS2tcpip.h>

using json = nlohmann::json;

int main(void)
{

    std::cout << "Création du server" << std::endl;
    ThunderChatServer Server = ThunderChatServer("127.0.0.1", 8888);
    std::cout << "Serveur créé" << std::endl;
    //std::cin.ignore();
    while (true) { //std::cout << "server is alive" << std::endl; 
	}
}