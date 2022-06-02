#ifndef USER_HPP
# define USER_HPP

#include "GlobalLib.hpp"

class User {
private:
	int		_fd;
	string	_nick;
	string	_username;

	int		_flags[3];

public:
	User();
	User(int fd);
	~User();

	void	setNick(string nick);
	void	setUsername(string username);
	void	setFd(int fd);
	void	setFlags(string input);

	int		getFd();
	int		getFlags(string input);
	string	getUsername();
	string	getNick();


};

#endif