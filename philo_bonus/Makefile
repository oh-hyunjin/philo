# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 09:56:38 by hyoh              #+#    #+#              #
#    Updated: 2023/03/13 13:21:25 by hyoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus

CC		=	cc
CFLAG	=	-Wall -Wextra -Werror
RM		=	rm -f

SRC		=	philo_bonus.c\
			action_bonus.c\
			ready_bonus.c\
			utils_bonus.c\

OBJ		=	$(SRC:.c=.o)

all	: $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re