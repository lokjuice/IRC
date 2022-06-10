#include "../../inc/Command.hpp"

void	Command::botHelp() {
	send(_fd, "BOT COMMANDS: <<HELP>> <<ONLINE>> <<>> <<>>", 44, 0);
}