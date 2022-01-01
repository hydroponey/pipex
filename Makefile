# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 17:42:52 by asimoes           #+#    #+#              #
#    Updated: 2022/01/01 16:54:08 by asimoes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=pipex
SRCS=srcs/main.c\
	 srcs/utils.c
OBJS=${SRCS:.c=.o}
CC=cc
LFT=./libft/libft.a
CFLAGS=-Wall -Wextra -Werror -I./includes -I.
CLIBS=-L./libft -lft

%.o: %.c includes/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LFT):
	make -C ./libft

$(NAME): $(OBJS) $(LFT)
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean:
		rm -f $(LFT)
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
