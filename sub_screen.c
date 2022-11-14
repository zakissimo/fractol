/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 08:18:52 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/14 08:45:33 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_boundries	init_sub_screen(int n, t_boundries b)
{
	if (n == 0)
	{
		b.end_x -= (b.end_x - b.start_x) / 2;
		b.end_y -= (b.end_y - b.start_y) / 2;
	}
	else if (n == 1)
	{
		b.start_x += (b.end_x - b.start_x) / 2;
		b.end_y -= (b.end_y - b.start_y) / 2;
	}
	else if (n == 2)
	{
		b.start_x += (b.end_x - b.start_x) / 2;
		b.start_y += (b.end_y - b.start_y) / 2;
	}
	else if (n == 3)
	{
		b.start_y += (b.end_y - b.start_y) / 2;
		b.end_x -= (b.end_x - b.start_x) / 2;
	}
	return (b);
}

void	color_sub_screen(t_boundries *b, t_mlx *mlx)
{
	t_pixel	p;

	p.x = b->start_x;
	p.color = b->color;
	while (p.x < b->end_x)
	{
		p.y = b->start_y + 1;
		while (p.y < b->end_y)
		{
			if (mlx->img->canvas[p.x][p.y] == -1)
			{
				mlx->img->canvas[p.x][p.y] = p.color;
				put_pixel(mlx, p);
			}
			p.y++;
		}
		p.x++;
	}
}

bool	b_is_valid(t_boundries b)
{
	return (b.start_x >= 0 && b.start_y >= 0
		&& b.end_x > 0 && b.end_y > 0
		&& b.end_x > b.start_x + 1
		&& b.end_y > b.start_y + 1
		&& b.end_x < WIDTH
		&& b.end_y < HEIGHT);
}
