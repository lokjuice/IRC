#include <iostream>
#include "../inc/GlobalLib.hpp"
#include "../inc/Server.hpp"

int main(int argc, char **argv)
{
	if (argc != 3){
		error("Error: Wrong count of arguments");
	}

	Server server(atoi(argv[1]), std::string(argv[2]));
	return (0);
}