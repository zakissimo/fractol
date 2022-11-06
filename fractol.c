/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 07:58:03 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/06 12:39:41 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_color(int n, int max_iter)
{
	const int tokyo_night[] = {0xF7768E,
								0x9ECE6A,
								0xE0AF68,
								0x7AA2F7,
								0x9a7ecc,
								0x4abaaf,
								0xa9b1d6};
	if (n == max_iter)
		return (0);
	if (n == 12345)
		return ((int)((double)n / (double)255 * (double)0x00FFFFFFFF));
	return (tokyo_night[n % 7]);
}

int	get_mandelbrot_iter(t_pixel p, int max_iter)
{
	int		n;
	double	new_a;
	double	new_b;
	double	old_a;
	double	old_b;

	n = 0;
	p.a = (double)p.x / 500;
	p.b = (double)p.y / 500;
	old_a = p.a;
	old_b = p.b;
	// while (n < max_iter && fabs(p.a + p.b) < 3)
	while (n < max_iter && (p.a * p.a + p.b * p.b) < 4)
	{
		new_a = p.a * p.a - p.b * p.b;
		new_b = 2 * p.a * p.b;
		p.a = new_a + old_a;
		p.b = new_b + old_b;
		n++;
	}
	return (n);
}

void	draw_mandelbrot(t_mlx *mlx)
{
	t_pixel	p;
	int		n;
	int		max_iter;

	max_iter = 500;
	p.x = -WIDTH / 3 * 2;
	while (p.x < WIDTH / 3)
	{
		p.y = -HEIGHT / 2;
		while (p.y < HEIGHT / 2)
		{
			n = get_mandelbrot_iter(p, max_iter);
			p.color = get_color(n, max_iter);
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
