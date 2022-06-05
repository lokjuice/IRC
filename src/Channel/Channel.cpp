#include "../inc/Channel.hpp"
#include "./inc/Server.hpp"

Channel::Channel() { }

Channel::Channel(string chnlName, int fd) : _chnlName(chnlName), _fdAdm(fd) { _fds.push_back(fd); }
// string				Channel::getChannelName(){ return(_channelName); }

vector<int>			Channel::FdVector(){ return(_fds); }
int					Channel::FdAdm(){ return(_fdAdm); }
string				Channel::ChnlName(){ return(_chnlName); }

//
void				Channel::fdsPushBack(int fd) { _fds.push_back(fd); }
void				Channel::setChnlName(string chnlName) { _chnlName = chnlName; }
void				Channel::setFdVector(vector<int> &fds) { _fds = fds; }
void				Channel::setFdAdmin(int fd) { _fdAdm = fd; }
void				Channel::setNewVector(vector<int> &newVector) { _fds = newVector; }

void                newusrConnect(Server &server, int fd, string nick, int id, string chnlName){
    Channel tmpChannel = server.getChannel(id);
    vector<int> tmpFdVector = tmpChannel.FdVector();
    string JoinedUser = ":127.0.0.1 " + nick + " " + "JOIN " + chnlName + "\r\n";

    for(size_t i = 0; i < tmpFdVector.size(); i++){
        if(tmpFdVector[i] != fd)
            send(tmpFdVector[i], JoinedUser.c_str(), JoinedUser.length() + 1, 0);
    }

    string beginMsg = string(":ircserv 331 " + nick + " " + chnlName + ": No topic is set\r\n");

    send(fd, beginMsg.c_str(), beginMsg.length() + 1, 0);
}

bool checkChnlNameExist(vector<Channel> &tmpVector, string chnlName){
    for(vector<Channel>::iterator it = tmpVector.begin(); it != tmpVector.end(); it++){
        if((*it).ChnlName() == chnlName)
            return true;
    }
}

bool Channel::checkUserInChnl(int fd){
    for (vector<int>::iterator it = _fds.begin(); it != _fds.end(); it++){
		if ((*it) == fd)
			return true;
	}
	return false;
}

void Channel::doChannelPrivmsg(int fd, string msg, string nick, string username){
    if(checkUserInChnl(fd)){
        for(vector<int>::iterator it = _fds.begin(); it != _fds.end(); it++){
            if((*it) != fd)
                SendMsgIrcSynt((*it), nick, username, msg);
        }
    }else{
        send(fd, "404 ERR_CANNOTSENDTOCHAN: \r\n", 28, 0);
            std::cout << "NOT IN THE CHANNEL!\n";
    }
}