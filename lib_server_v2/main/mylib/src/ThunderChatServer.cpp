#include "ThunderChatServer.hpp"
#include "Message.hpp"

#include <iostream>
#include <thread>
#include <array>
#include <algorithm>

#define MAX_MSG_SIZE 1024 //to define more precisely

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

using SOCKET = int
#define SD_BOTH SHUT_RDWR
#define closesocket(s) close(s)
#defin INVALID_SOCKET - 1

#endif

void ThunderChatServer::runner()
{
    int nb_connected=0;
    
    #ifdef _WIN32
    WORD versionRequested;
    WSADATA wsaData;
    versionRequested = MAKEWORD(2,2);
    if(WSAStartup(versionRequested,&wsaData)<0){
        std::cout << "ERROR";
    }
    #endif 
	std::cout << "Win library launched" << std::endl;


   

    //main loop
    std::cout << "entering main loop" << std::endl;
    while(!shouldStop){

        // creation of the socket
        SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
        if (s < 0) { std::cout << "ERROR"; }

        std::cout << "Socket succesfully created" << std::endl;

        // Binding
        if (bind(s, (sockaddr*) &addrServer, sizeof(sockaddr)) < 0)
        {
            std::cout << "ERROR";
            closesocket(s);
        }

        std::cout << "Bind succeed" << std::endl;

        // listening for new connections
        if (listen(s, 10) < 0) { std::cout << "ERROR"; }

        std::cout << "Listening new connections" << std::endl;

        sockaddr clientAddr;
        socklen_t clientAddrLength = sizeof(clientAddr);

        if (nb_connected < 9) std::cout << "waiting new connection" << std::endl;

		int clientSocket = accept(s, &clientAddr, &clientAddrLength);

            if(clientSocket	==INVALID_SOCKET){
                std::cout << "ERROR : " << clientSocket << std::endl;   
            }
            else{
                std::cout << "Something is coming" << std::endl;
                //waiting client to tell wich team them belongs to

				/*****Recv juste après accept => récupération de l'équipe pour 
				le mettre dans le bon array de socket******/
                std::array<char, MAX_MSG_SIZE> buffer;
				memset(buffer.data(), '\0', MAX_MSG_SIZE);
                if (int receivedBytes = recv(clientSocket, buffer.data(), MAX_MSG_SIZE, 0) < 0)
                { std::cout << "ERROR RECEPTION FAIL : " << WSAGetLastError() << std::endl;
				}
                else
                {
                    std::string dataStr(buffer.data(), receivedBytes);
					std::cout  << buffer.data() << std::endl;
					std::string client_team_str = buffer.data();
					int client_team = std::stoi(client_team_str);
					std::cout << "Team client : " << client_team << std::endl;
					std::cout << "Client team + 1000 = " << (client_team + 1000) << std::endl; 
					if (client_team == 0) {
						//Mettre dans l'équipe A
                        std::cout << "Creating connection" << std::endl;
						auto client =  Connection(s,clientAddr,clientAddrLength,0);
                        std::cout << "Connection created" << std::endl;
						socket_team_A.push_back(client); 
						std::cout << "Client ajouté à la BDD" << std::endl;
						
						client.OnData([this] (const std::string & msg) { 
							//on parse le json reçu
							json d = json::parse(msg);
							//si on envoie à toute la partie, on envoie à la team adverse
							if (d["msg_type"] == 0) {
								for_each(socket_team_B.begin(), socket_team_B.end(), [&d](Connection c) {
									std::string toSend = d["msg"];
									send(c.getSocket(),toSend.data() , sizeof(toSend.data()) , 0);
								});
							}
							//dans tous les cas, on envoie à sa propre équipe
                            for_each( socket_team_A.begin(),socket_team_A.end(), [&d](Connection c){
                                    std::string toSend = d["msg"];
									send(c.getSocket(), toSend.data() ,sizeof(toSend.data()), 0); });

						});

						std::cout << "OnData Callback configured" << std::endl;

						for(std::function<void(const std::string& clientA)> f : callbackOnConnect)
						{
							char str[INET_ADDRSTRLEN];
							inet_ntop(AF_INET, &clientAddr, str, INET_ADDRSTRLEN);
							f(str);
						};                                               

						std::cout << "Callback OnConnect done" << std::endl;
						nb_connected++;
					}
					if (client_team == 1) {
                        // Mettre dans l'équipe B

                        auto client =Connection(s, clientAddr, clientAddrLength, 1);
                        socket_team_B.push_back(client);

                        for (std::function<void(const std::string& clientA)> f :
                                callbackOnConnect)
                        {
                            char str[INET_ADDRSTRLEN];
                            inet_ntop(AF_INET, &clientAddr, str,
                                        INET_ADDRSTRLEN);
                            f(str);
                        };         
						nb_connected++;
					}
					else {
                        closesocket(s);
					}
                }
            }
    }
}

ThunderChatServer::ThunderChatServer(std::string addr, int port){
    //initialization
    std::cout << "Server initialization" << std::endl; 
    sockaddr_in addrv4;
    addrv4.sin_family = AF_INET;
    addrv4.sin_port = htons(port);
    inet_pton(AF_INET, addr.c_str(), &addrv4.sin_addr);
    addrServer = addrv4;
    std::cout << "Running main thread" << std::endl;
    shouldStop=false;
    //launching server
    loop = std::make_unique<std::thread>(&ThunderChatServer::runner, this);
    std::cout << "Thread launched" << std::endl;
}

void ThunderChatServer::OnConnect(std::function<void(const std::string& addrclient)> OCCB){
    callbackOnConnect.push_back(OCCB);
}

void ThunderChatServer::OnDisconnect(std::function<void(const std::string& addrClient)> ODCB){
    callbackOnDisconnect.push_back(ODCB);
}

void ThunderChatServer::Stop(){
    shouldStop=true;
    //waiting main thread to stop
    if(loop->joinable()){
        loop->join();
    }

    //closing all connexions
    std::for_each(socket_team_A.begin(),socket_team_A.end(), [&](Connection & c) {c.CloseConnection();});
    std::for_each(socket_team_B.begin(), socket_team_B.end(), [&](Connection& c) { c.CloseConnection(); });
    //closing windows library
    #ifdef _WIN32
    WSACleanup();
    #endif
}