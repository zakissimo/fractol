#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/04 08:44:16 by zhabri            #+#    #+#              #
#    Updated: 2022/11/07 08:35:20 by zhabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -O3

MLXFLAGS	= -Llibft -lft -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz -lbsd

RM			= rm -f

NAME		= fractol

SRCS		= fractol.c utils.c draw.c

OBJS		= $(SRCS:.c=.o)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			make -C mlx
			make -C libft
			$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -o $@

all:		$(NAME)

clean:
			make clean -C libft
			make clean -C mlx
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C libft
			$(RM) $(NAME)

re:
			make fclean
			make all

.PHONY:		all clean fclean re
