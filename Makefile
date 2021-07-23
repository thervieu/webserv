# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/19 14:45:55 by user42            #+#    #+#              #
#    Updated: 2021/07/23 10:08:00 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	webserv

SRCS =	Webserv.cpp		\
		Config.cpp		\
		Socket.cpp		\
		Client.cpp		\
		Server.cpp		\
		Response.cpp	\
		Request.cpp		\
		Signal.cpp		\
		CGI.cpp

SRCS_DIR = ./srcs/

INCS = ./incs/Webserv.hpp

FLAGS =	-Wall -Wextra -Werror -std=c++98

OBJ = $(SRCS:.cpp=.o)

OBJS = $(addprefix $(OBJS_DIR),  $(OBJ))

OBJS_DIR =	objs/

PRINT_REQ_AND_RESP = 0

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp $(INCS)
	@mkdir -p $(OBJS_DIR)
	@clang++ -D PRINT_VALUE=$(PRINT_REQ_AND_RESP) $(FLAGS) -c  $< -o $@
	@echo "Compiling $<"

$(NAME): $(OBJS)
	@clang++ $(FLAGS) -o $(NAME) $(OBJS)
	@echo "Exec 'webserv' created"
	@echo "\nUsage: './webserv confs/configuration_file"

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Objects removed"

fclean: clean
	@rm -f $(NAME)
	@echo "Exec removed"

re: fclean all

test: $(NAME)
	@echo "\nplease launch the python tester by executing 'python3 tester_srcs/main.py 8080' in another terminal"
	@echo "executing: './webserv/confs/tester.conf"
	@./webserv confs/tester.conf
