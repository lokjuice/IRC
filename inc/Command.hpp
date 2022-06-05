#ifndef COMMAND_HPP
#define COMMAND_HPP

#pragma once //Указывает, что компилятор включает файл заголовка только один раз при компиляции файла с исходным кодом.
#include "GlobalLib.hpp"
#include "User.hpp"
#include "Server.hpp"
// #include "Channel.hpp"

class User;
class Server;
class Channel;

class Command{
    private:

    int     _fd;
    int     _iter;
    string  _msg;
    string  _usrname;
    string  _nick;
    string  _cmd;

    vector<User>    _users;
    vector<string>  _arguments;

    public:
    Command();
    Command(string msg, int fd, string nick, vector<User> &users);
    ~Command();

    //
    vector<User>    getVectorOfUsers();

    int     commandStart(Server &server, struct pollfd fds[]);
    void       checkCommand(Server &server, struct pollfd fds[]);

    void QuitCmd(Server &server, struct pollfd fds[]);
    void NoticeCmd(Server server);
    void NickCmd(Server &server);
    void PrivmsgCmd(Server &server);

    //channel cmds in bot
    void createNewChnl(Server &server);


};
#endif