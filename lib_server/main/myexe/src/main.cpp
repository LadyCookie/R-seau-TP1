#include <iostream>
#include "ThunderChatServer.hpp"

int main(void)
{
    std::cout << "Hello world, it's me" << std::endl;

    std::cout << "Creating new server" << std::endl;
    ThunderChatServer* Server = new ThunderChatServer("127.0.0.0",8888);

    std::cout << "Server Successfully created" << std::endl;


}