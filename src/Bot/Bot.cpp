#include "../../inc/Command.hpp"

void	Command::botHelp() {
	send(_fd, "BOT COMMANDS: <<HELP>> <<ONLINE>> <<>> <<>>\r\n", 46, 0);
}
