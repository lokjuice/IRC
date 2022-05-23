#ifndef HEAD_HPP
# define HEAD_HPP

#include "GlobalLib.hpp"

class User;

class Server{
private:
	int				_port;
	int				_id;
	int				_channelID;
	int			_listenning;
	int				_cntConnects;
	string			_pswrd;

	// vector<User>	_users;
public:
	Server();
	Server(int port, string pswrd);
	~Server();

	int				getID();
	int				getChannelID();
	int				getPort();
	int				getListenning();
	int				getCntConnects();
};

#endif