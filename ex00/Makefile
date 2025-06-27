# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 12:13:07 by ilevy             #+#    #+#              #
#    Updated: 2025/06/27 15:27:07 by ilevy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program Name:

NAME:= btc

#Flags and compilers

CPP:= c++
CPP_FLAGS:= -Wall -Wextra -Werror -std=c++98

#Files and Dir
O_DIR:= o_files/
CPP_FILES:= main.cpp BitcoinExchange.cpp
O_FILES:= $(addprefix $(O_DIR), $(CPP_FILES:.cpp=.o))

#To give some color to my makefile~

GREEN := \033[32m
YELLOW := \033[33m
RED := \033[31m
CYAN := \033[36m
MAGENTA:= \033[35m
BLUE := \033[34m
RESET := \033[0m

#Rules:

all:	$(NAME)

$(NAME):	$(O_FILES)
	$(CPP) $(CPP_FLAGS) $(O_FILES) -o $(NAME)
	@echo "$(CYAN)Compiled $(NAME)!$(RESET)"

$(O_DIR)%.o:	./%.cpp | $(O_DIR)
	$(CPP) $(CPP_FLAGS) -c $< -o $@
	@echo "$(CYAN)Compiled $@ files!$(RESET)"

$(O_DIR):
	mkdir -p $(O_DIR)
	@echo "$(MAGENTA)Created the $(O_DIR) directory!$(RESET)"

fclean:clean
	rm -rf $(NAME)
	@echo "$(RED)Fcleaned the $(NAME) program and its .o files!$(RESET)"

clean:
	rm -rf $(O_DIR)
	@echo "$(YELLOW)Cleaned up the $(O_DIR) with clean!$(RESET)"

re:	fclean all

.PHONY: re fclean clean all
