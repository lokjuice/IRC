#ifndef CHANNEL_HPP
# define CHANNEL_HPP
//masha's commit
#include "GlobalLib.hpp"
#include "../inc/Command.hpp"
#include "./inc/Server.hpp"

class Channel {
private:
    string  _chnlName;
    vector<int> _fds;
    int        _fdAdm;

public:

    Channel();
    Channel(string chnllName, int fd);
    ~Channel();

    //
    string      ChnlName();
    vector<int> FdVector();
    int         FdAdm();

    //setters
    void			doChannelPrivmsg(int fd, string msg, string nick, string username);
    void            fdsPushBack(int fd);
    void            setChnlName(string chnlName);
    void            setFdVector(vector<int> &fds);
    void            setFdAdmin(int fd);
    void            setNewVector(vector<int> &newVector);
    
    
    bool            checkUserInChnl(int fd);
    bool            doPartFromChnl(int fd);
};
#endif