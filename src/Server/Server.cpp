#include "../../inc/Server.hpp"
#include "../../inc/GlobalLib.hpp"

Server::Server(int port, string pswrd) : _port(port), _channelID(0), _cntConnects(0), _pswrd(pswrd){}

int		Server::getID() { return (_id); }
int		Server::getChannelID() { return (_channelID); }
int		Server::getPort() { return (_port); }
int		Server::getListenning() { return (_listenning); }
int		Server::getCntConnects() { return (_cntConnects); }

void	Server::setListenning(int socket) { _listenning = socket; }
void	Server::setCntConnects(int i) { _cntConnects += i; }
void	Server::addConnection(int i) {}; 
void	Server::allConnection(int i) {};

void 	Server::createSocket(Server &server){
	server.setListenning(socket(AF_INET, SOCK_STREAM, 0));
	if (server.getListenning() == -1){
		error("Can't create a socket");
	}
}

void 	Server::bindSocket(Server &server) {
	int flag = 0;

	if (setsockopt(server.getListenning(), SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) < 0) {
		error("Setsockpt crash");
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(server.getPort());
	hint.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);

	if (bind(server.getListenning(), (sockaddr *)&hint, sizeof(int)) == 1) {
		error("Can't bind");
	}
}

void 	Server::listenSocket(Server &server, struct pollfd fds[]) {
	if (listen(server.getListenning(), SOMAXCONN) == -1) {
		error("Can't listen");
	}

	fds[0].fd = server.getListenning();
	fcntl(fds[0].fd, F_SETFL, O_NONBLOCK);
}

void	Server::startServ(Server &server, struct pollfd fds[]) {
	int flag = 0;
	std::cout << "Server start!\n";
	while(1) {
		int COUNTFD;

		if (flag > 0) {
			std::cout << "Exit\n";
			exit(EXIT_SUCCESS);
		}
		if ((COUNTFD = poll(fds, server.getCntConnects(), -1)) == -1) {
			error("Poll crash");
		}
		for (int i = 0; i < server.getCntConnects(); i++) {
			if (fds[i].fd > 0 && (fds[i].revents & POLLIN) == POLLIN) {
				++flag;
				if (i == 0)
					server.addConnection(flag, fds, i);
				else
					server.allConnection(flag, fds, i);
			}
		}
	}
}



Server::~Server(){}