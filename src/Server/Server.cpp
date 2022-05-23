#include "../../inc/Server.hpp"
#include "../../inc/GlobalLib.hpp"

Server::Server(int port, string pswrd) : _port(port), _channelID(0), _cntConnects(0), _pswrd(pswrd){}

int		Server::getID() { return (_id); }
int		Server::getChannelID() { return (_channelID); }
int		Server::getPort() { return (_port); }
int		Server::getListenning() { return (_listenning); }
int		Server::getCntConnects() { return (_cntConnects); }

int		Server::getID() { return (_id); }
int		Server::getID() { return (_id); }
// int		Server::setListenning(int socket) { _listenning = socket; }

Server::~Server(){}