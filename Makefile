NAME		=	ircserv

HEADER		=	./inc/

SRCS		=	src/main.cpp \
					src/Utils/Utils.cpp \
					src/Server/Server.cpp \

OBJS		= 	$(patsubst %.cpp,%.o,$(SRCS))

CPP			= 	@c++

CFLAGS		= 	-Wall -Wextra -Werror -std=c++98 -I.

RM			= 	rm -rf

all: 			$(NAME)

$(NAME): 		$(OBJS) $(HEADER)
				$(CPP) $(CFLAGS) -o $(NAME) $(OBJS) 
				@echo "\033[30;42m      Program completed      \033[0m"

clean:
				@${RM} $(OBJS)
				@echo "\033[30;43m        files deleted        \033[0m"

fclean:			
				@${RM} $(OBJS) $(NAME) newFile.txt
				@echo "\033[30;43m        files deleted        \033[0m"

exe:			all clean

re:				fclean all

.PHONY:			all clean fclean re