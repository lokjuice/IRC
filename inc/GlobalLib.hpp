#ifndef GLOBAL_LIB_H
# define GLOBAL_LIB_H

#include <iostream>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <sstream>
// #include <algorithm>
// #include <cstring>

using std::string;
using std::vector;

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define COLOR_END "\033[0m"

#define BUFFER_SIZE 4096


// class Span
// {
// private:
// public:
// };


void			error(string error);
vector<string>	getParams(string msg, string &firstParam);

#endif