/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_boundries.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:08:32 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/12 13:59:59 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

bool	color_up(t_boundries *b, t_mlx *mlx,
			int (*fractal)(t_pixel *p, t_draw *draw))
{
	int		i;
	int		j;
	t_pixel	p;
	int		prev;

	prev = -1;
	i = b->start_x;
	j = b->start_y;
	b->same = true;
	while (i < b->end_x)
	{
		p.x = i;
		p.y = j;
		translate_coordinates(mlx, &p);
		if (mlx->img->canvas[i][j] == -1)
			mlx->img->canvas[i][j] = fractal(&p, mlx->draw);
		if (prev != -1 && prev != mlx->img->canvas[i][j])
			b->same = false;
		prev = mlx->img->canvas[i][j];
		i++;
	}
	b->color = p.color;
	return (b->same);
}

bool	color_down(t_boundries *b, t_mlx *mlx,
			int (*fractal)(t_pixel *p, t_draw *draw))
{
	int		i;
	int		j;
	t_pixel	p;
	int		prev;

	prev = -1;
	i = b->start_x;
	j = b->end_y;
	b->same = true;
	while (i < b->end_x)
	{
		p.x = i;
		p.y = j;
		translate_coordinates(mlx, &p);
		if (mlx->img->canvas[i][j] == -1)
			mlx->img->canvas[i][j] = fractal(&p, mlx->draw);
		if (prev != -1 && prev != mlx->img->canvas[i][j])
			b->same = false;
		prev = mlx->img->canvas[i][j];
		i++;
	}
	b->color = p.color;
	return (b->same);
}

bool	color_left(t_boundries *b, t_mlx *mlx,
			int (*fractal)(t_pixel *p, t_draw *draw))
{
	int		i;
	int		j;
	t_pixel	p;
	int		prev;

	prev = -1;
	i = b->start_x;
	j = b->start_y;
	b->same = true;
	while (j < b->end_y)
	{
		p.x = i;
		p.y = j;
		translate_coordinates(mlx, &p);
		if (mlx->img->canvas[i][j] == -1)
			mlx->img->canvas[i][j] = fractal(&p, mlx->draw);
		if (prev != -1 && prev != mlx->img->canvas[i][j])
			b->same = false;
		prev = mlx->img->canvas[i][j];
		j++;
	}
	b->color = p.color;
	return (b->same);
}

bool	color_right(t_boundries *b, t_mlx *mlx,
			int (*fractal)(t_pixel *p, t_draw *draw))
{
	int		i;
	int		j;
	t_pixel	p;
	int		prev;

	prev = -1;
	i = b->end_x;
	j = b->start_y;
	b->same = true;
	while (j < b->end_y)
	{
		p.x = i;
		p.y = j;
		translate_coordinates(mlx, &p);
		if (mlx->img->canvas[i][j] == -1)
			mlx->img->canvas[i][j] = fractal(&p, mlx->draw);
		if (prev != -1 && prev != mlx->img->canvas[i][j])
			b->same = false;
		prev = mlx->img->canvas[i][j];
		j++;
	}
	b->color = p.color;
	return (b->same);
}
