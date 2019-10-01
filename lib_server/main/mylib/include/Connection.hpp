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
    Connection();
    Connection(SOCKET,sockaddr,socklen_t);
    void OnData(std::function<void(const std::string& client)> f);
    void CloseConnection();

    private:
    void run();
    bool shouldStop;
    SOCKET clientSocket;
    sockaddr clientAddr;
    socklen_t clientAddrLength;
    std::vector<std::function<void(const std::string& client)>> OnDataEvent;
};