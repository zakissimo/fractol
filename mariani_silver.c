/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mariani_silver.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:15:10 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/12 14:56:04 by zhabri           ###   ########.fr       */
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

void	rec(int sx, int sy, int ex, int ey, t_boundries *b, t_mlx *mlx, int (*fractal)(t_pixel *p, t_draw *draw))
{
	b->start_x = sx;
	b->start_y = sy;
	b->end_x = ex;
	b->end_x = ex;
	if (color_left(b, mlx, fractal) && color_right(b, mlx, fractal)
		&& color_up(b, mlx, fractal) && color_down(b, mlx, fractal))
		color_sub_region(b, mlx);
	else if (ex && ey)
	{
		rec(sx, sy, (ex - sx) / 2, (ey - sy) / 2, b, mlx, fractal);
		rec((ex - sx) / 2, ex, sy, (ey - sy) / 2, b, mlx, fractal);
		rec((ex - sx) / 2, ex, (ey - sy) / 2, sy, b, mlx, fractal);
		rec(sx, (ex - sx) / 2, (ey - sy) / 2, sy, b, mlx, fractal);
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

	b.sx = 0;
	b.sy = 0;
	b.ex = WIDTH - 1;
	b.ey = HEIGHT - 1;
	b.start_x = 0;
	b.start_y = 0;
	b.end_x = WIDTH - 1;
	b.end_y = HEIGHT - 1;
	rec(0, 0, WIDTH - 1, HEIGHT - 1, &b, mlx, fractal);
	complete_canvas(mlx, fractal);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}
