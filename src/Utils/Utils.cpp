#include "../../inc/GlobalLib.hpp"
#include "../../inc/User.hpp"
#include "../../inc/Server.hpp"

vector<string> getParams(string msg, string &firstParam){
	vector<string> params;
	if (!msg.empty()) {
		std::istringstream tempStr(msg.c_str());
		string resStr;

		while (getline(tempStr, resStr, ' ') && resStr != " ")
			params.push_back(resStr);
		firstParam = params[0];
		params.erase(params.begin());

		for(vector<string>::iterator it = params.begin(); it != params.end(); it++)
			(*it).erase(std::remove((*it).begin(), (*it).end(), '\r'), (*it).end());
		for(vector<string>::iterator it = params.begin(); it != params.end(); it++)
			(*it).erase(std::remove((*it).begin(), (*it).end(), '\n'), (*it).end());

		firstParam.erase(std::remove(firstParam.begin(), firstParam.end(), '\r'), firstParam.end());
		firstParam.erase(std::remove(firstParam.begin(), firstParam.end(), '\n'), firstParam.end());
	}
	return params;
}

void	error(string error){
	std::cout << "Error: " << error << std::endl;
	exit(EXIT_FAILURE);
}