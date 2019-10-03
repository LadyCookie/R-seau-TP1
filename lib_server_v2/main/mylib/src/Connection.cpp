#include "Connection.hpp"

#include <array>
#include <thread>
#include <functional>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


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

std::thread loop;

Connection::Connection(SOCKET s,sockaddr clientAddr,socklen_t clientAddrLength, int team){

	std::cout << "Attributing values" << std::endl;
    clientSocket=s;
    clientAddr_=clientAddr;
    clientAddrLength_=clientAddrLength;
    team_ = team;
    std::cout << "Launching connexion thread" << std::endl;
    shouldStop = false;
	//SOCKET ALREADY CLOSE AT THIS POINT
    loop = std::make_unique<std::thread>(&Connection::run, this);
    std::cout << "thread connexion launched" << std::endl;
}


void Connection::OnData(std::function<void(const std::string& client)> f) {
    OnDataEvent.push_back(f);
};

void Connection::run(){
	std::array<char, MAX_MSG_SIZE> buffer;
	memset(buffer.data(), '\0', MAX_MSG_SIZE);
    while(!shouldStop){
        int receivedBytes = recv(clientSocket, buffer.data(), MAX_MSG_SIZE, 0);
        if (! (receivedBytes < 0)){
            std::cout << "RECEPTION" << std::endl;
            for(std::function<void(const std::string&)> f : OnDataEvent)
            {
                f(buffer.data());
            };
        }
		else {
			//std::cout << WSAGetLastError() << std::endl;
		}
    }
    
}

void Connection::CloseConnection(){
    shouldStop=true;
    if(loop->joinable()){
        loop->join();
    }
    int err = shutdown(clientSocket, SD_BOTH);
    err = closesocket(clientSocket);
}

SOCKET Connection::getSocket() { return clientSocket; }