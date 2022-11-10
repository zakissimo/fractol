/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:07:45 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/10 10:58:15 by zhabri           ###   ########.fr       */
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

static void	put_pixel(t_mlx *mlx, t_pixel p)
{
	char	*dst;

	if (p.x >= 0 && p.x <= WIDTH && p.y >= 0 && p.y <= HEIGHT)
	{
		dst = mlx->img->addr + (p.y * mlx->img->line_len + p.x * (mlx->img->bpp
					/ 8));
		*(unsigned int *)dst = p.color;
	}
}

static void	get_boundries(t_pixel *p, t_draw *draw)
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

static int	fractal(t_pixel *p, t_draw *draw)
{
	int		n;
	double	new_a;
	double	new_b;
	double	old_a;
	double	old_b;

	n = 0;
	old_a = p->a;
	old_b = p->b;
	if (draw->julia)
	{
		old_a = draw->c_a;
		old_b = draw->c_b;
	}
	get_boundries(p, draw);
	while (n < draw->max_iter && p->a * p->a + p->b * p->b < 4)
	{
		new_a = p->a * p->a - p->b * p->b;
		new_b = 2 * p->a * p->b;
		p->a = new_a + old_a;
		p->b = new_b + old_b;
		n++;
	}
	return (n);
}

void	draw_fractal(t_mlx *mlx)
{
	int		n;
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
			n = fractal(&p, mlx->draw);
			p.color = get_color(mlx->draw, n, mlx->draw->max_iter);
			put_pixel(mlx, p);
			p.y++;
		}
		p.x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}
