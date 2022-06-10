#include "../../inc/GlobalLib.hpp"
#include "../../inc/User.hpp"
// #include "../../inc/Command.hpp"
#include<string> 


User::User() { this->_flags[0] = 0; this->_flags[1] = 0; this->_flags[2] = 0; }

User::User(int fd) { this->_fd = fd; this->_flags[0] = 0; this->_flags[1] = 0; this->_flags[2] = 0; }

void	User::setFd(int fd) { this->_fd = fd; }
void	User::setNick(string nick) { _nick = nick; };
void	User::setUsername(string username) { _username = username; };
void	User::setFlags(string input) {
	if (input == "PASS"){ _flags[0] = 1; }
	if (input == "NICK"){ _flags[1] = 1; }
	if (input == "USER"){ _flags[2] = 1; }
}

string	User::getNick() { return (_nick); }
string	User::getUsername() { return (_username); }
int		User::getFd() { return(this->_fd); }
int		User::getFlags(string input) {
	if (input == "PASS"){ return (_flags[0]); }
	if (input == "NICK"){ return (_flags[1]); }
	if (input == "USER"){ return (_flags[2]); }
	if (input == "ALL"){ return getFlags("PASS") && getFlags("NICK") && getFlags("USER") ? 2 : 3; } // 2 - true / 3 - false
	return 0;
}

void	botHelp(string msg, int fd){
	send(fd, "BOT COMMANDS: <<HELP>> <<ONLINE>> <<>> <<>>\n", 45, 0);
}

void	botOnline(string msg, int fd, Server &server) {
	string finalStr;
	std::stringstream ss;
	
	for(int i = 0; i < server.getCntConnects() - 1; i++) {
		if (!server.getUser(i).getUsername().empty()) {
			ss << "ID: ";
			ss << server.getUser(i).getFd();
			ss << " USER: ";
			ss << server.getUser(i).getUsername();
			ss << " NICK: ";
			ss << server.getUser(i).getNick();
			ss << "\n";
		}
	}
	finalStr = ss.str();
	send(fd, finalStr.c_str(), finalStr.length() + 1, 0);
}

int 	User::settingParams(Server &server, string msg, int i, struct pollfd fds[]) {
	int checkFlags = server.getUser(i).getFlags("ALL");

	if (checkFlags == 3)	// if flags are 0
		return server.getUser(i).cmdPars(server, msg, i);

	vector<User> vectorUser = server.getVectorUsers();
	if (msg == "HELP\r\n" || msg == "HELP\n")
		botHelp("HELP" ,server.getUser(i).getFd());
	if (msg == "ONLINE\r\n" || msg == "ONLINE\n")
		botOnline("", server.getUser(i).getFd(), server);
	// Command command(msg, server.getUser(i).getFd(), server.getUser(i).getNick(), vectorUser);
	// return command.commandStart(server, fds);
	return 0;
}

int		checkNicks(Server &server, vector<string> params, int _fd) {
	string newNick = params[0];
	vector<User> tmpVector = server.getVectorUsers();

	if (newNick.length() <= 0 || newNick.length() >= 9) {
		string err = ERR_ERRONEUSNICKNAME(newNick);
		send(_fd, err.c_str(), err.length() + 1, 0);
	}
	for (vector<User>::iterator it = tmpVector.begin(); it != tmpVector.end(); it++) {
		if ((*it).getNick() == newNick) {
			string el = ERR_NICKNAMEINUSE(newNick);
			send(_fd, el.c_str(), el.length() + 1, 0);
			return(1);
		}
	}
	return (0);
}

int		User::nickPars(Server &server, string msg, int i) {
	string noUseParam;
	vector<string> params = getParams(msg, noUseParam);
	
	if (params.size() == 0){
		sendError(ERR_NEEDMOREPARAMS(string("NICK")));
		return (1);
	}
	if (checkNicks(server, params, _fd))
		return 1;

	server.setNick(params[0], i);
	server.setFlags(i, "NICK");
	if (GET_USER_PASSED) {
		send(_fd, NEW_USER(_nick, _username).c_str(), NEW_USER(_nick, _username).length() + 1, 0);
		SEND_ABOUT_NEW_USER;
	}
	return (0);
}

int		User::userPars(Server &server, string msg, int i) {
	string noUseParam;
	vector<string> params = getParams(msg, noUseParam);
	
	if (params.size() == 0){
		sendError(ERR_NEEDMOREPARAMS(string("NICK")));
		return (1);
	}
	server.setUsername(params[0], i);
	server.setFlags(i, "USER");
	if (GET_NICK_PASSED) {
		send(_fd, NEW_USER(_nick, _username).c_str(), NEW_USER(_nick, _username).length() + 1, 0);
		SEND_ABOUT_NEW_USER;
	}
	return (0);
}

int 	User::cmdPars(Server &server, string msg, int i) {
	string firstParam;
	vector<string> params = getParams(msg, firstParam);
	static int flag = 0;
	
	if (!flag && params.size() > 0){
		if (params[0] == "LSPING"){
			string pong = "PONG " + params[1] + "\r\n";
			send(_fd, pong.c_str(), pong.length() + 1, 0);
		}
		++flag;
	}

	if (server.getUser(i).getFlags("PASS") == 0 && firstParam == "PASS") {
		server.getUser(i).validatePassword(server, msg, i);
		return (1);
	}
	else if (server.getUser(i).getFlags("PASS") == 0 && firstParam != "PASS") {
		sendError(ERR_NOTREGISTERED);
		return (1);
	}

	if (!(server.getUser(i).getFlags("USER") && server.getUser(i).getFlags("NICK"))){
		if (firstParam == "NICK\n" || firstParam == "NICK")
			return (server.getUser(i).nickPars(server, msg, i));
		else if (firstParam == "USER\n" || firstParam == "USER")
			return (server.getUser(i).userPars(server, msg, i));
		else {
			sendError(ERR_NOTREGISTERED);
			return (1);
		}
	}

	return 0;
}

void	User::validatePassword(Server &server, string msg, int i) {
	string			noUseParam;
	vector<string>	params = getParams(msg, noUseParam);

	if (params.size() == 0) {
		sendError(ERR_NEEDMOREPARAMS(string("PASS")));
		return ;
	}
	if (params[0] == server.getPassword())
		server.setFlags(i, "PASS");
	else
		sendError(ERR_PASSWDMISMATCH);
}

void	User::sendError(string err) { send(_fd, err.c_str(), err.length() + 1, 0); }

User::~User() {  }