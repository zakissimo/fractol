/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:07:45 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/11 18:07:19 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	compute_key_offset(int key, t_draw *draw)
{
	if (key == XK_Right)
		draw->x_key += -(draw->x_max - draw->x_min) * 5 / 100;
	if (key == XK_Left)
		draw->x_key += (draw->x_max - draw->x_min) * 5 / 100;
	if (key == XK_Up)
		draw->y_key += (draw->y_max - draw->y_min) * 5 / 100;
	if (key == XK_Down)
		draw->y_key += -(draw->y_max - draw->y_min) * 5 / 100;
}

void	put_pixel(t_mlx *mlx, t_pixel p)
{
	char	*dst;

	if (p.x >= 0 && p.x <= WIDTH && p.y >= 0 && p.y <= HEIGHT)
	{
		dst = mlx->img->addr + (p.y * mlx->img->line_len + p.x * (mlx->img->bpp
					/ 8));
		*(unsigned int *)dst = p.color;
	}
}

void	get_boundries(t_pixel *p, t_draw *draw)
{
	if (p->x == 0 && p->y == 0)
	{
		draw->x_min = p->a;
		draw->y_min = p->b;
	}
	if (p->x == WIDTH - 1 && p->y == HEIGHT - 1)
	{
		draw->x_max = p->a;
		draw->y_max = p->b;
	}
}

void	draw_fractal(t_mlx *mlx, int (*fractal)(t_pixel *p, t_draw *draw))
{
	t_pixel	p;

	p.x = 0;
	while (p.x < WIDTH)
	{
		p.y = 0;
		while (p.y < HEIGHT)
		{
			p.a = (long double)(p.x - mlx->draw->x_offset) / mlx->draw->zoom
				- mlx->draw->x_mouse - mlx->draw->x_key;
			p.b = (long double)(p.y - mlx->draw->y_offset) / mlx->draw->zoom
				- mlx->draw->y_mouse - mlx->draw->y_key;
			fractal(&p, mlx->draw);
			put_pixel(mlx, p);
			p.y++;
		}
		p.x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}
