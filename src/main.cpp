#include <iostream>
#include "../inc/GlobalLib.hpp"
#include "../inc/Server.hpp"
#include "../inc/Command.hpp"
#include "../inc/Channel.hpp"

int main(int argc, char **argv) {
	if (argc != 3) {
		error("Wrong count of arguments");
	}

	Server server(atoi(argv[1]), std::string(argv[2]));
	struct pollfd fds[10];

	server.setCntConnects(1);

	for (int i; i < 10; i++)
		fds[i].fd = -1;
	fds[0].events = POLL_IN;
	fds[0].revents = 0;

	server.createSocket(server);
	server.bindSocket(server);
	server.listenSocket(server, fds);
	server.startServ(server, fds);

	return (0);
}