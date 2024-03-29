# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 13:42:54 by rboudwin          #+#    #+#              #
#    Updated: 2024/02/12 13:56:50 by rboudwin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= pipex 
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast 
SRCS	:= main.c \
   		   tools.c \
		   pipex.c \
		   validate_args.c
OBJS	:= ${SRCS:.c=.o} Libft/libft.a
BONUS_OBJS := ${BONUS_SRCS:.c=.o} Libft/libft.a 
all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< 

$(NAME): $(OBJS) 
	@$(CC) $(OBJS) -o $(NAME)

Libft/libft.a: 
	$(MAKE) -C Libft/ all
	$(MAKE) -C Libft/ bonus

clean:
	@rm -rf $(OBJS) checker_bonus.o
	rm -f Libft/.bonus;
	$(MAKE) -C Libft/ clean

fclean: clean
	@rm -rf $(NAME)

re: clean fclean all

.PHONY: all, clean, fclean, re 
