#include <iostream>
//#include "ThunderChatServer.hpp"
//#include "Message.hpp"
#include <nlohmann/json.hpp>

int main(void)
{
    std::cout << "Hello world, it's me" << std::endl;

    std::cout << "Creating new server" << std::endl;
    //ThunderChatServer Server = ThunderChatServer("127.0.0.0",8888);

    std::cout << "Server Successfully created" << std::endl;
	/*
	Message msg = Message("playerTest", 1, 1, "playerTest n'a rien à dire");
	int team = msg.getTeam();
	std::cout << "The team of the player is : " << team << std::endl;
	*/
}