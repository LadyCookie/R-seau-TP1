#include <string>
#include "Message.hpp"

class ThunderChatClient{
    public:
    ThunderChatClient(std::string serverName,std::string playerId,int team);
    ~ThunderChatClient();
    bool Connect();
    void OnMessage(const Message& msg);
    void OnDisconnet();
    void SendToParty(const std::string& msg);
    void SendToTeam(const std::string& msg);
};