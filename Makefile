#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/04 08:44:16 by zhabri            #+#    #+#              #
#    Updated: 2022/11/12 11:01:14 by zhabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -O3 -g

MLXFLAGS	= -Llibft -lft -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz -lbsd

RM			= rm -f

NAME		= fractol

SRCS		= fractol.c compute.c input_hooks.c palette.c usage.c ft_atof.c \
			  mandelbrot.c julia.c newton.c complex_calculus.c init.c print_canvas.c \
			  nuke.c mariani_silver.c color_boundries.c

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
