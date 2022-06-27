#ifndef COMMAND_HPP
#define COMMAND_HPP

#pragma once //Указывает, что компилятор включает файл заголовка только один раз при компиляции файла с исходным кодом.
#include "GlobalLib.hpp"
#include "User.hpp"
#include "Server.hpp"
#include "Channel.hpp"

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

    int     commandStart(Server &server, struct pollfd fds[], int i);
    void    checkCommand(Server &server, struct pollfd fds[], int i);

    void	QuitCmd(Server &server, struct pollfd fds[]);
    void	NoticeCmd(Server server);
    void	NickCmd(Server &server);
    void	PrivmsgCmd(Server &server);

    // void	NewUserConnect(Server &server, int fd, string nickname, int id, string channelName);
    void	createNewChannel(Server &server);

    void	doJoinCommand(Server &server);
    void	doPartCommand(Server &server);
    void    doKickCommand(Server &server);

    //channel cmds in bot
    void	botHelp(string msg, int fd);
    void	botOnline(string msg, int fd, Server &server);
    void	botTime(int fd);
    void	botPizza(string msg, int fd);
};
#endif