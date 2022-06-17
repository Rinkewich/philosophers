# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fardath <fardath@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 10:42:26 by fardath           #+#    #+#              #
#    Updated: 2022/06/17 13:26:50 by fardath          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus
SRCS	= 	main.c\
			init.c\
			logs.c\
			utils.c\
			what_do.c
OBJS	= $(SRCS:.c=.o)
HEADER	= philosophers.h
CC		= gcc
FLAGS	=	-Wall -Wextra -Werror
INCLUDE	= -lpthread
.PHONY:	all clean fclean re 

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $<  -o $(<:.c=.o)