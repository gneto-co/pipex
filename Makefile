# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 10:09:55 by gabriel           #+#    #+#              #
#    Updated: 2024/03/08 11:25:44 by gneto-co         ###   ########.fr        #
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
#-------------------------BONUS PROJECT SOURCE FILES-----------------------------
#--------------------------------------------------------------------------------


BONUS_PROJECT_PATH = ./bonus_files

BONUS_PROJECT = $(BONUS_PROJECT_PATH)/$(NAME).a

$(BONUS_PROJECT):
	@$(MAKE) -C $(BONUS_PROJECT_PATH) --no-print-directory


#--------------------------------------------------------------------------------
#--------------------------COMPILATION SPECIFICATIONS----------------------------
#--------------------------------------------------------------------------------
# -fsanitize=address

CC = cc
OBJ = $(PROJECT) $(LIBFT)
BONUS_OBJ = $(BONUS_PROJECT) $(LIBFT)
CFLAGS = -Wall -Wextra -Werror -g -I$(LIBFT_PATH) -I$(PROJECT_PATH)

#--------------------------------------------------------------------------------
#---------------------------------MAKEFILE RULES---------------------------------
#--------------------------------------------------------------------------------

.DEFAULT_GOAL := all

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@clear
	@echo "\033[32m\n---------- $(NAME) compiled and ready! ----------\033[0m"
	
bonus: $(BONUS_OBJ)
	$(CC) $(BONUS_OBJ) $(CFLAGS) -o $(NAME)
	@clear
	@echo "\033[32m\n---------- $(NAME) compiled and ready! ----------\033[0m"

clean:
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory
	@$(MAKE) -C $(PROJECT_PATH) clean --no-print-directory
	@$(MAKE) -C $(BONUS_PROJECT_PATH) clean --no-print-directory
	@clear
	@echo "\033[31m\033[33m\n---------- program objects cleaned ----------\033[0m"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory
	@$(MAKE) -C $(PROJECT_PATH) fclean --no-print-directory
	@$(MAKE) -C $(BONUS_PROJECT_PATH) fclean --no-print-directory
	@clear
	@echo "\033[31m\033[33m\n--------- program name and objects cleaned ----------\033[0m"
	
re: fclean all
