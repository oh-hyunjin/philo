# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 09:56:38 by hyoh              #+#    #+#              #
#    Updated: 2023/02/17 10:56:45 by hyoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	cc
CFLAG	=	-Wall -Wextra -Werror
RM		=	rm -f

SRCS_DIR	=	./src

SRC		=	philo.c	utils.c	before_routine.c
SRC_BN	=	philo.c	utils.c	before_routine.c

OBJ		=	$(addprefix $(SRCS_DIR)/, $(SRC:.c=.o))
OBJ_BN	=	$(addprefix $(SRCS_DIR)/, $(SRC_BN:.c=.o))

ifdef WITH_BONUS
	OBJECT = $(OBJ_BN)
else
	OBJECT = $(OBJ)
endif

all	: $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

$(NAME) : $(OBJECT)
	$(CC) $(CFLAG) $(OBJECT) -o $(NAME)

bonus :
	make WITH_BONUS=1 all

clean :
	$(RM) $(OBJ) $(OBJ_BN)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus