/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mariani_silver.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:15:10 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/12 13:02:48 by zhabri           ###   ########.fr       */
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
			// mlx->img->canvas[i][j] = p.color;
			put_pixel(mlx, p);
			j++;
		}
		i++;
	}
}

void	rec(t_boundries *b, t_mlx *mlx, int (*fractal)(t_pixel *p, t_draw *draw))
{
	if (color_left(b, mlx, fractal) && color_right(b, mlx, fractal)
		&& color_up(b, mlx, fractal) && color_down(b, mlx, fractal))
	{
		b->color = 0xffffffff;
		ft_printf("OKAY\n");
		color_sub_region(b, mlx);
	}
	else
		ft_printf("PAOKAY\n");
		// else if (b.end_y - b.start_y > 21 && b.end_x - b.start_x > 21)
		// {
		// 	b.end_x = (b.end_x - b.start_x) / 2;
		// 	b.end_y = (b.end_y - b.start_y) / 2;
		// 	rec(b, mlx, fractal);
		// 	b.start_x += b.end_x;
		// 	b.end_x = b.ex;
		// 	rec(b, mlx, fractal);
		// 	b.start_y = b.ey / 2;
		// 	b.end_y = b.ey;
		// 	rec(b, mlx, fractal);
		// 	b.start_x = 0;
		// 	b.end_x = b.ex / 2;
		// 	rec(b, mlx, fractal);
		// }
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
	rec(&b, mlx, fractal);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}
