/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_boundries.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:08:32 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/14 07:42:02 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	color_up(t_boundries *b, t_mlx *mlx,
			int (*fractal)(t_pixel *p, t_draw *draw))
{
	t_pixel	p;
	int		prev;

	prev = -1;
	p.x = b->start_x;
	p.y = b->start_y;
	b->same = true;
	while (p.x < b->end_x)
	{
		translate_coordinates(mlx, &p);
		if (mlx->img->canvas[p.x][p.y] == -1)
			mlx->img->canvas[p.x][p.y] = fractal(&p, mlx->draw);
		p.color = mlx->img->canvas[p.x][p.y];
		put_pixel(mlx, p);
		if (prev != -1 && prev != mlx->img->canvas[p.x][p.y])
			b->same = false;
		prev = mlx->img->canvas[p.x][p.y];
		p.x++;
	}
	b->color = prev;
	if (b->same)
		return (b->color);
	return (-1);
}

static int	color_down(t_boundries *b, t_mlx *mlx,
			int (*fractal)(t_pixel *p, t_draw *draw))
{
	t_pixel	p;
	int		prev;

	prev = -1;
	p.x = b->start_x;
	p.y = b->end_y;
	b->same = true;
	while (p.x < b->end_x)
	{
		translate_coordinates(mlx, &p);
		if (mlx->img->canvas[p.x][p.y] == -1)
			mlx->img->canvas[p.x][p.y] = fractal(&p, mlx->draw);
		p.color = mlx->img->canvas[p.x][p.y];
		put_pixel(mlx, p);
		if (prev != -1 && prev != mlx->img->canvas[p.x][p.y])
			b->same = false;
		prev = mlx->img->canvas[p.x][p.y];
		p.x++;
	}
	b->color = prev;
	if (b->same)
		return (b->color);
	return (-1);
}

static int	color_left(t_boundries *b, t_mlx *mlx,
			int (*fractal)(t_pixel *p, t_draw *draw))
{
	t_pixel	p;
	int		prev;

	prev = -1;
	p.x = b->start_x;
	p.y = b->start_y;
	b->same = true;
	while (p.y < b->end_y)
	{
		translate_coordinates(mlx, &p);
		if (mlx->img->canvas[p.x][p.y] == -1)
			mlx->img->canvas[p.x][p.y] = fractal(&p, mlx->draw);
		p.color = mlx->img->canvas[p.x][p.y];
		put_pixel(mlx, p);
		if (prev != -1 && prev != mlx->img->canvas[p.x][p.y])
			b->same = false;
		prev = mlx->img->canvas[p.x][p.y];
		p.y++;
	}
	b->color = prev;
	if (b->same)
		return (b->color);
	return (-1);
}

static int	color_right(t_boundries *b, t_mlx *mlx,
			int (*fractal)(t_pixel *p, t_draw *draw))
{
	t_pixel	p;
	int		prev;

	prev = -1;
	p.x = b->end_x;
	p.y = b->start_y;
	b->same = true;
	while (p.y < b->end_y)
	{
		translate_coordinates(mlx, &p);
		if (mlx->img->canvas[p.x][p.y] == -1)
			mlx->img->canvas[p.x][p.y] = fractal(&p, mlx->draw);
		p.color = mlx->img->canvas[p.x][p.y];
		put_pixel(mlx, p);
		if (prev != -1 && prev != mlx->img->canvas[p.x][p.y])
			b->same = false;
		prev = mlx->img->canvas[p.x][p.y];
		p.y++;
	}
	b->color = prev;
	if (b->same)
		return (b->color);
	return (-1);
}

bool	check_color_perimiter(t_boundries *b, t_mlx *mlx,
			int (*fractal)(t_pixel *p, t_draw *draw))
{
	int	up;
	int	down;
	int	left;
	int	right;

	left = color_left(b, mlx, fractal);
	right = color_right(b, mlx, fractal);
	up = color_up(b, mlx, fractal);
	down = color_down(b, mlx, fractal);
	if (left == right
		&& up == down
		&& left == up)
		if (left != -1)
			return (true);
	return (false);
}
