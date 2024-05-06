# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 16:25:49 by amabrouk          #+#    #+#              #
#    Updated: 2024/05/06 16:21:13 by amabrouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = mandatory/pipex.c mandatory/parsing.c\
		mandatory/utils_fun.c mandatory/utils_fun2.c
OBJ = $(SRC:.c=.o)

B_SRC = bonus/pipex_bonus.c bonus/get_next_line_utils_bonus.c\
		bonus/get_next_line_bonus.c bonus/utils_fun_bonus.c\
		bonus/parsing_bonus.c bonus/utils_fun2_bonus.c\
		bonus/ft_pipe_bonus.c

B_OBJ = $(B_SRC:.c=.o)

all : $(NAME)

bonus : $(BONUS_NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(BONUS_NAME) : $(B_OBJ)
	$(CC) $(CFLAGS) $(B_OBJ) -o $(BONUS_NAME)

mandatory/%.o : mandatory/%.c headers/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o : bonus/%.c headers/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ) $(B_OBJ)

fclean : clean
	rm -rf $(NAME) $(BONUS_NAME)

re : fclean all