# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 10:09:55 by gabriel           #+#    #+#              #
#    Updated: 2024/02/29 14:45:03 by gneto-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

#--------------------------------------------------------------------------------
#-----------------------------LIBFT SOURCE FILES---------------------------------
#--------------------------------------------------------------------------------

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory


#--------------------------------------------------------------------------------
#----------------------------PROJECT SOURCE FILES--------------------------------
#--------------------------------------------------------------------------------


PROJECT_PATH = ./$(NAME)_files

PROJECT = $(PROJECT_PATH)/$(NAME).a

$(PROJECT):
	@$(MAKE) -C $(PROJECT_PATH) --no-print-directory

	
#--------------------------------------------------------------------------------
#-----------------------------------MAIN FILES-----------------------------------
#--------------------------------------------------------------------------------

MAINSOURCES = \
main.c

SOURCES = $(MAINSOURCES)

MAIN = $(SOURCES:.c=.o)


#--------------------------------------------------------------------------------
#--------------------------COMPILATION SPECIFICATIONS----------------------------
#--------------------------------------------------------------------------------
# -fsanitize=address

CC = cc
OBJ = $(MAIN) $(PROJECT) $(LIBFT)
CFLAGS = -Wall -Wextra -Werror -Imlx -I$(LIBFT_PATH) -I$(PROJECT_PATH)

#--------------------------------------------------------------------------------
#---------------------------------MAKEFILE RULES---------------------------------
#--------------------------------------------------------------------------------

.DEFAULT_GOAL := all

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@clear
	@echo "\033[32m\n---------- $(NAME) compiled and ready! ----------\033[0m"

clean:
	@rm -f $(MAIN) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory
	@$(MAKE) -C $(PROJECT_PATH) clean --no-print-directory
	@clear
	@echo "\033[31m\033[33m\n---------- program objects cleaned ----------\033[0m"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory
	@$(MAKE) -C $(PROJECT_PATH) fclean --no-print-directory
	@clear
	@echo "\033[31m\033[33m\n--------- program name and objects cleaned ----------\033[0m"
	
re: fclean all
