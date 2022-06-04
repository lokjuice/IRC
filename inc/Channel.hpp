#ifndef CHANNEL_HPP
# define CHANNEL_HPP
//masha's commit
#include "GlobalLib.hpp"

class Channel {
private:
    string  _chnlName;
    vector<int> _fds;

public:

    Channel();
    Chanel(string chnlName, int fd);
    ~Channel();

    //
    string      ChnlName();
    vector<int> FdVector();
    int         FdAdmin();

    //setters
    void			doChannelPrivmsg(int fd, string message, string nickname, string username);
};
#endif