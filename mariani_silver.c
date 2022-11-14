/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mariani_silver.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:15:10 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/14 08:45:28 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
				mlx->img->canvas[p.x][p.y] = fractal(&p, mlx->draw);
				put_pixel(mlx, p);
			}
			p.y++;
		}
		p.x++;
	}
}

void	rec(t_boundries b, t_mlx *mlx,
		int (*fractal)(t_pixel *p, t_draw *draw))
{
	t_boundries	sub_screen;
	int			i;

	i = 0;
	while (i < 4)
	{
		sub_screen = init_sub_screen(i, b);
		if (check_color_perimiter(&sub_screen, mlx, fractal))
			color_sub_screen(&sub_screen, mlx);
		else if (b_is_valid(sub_screen))
			rec(sub_screen, mlx, fractal);
		i++;
	}
}

void	ms(t_mlx *mlx, int (*fractal)(t_pixel *p, t_draw *draw))
{
	t_boundries	b;

	b.start_x = 0;
	b.start_y = 0;
	b.end_x = (WIDTH - 1);
	b.end_y = (HEIGHT - 1);
	if (mlx->draw->smooth)
		complete_canvas(mlx, fractal);
	else
		rec(b, mlx, fractal);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}
