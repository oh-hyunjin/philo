# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 09:56:38 by hyoh              #+#    #+#              #
#    Updated: 2023/02/25 12:15:52 by hyoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_MDT	=	philo
NAME_BNS	=	philo_bonus

CC			=	cc
CFLAG		=	-Wall -Wextra -Werror
RM			=	rm -f

DIR_MDT		=	./philo_#ㅂㅏ꾸ㅓ야됨!!!!!!!!!!!!!!!!!!!!!!!!!
DIR_BNS		=	./philo_bonus_

SRC_MDT		=	philo.c\
				utils.c\
				before_routine.c\
				status_check.c

SRC_BNS		=	philo_bonus.c\
				action_bonus.c\
				ready_bonus.c\
				utils_bonus.c\

OBJ_MDT		=	$(addprefix $(DIR_MDT)/,$(SRC_MDT:.c=.o))
OBJ_BNS		=	$(addprefix $(DIR_BNS)/,$(SRC_BNS:.c=.o))

ifdef WITH_BONUS
	NAME	=	$(NAME_BNS)
	OBJECT	=	$(OBJ_BNS)
else
	NAME	=	$(NAME_MDT)
	OBJECT	=	$(OBJ_MDT)
endif

all	: $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

$(NAME) : $(OBJECT)
	$(CC) $(CFLAG) $(OBJECT) -o $(NAME)

bonus :
	make WITH_BONUS=1 all

clean :
	$(RM) $(OBJ_MDT) $(OBJ_BNS)

fclean : clean
	$(RM) $(NAME_MDT) $(NAME_BNS)

re : fclean all

.PHONY : all clean fclean re bonus