# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 17:42:52 by asimoes           #+#    #+#              #
#    Updated: 2021/12/26 16:37:50 by asimoes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=pipex
SRCS=srcs/main.c\
	 srcs/utils.c
OBJS=${SRCS:.c=.o}
CC=cc
CFLAGS=-Wall -Wextra -Werror -I./includes -I.
CLIBS=-L./libft -lft

%.o: %.c includes/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

all: $(NAME)

clean:
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re