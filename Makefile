# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/19 14:45:55 by user42            #+#    #+#              #
#    Updated: 2021/06/22 13:02:43 by user42           ###   ########.fr        #
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

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp $(INCS)
	@mkdir -p $(OBJS_DIR)
	@clang++ $(FLAGS) -c  $< -o $@
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
