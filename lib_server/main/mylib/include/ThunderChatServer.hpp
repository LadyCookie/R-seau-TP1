#include "Message.hpp"
#include <string>

class ThunderChatServer{
    public:
    ThunderChatServer(std::string addr, int port);
    ~ThunderChatServer();
    void OnConnect(std::string addrClient);
    void Stop();

    private:
    //sockets
};