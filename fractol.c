/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 07:58:03 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/05 13:28:20 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_mandelbrot(t_mlx *mlx)
{
	t_pixel	p;
	int		n;
	int		max_iter;
	double	new_a;
	double	new_b;
	double	old_a;
	double	old_b;

	max_iter = 100;
	p.x = -WIDTH / 3 * 2;
	while (p.x < WIDTH / 3)
	{
		p.y = -HEIGHT / 2;
		while (p.y < HEIGHT / 2)
		{
			n = 0;
			p.a = (float)p.x / 500;
			p.b = (float)p.y / 500;
			old_a = p.a;
			old_b = p.b;
			while (n < max_iter)
			{
				new_a = p.a * p.a - p.b * p.b;
				new_b = 2 * p.a * p.b;
				p.a = new_a + old_a;
				p.b = new_b + old_b;
				if (fabs(p.a + p.b) > 2)
					break ;
				n++;
			}
			if (n == 100)
				p.color = 0x00000000;
			else
				p.color = 0x00FFFFFF;
			put_pixel(mlx->img, p);
			p.y++;
		}
		p.x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}

int	main(void)
{
	t_mlx	mlx;
	t_image	image;

	init(&mlx, &image);
	load_hooks(&mlx);
	draw_mandelbrot(&mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
