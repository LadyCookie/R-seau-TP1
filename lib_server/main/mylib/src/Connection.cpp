#include "Connection.hpp"

#include <thread>
#include <functional>

#define MAX_MSG_SIZE 300 //to define more precisely

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <WinSock2.h>
#include <WS2tcpip.h>

#else

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>

using SOCKET = inet
#define SD_BOTH SHUT_RDWR
#define closesocket(s) close(s)

#endif

//std::thread loop;

/*Connection::Connection(SOCKET s,sockaddr clientAddr,socklen_t clientAddrLength){
    clientSocket=s;
    clientAddr=clientAddr;
    clientAddrLength=clientAddrLength;
    std::thread loop(&run);
}*/

Connection::Connection(SOCKET clientSocket)
{
	this->clientSocket = clientSocket;
	std::thread t_init(&run);
	t = &t_init;
}

void Connection::OnData(std::function<void(const std::string& client)> f) {
    dataEvents.push_back(f);
};

void Connection::run(){

	std::array<char, MAX_MSG_SIZE> buffer;

    while(!shouldStop){
		int receivedBytes = recv(clientSocket, buffer, MAX_MSG_SIZE, 0);
		if (receivedBytes < 0)
		{
			std::cout << "Error" << std::endl;
			closesocket(clientSocket);
			return EXIT_FAILURE;
		}
        for(std::function<void(const std::string& client)> f : OnDataEvent)
        {
            f(buffer);
        };
    }
}

void Connection::CloseConnection(){
    shouldStop=true;
    if(loop.joinable()){
        loop.join();
    }
    int err = shutdown(clientSocket, SD_BOTH);
    int err = closesocket(clientSocket);
}