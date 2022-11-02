#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/04 08:44:16 by zhabri            #+#    #+#              #
#    Updated: 2022/11/02 08:44:39 by zhabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g -lm

RM			= rm -f

NAME		= fractol

SRCS		= fractol.c

OBJS		= $(SRCS:.c=.o)

%.o: %.c
			$(CC) $(CFLAGS) -c $^ -o $@

LIB			= libft/libft.a

MINILIBX	= minilibx-linux/libmlx_Linux.a

$(NAME):	$(OBJS) $(LIB) $(MINILIBX)
			$(CC) $(CFLAGS) $^ -o $@

all:		$(NAME)

$(LIB):
			make -C libft

$(MINILIBX):
			make -C minilibx-linux

clean:
			make clean -C libft
			make clean -C minilibx-linux
			$(RM) $(OBJS) $(OBJSBO)

fclean:		clean
			make fclean -C libft
			$(RM) $(NAME) $(BONUS)

re:			fclean all

.PHONY:		all clean fclean re
