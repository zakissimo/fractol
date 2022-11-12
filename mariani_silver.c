/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mariani_silver.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:15:10 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/12 17:28:53 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft/libft.h"

void	translate_coordinates(t_mlx *mlx, t_pixel *p)
{
	p->a = (long double)(p->x - mlx->draw->x_offset) / mlx->draw->zoom
		- mlx->draw->x_mouse - mlx->draw->x_key;
	p->b = (long double)(p->y - mlx->draw->y_offset) / mlx->draw->zoom
		- mlx->draw->y_mouse - mlx->draw->y_key;
}

void	color_sub_region(t_boundries *b, t_mlx *mlx)
{
	int		i;
	int		j;
	t_pixel	p;

	i = b->start_x;
	p.color = b->color;
	while (i < b->end_x)
	{
		j = b->start_y;
		while (j < b->end_y)
		{
			p.x = i;
			p.y = j;
			put_pixel(mlx, p);
			j++;
		}
		i++;
	}
}

void	init_b(t_boundries *b, int sx, int sy, int ex, int ey)
{
	b->start_x = sx;
	b->start_y = sy;
	b->end_x = ex;
	b->end_y = ey;
}

void	rec(t_boundries *b, t_mlx *mlx, int (*fractal)(t_pixel *p, t_draw *draw))
{
	if (color_left(b, mlx, fractal) && color_right(b, mlx, fractal)
		&& color_up(b, mlx, fractal) && color_down(b, mlx, fractal))
	{
		color_sub_region(b, mlx);
	}
	else if (b->end_x && b->end_y)
	{
		init_b(b, b->start_x, b->start_y, (b->end_x - b->start_x) / 2, (b->end_y - b->start_y) / 2);
		rec(b, mlx, fractal);
		init_b(b, (b->end_x - b->start_x) / 2, b->start_y, b->end_x, (b->end_y - b->start_y) / 2);
		rec(b, mlx, fractal);
		// init_b(b, (ex - sx) / 2, sy, ex, (ey - sy) / 2);
		// rec((ex - sx) / 2, sy, ex, (ey - sy) / 2, b, mlx, fractal);
		// rec((ex - sx) / 2, ex, (ey - sy) / 2, sy, b, mlx, fractal);
		// init_b(b, (ex - sx) / 2, ex, (ey - sy) / 2, ey);
		// rec(sx, (ex - sx) / 2, (ey - sy) / 2, sy, b, mlx, fractal);
		// init_b(b, sx, (ex - sx) / 2, (ey - sy) / 2, ey);
	}
}

void	complete_canvas(t_mlx *mlx, int (*fractal)(t_pixel *p, t_draw *draw))
{
	t_pixel	p;

	p.x = 0;
	while (p.x < WIDTH)
	{
		p.y = 0;
		while (p.y < HEIGHT)
		{
			if (mlx->img->canvas[p.x][p.y] == -1)
			{
				translate_coordinates(mlx, &p);
				fractal(&p, mlx->draw);
				put_pixel(mlx, p);
			}
			p.y++;
		}
		p.x++;
	}
}

void	ms(t_mlx *mlx, int (*fractal)(t_pixel *p, t_draw *draw))
{
	t_boundries	b;

	init_b(&b, 0, 0, (WIDTH - 1), (HEIGHT - 1));
	// complete_canvas(mlx, fractal);
	rec(&b, mlx, fractal);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}
