#include <thread>
#include <functional>

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

class Connection{
    public:
    Connection(SOCKET,sockaddr,socklen_t,int);
	Connection(const Connection&) = default;
    void OnData(std::function<void(const std::string& msg)> f);
    void CloseConnection();
    SOCKET getSocket();
    int getTeam();
    std::vector<std::function<void(const std::string& client)>> getDataEvent();

    private:
    void run();
    bool shouldStop;
    int team_;

    std::shared_ptr<std::thread> loop;

    SOCKET clientSocket;
    sockaddr clientAddr_;
    socklen_t clientAddrLength_;
    std::vector<std::function<void(const std::string& client)>> OnDataEvent;
    std::vector<Connection> *myTeam_;
    std::vector<Connection> *otherTeam_;
};