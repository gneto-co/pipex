# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 10:51:25 by gneto-co          #+#    #+#              #
#    Updated: 2024/02/29 14:47:54 by gneto-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

PROJECT_SOURCES = $(addsuffix .c, \
pipex \
)

SOURCES = $(PROJECT_SOURCES)
	
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) 
	@ar rcs $(NAME) $(OBJECTS)

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all