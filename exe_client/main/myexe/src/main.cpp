#include <iostream>
#include "ThunderChatClient.cpp"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <WinSock2.h>
#include <WS2tcpip.h>


int main(void)
{

    ThunderChatClient Client = ThunderChatClient("127.0.0.1", "playerId", 1);

}