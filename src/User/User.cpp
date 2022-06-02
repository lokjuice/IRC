#include "../../inc/GlobalLib.hpp"
#include "../../inc/User.hpp"

User::User() { this->_flags[0] = 0; this->_flags[1] = 0; this->_flags[2] = 0; }

User::User(int fd) { this->_fd = fd; this->_flags[0] = 0; this->_flags[1] = 0; this->_flags[2] = 0; }

void	User::setFd(int fd) { this->_fd = fd; }
void	User::setNick(string nick) { _nick = nick; };
void	User::setUsername(string username) { _username = username; };
void	User::setFlags(string input) {
	if (strcmp(input.c_str(), "PASS") == 0){ _flags[0] = 1; } 
	if (strcmp(input.c_str(), "NICK") == 0){ _flags[1] = 1; }
	if (strcmp(input.c_str(), "USER") == 0){ _flags[2] = 1; }
}

string	User::getNick() { return (_nick); }
string	User::getUsername() { return (_username); }
int		User::getFd() { return(this->_fd); }
int		User::getFlags(string input) {
	if (strcmp(input.c_str(), "PASS") == 0){ return (_flags[0]); } 
	if (strcmp(input.c_str(), "NICK") == 0){ return (_flags[1]); }
	if (strcmp(input.c_str(), "USER") == 0){ return (_flags[2]); }
	if (strcmp(input.c_str(), "ALL") == 0){ return getFlags("PASS") && getFlags("NICK") && getFlags("USER") ? 2 : 3; } // 2 - true / 3 - false

	return 0;
}

User::~User() {  }