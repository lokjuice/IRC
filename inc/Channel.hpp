#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "GlobalLib.hpp"
// #include "Command.hpp"
// #include "Server.hpp"

class Channel {
private:
    string  _channelName;
    vector<int> _fds;
    int        _fdAdmin;

public:

    Channel();
    Channel(string chnllName, int fd);
    ~Channel();

    //
    string      ChnlName();
    vector<int> FdVector();
    int         FdAdmin();

    //getters
    vector<int>		getFdVector();
    int				getFdAdmin();
    string			getChannelName();

    //setters
    void			doChannelPrivmsg(int fd, string msg, string nick, string username);
    void            fdsPushBack(int fd);
    void            setChnlName(string chnlName);
    void            setFdVector(vector<int> &fds);
    void            setFdAdmin(int fd);
    void            setNewVector(vector<int> &newVector);
    
    
    bool            checkUserInChnl(int fd);

    //funcs
    void	NewUserConnect(Server &server, int fd, string nickname, int id, string channelName);
    bool	checkChannelNameExist(vector<Channel> &tmpVector, string channelName);
    bool    checkUserInChannel(int fd);
    void	doChannelPrivmsg(int fd, string message, string nickname, string username);
    void	createNewChannel(Server &server);
    int     checkChannelErrors(vector<string> _arguments, int _fd);
    void	doJoinCommand(Server &server);
    void	doPartCommand(Server &server);
    bool    doPartFromChannel(int fd);
    void    doKickCommand(Server &server);
    bool    doKickFromChannel(int fd, int userFd, string userName);
    void    printFds();
};
#endif