#include <string>

class Message{
    public:
    Message(std::string path);
    Message(std::string username, int msg_type, int team, std::string msg);
    ~Message();

    private:
    std::string username;
    int msg_type;
    int team;
    std::string msg;
};