#include "Message.hpp"
#include <string>
#include<iostream>
#include <fstream>


Message::Message(std::string username, int msg_type, int team, std::string msg){
    json d;
    if(username.size()>24 
    || msg_type<0 || msg_type>1 
    || team <0 || team > 1
    || msg.size()>512){
    }
    else{
        d["username"]=username;
        d["msg_type"]=msg_type;
        d["team"]=team;
        d["msg"]=msg;
    }
    data=d;
}

int Message::getTeam(){
    return(data.at("team"));
}

int Message::getMsgType() {
	return (data.at("msg_type")); 
}

std::string Message::getUsername() {
	return (data.at("username")); 
}

std::string Message::getMsg() {
	return (data.at("msg")); 
}