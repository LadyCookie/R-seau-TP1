#ifndef MESSAGE_HEADER
#define MESSAGE_HEADER

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Message{
    public:
    Message(std::string username, int msg_type, int team, std::string msg);
    ~Message();
    
    int getTeam();

    private:
    json data;
};

#endif