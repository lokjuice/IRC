#include "../../inc/Command.hpp"


void	Command::botHelp(string msg, int fd){
	send(fd, "BOT COMMANDS: <<HELP>> <<ONLINE>> <<TIME>> <<PIZZA>>\r\n", 54, 0);
}

void	Command::botOnline(string msg, int fd, Server &server) {
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

void	Command::botTime(int fd) {
	time_t timer = time(NULL);
	string data = ctime(&timer);

	send(fd, data.c_str(), data.length() + 1, 0);
}

void	Command::botPizza(string msg, int fd) {
	std::stringstream ss;

	ss <<   "`````````````````````_____`\r\n"<<
"``````````````__--~~~`````~~~--__`\r\n"<<
"```````````,/'```m#######=@##m````\\.`\r\n"<<
"`````````/'``m###+(_)##+##+###+##m```\\`\r\n"<<
"```````/'``##@=#+####+###+##(_)+####```\\`\r\n"<<
"`````/'``###+#####=@###(_)##+###+#@=##```\\`\r\n"<<
"````/``#(_)##(_)###+###+####=@(_)###+###``\\`\r\n"<<
"```/``@=###+####+###(_)##+##+####+###+###``\\`\r\n"<<
"``|``##+####=@###+####@=#(_)##=@##(_)#+###``|`\r\n"<<
"`|``####(_)####+#(_)+##+###+####+##+#+@=#+#``|`\r\n"<<
"`|``##+#+##+####+##+##+####=@#+(_)##+#+####``|`\r\n"<<
"`|``#(_)####(_)#=@###(_)+###+##+##@=##(_)##``|`\r\n"<<
"`|``##+#(_)#####+######=@##(_)##+###+######``|`\r\n"<<
"``|``##+####+####(_)+####+#+##@=#(_)##=@##``|`\r\n"<<
"```\\``#@=##+#(_)#####+#(_)###+##+##+#####``/`\r\n"<<
"````\\``##(_)###=@#(_)#+#+##(_)#+#(_)#@=#``/`\r\n"<<
"`````\\.`~###+#####+#+#=@##+##@=##+##+##`,/`\r\n"<<
"```````\\.`~+##(_)#####+#(_)##+#(_)+##`,/`\r\n"<<
"`````````\\_`~##+#=@#(_)##+##(_)##~``,/`\r\n"<<
"````````````\\__~~~+####+#####~``__/'`\r\n"<<
"````````````````~--.._____,,--~'`\r\n";
	string finalStr = ss.str();
	send(fd, finalStr.c_str(), finalStr.length() + 1, 0);
}
