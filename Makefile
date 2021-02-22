# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/19 14:45:55 by user42            #+#    #+#              #
#    Updated: 2021/01/22 14:48:34 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	webserv

SRCS =	webserv.cpp		\
		Config.cpp

SRCS_DIR = ./srcs/

INCS = ./incs/webserv.hpp

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
	@echo "Exec created"

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Objects removed"

fclean: clean
	@rm -f $(NAME)
	@echo "Exec removed"

re: fclean all
