#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/04 08:44:16 by zhabri            #+#    #+#              #
#    Updated: 2022/11/02 10:50:16 by zhabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g

MLXFLAGS	= -Llibft -lft -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz -lbsd

RM			= rm -f

NAME		= fractol

SRCS		= fractol.c

OBJS		= $(SRCS:.c=.o)

%.o: %.c
			$(CC) $(CFLAGS) -O3 -c $< -o $@

$(NAME):	$(OBJS)
			make -C mlx
			make -C libft
			$(CC) $(OBJS) $(MLXFLAGS) -o $@

all:		$(NAME)

clean:
			make clean -C libft
			make clean -C mlx
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C libft
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
