#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/04 08:44:16 by zhabri            #+#    #+#              #
#    Updated: 2022/11/09 15:44:12 by zhabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -O3

MLXFLAGS	= -Llibft -lft -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz -lbsd

RM			= rm -f

NAME		= fractol

SRCS		= fractol.c compute.c input_hooks.c palette.c usage.c

OBJS		= $(SRCS:.c=.o)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			@make --no-print-directory -sC mlx
			@make --no-print-directory -sC libft
			$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -o $@

all:		$(NAME)

clean:
			make clean -sC libft
			make clean -sC mlx
			$(RM) $(OBJS)

fclean:		clean
			make fclean -sC libft
			$(RM) $(NAME)

re:
			make fclean
			make all

.PHONY:		all clean fclean re
