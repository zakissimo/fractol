/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_boundries.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:08:32 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/12 15:47:57 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

bool	color_up(t_boundries *b, t_mlx *mlx,
			int (*fractal)(t_pixel *p, t_draw *draw))
{
	int		x;
	int		y;
	t_pixel	p;
	int		prev;

	prev = -1;
	x = b->start_x;
	y = b->start_y;
	b->same = true;
	while (x < b->end_x)
	{
		p.x = x;
		p.y = y;
		translate_coordinates(mlx, &p);
		if (mlx->img->canvas[x][y] == -1)
			mlx->img->canvas[x][y] = fractal(&p, mlx->draw);
		if (prev != -1 && prev != mlx->img->canvas[x][y])
			b->same = false;
		prev = mlx->img->canvas[x][y];
		x++;
	}
	b->color = p.color;
	return (b->same);
}

bool	color_down(t_boundries *b, t_mlx *mlx,
			int (*fractal)(t_pixel *p, t_draw *draw))
{
	int		x;
	int		y;
	t_pixel	p;
	int		prev;

	prev = -1;
	x = b->start_x;
	y = b->end_y;
	b->same = true;
	while (x < b->end_x)
	{
		p.x = x;
		p.y = y;
		translate_coordinates(mlx, &p);
		if (mlx->img->canvas[x][y] == -1)
			mlx->img->canvas[x][y] = fractal(&p, mlx->draw);
		if (prev != -1 && prev != mlx->img->canvas[x][y])
			b->same = false;
		prev = mlx->img->canvas[x][y];
		x++;
	}
	b->color = p.color;
	return (b->same);
}

bool	color_left(t_boundries *b, t_mlx *mlx,
			int (*fractal)(t_pixel *p, t_draw *draw))
{
	int		x;
	int		y;
	t_pixel	p;
	int		prev;

	prev = -1;
	x = b->start_x;
	y = b->start_y;
	b->same = true;
	while (y < b->end_y)
	{
		p.x = x;
		p.y = y;
		translate_coordinates(mlx, &p);
		if (mlx->img->canvas[x][y] == -1)
			mlx->img->canvas[x][y] = fractal(&p, mlx->draw);
		if (prev != -1 && prev != mlx->img->canvas[x][y])
			b->same = false;
		prev = mlx->img->canvas[x][y];
		y++;
	}
	b->color = p.color;
	return (b->same);
}

bool	color_right(t_boundries *b, t_mlx *mlx,
			int (*fractal)(t_pixel *p, t_draw *draw))
{
	int		x;
	int		y;
	t_pixel	p;
	int		prev;

	prev = -1;
	x = b->end_x;
	y = b->start_y;
	b->same = true;
	while (y < b->end_y)
	{
		p.x = x;
		p.y = y;
		translate_coordinates(mlx, &p);
		if (mlx->img->canvas[x][y] == -1)
			mlx->img->canvas[x][y] = fractal(&p, mlx->draw);
		if (prev != -1 && prev != mlx->img->canvas[x][y])
			b->same = false;
		prev = mlx->img->canvas[x][y];
		y++;
	}
	b->color = p.color;
	return (b->same);
}
