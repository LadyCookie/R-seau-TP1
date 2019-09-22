#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Message{
    public:
    Message(std::string path);
    Message(std::string username, int msg_type, int team, std::string msg);
    ~Message();

    private:
    json data;
};