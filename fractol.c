/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 07:58:03 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/07 11:36:23 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"

int	get_color(int n, int max_iter)
{
	static const int	tokyo_night[] = {0xF7768E, 0x9ECE6A, 0xE0AF68, 0x7AA2F7, 0x9A7ECC, 0x4ABAAF, 0xA9B1D6};

	if (n == max_iter)
		return (0);
	return (tokyo_night[n % 7]);
}

int	mandelbrot(t_pixel *p, int max_iter, int zoom)
{
	int		n;
	double	new_a;
	double	new_b;
	double	old_a;
	double	old_b;

	n = 0;
	p->a = (float)p->x / zoom;
	p->b = (float)p->y / zoom;
	old_a = p->a;
	old_b = p->b;
	while (n < max_iter && fabsl(p->a + p->b) < 3)
	{
		new_a = p->a * p->a - p->b * p->b;
		new_b = 2 * p->a * p->b;
		p->a = new_a + old_a;
		p->b = new_b + old_b;
		n++;
	}
	return (n);
}

void	draw_mandelbrot(t_mlx *mlx)
{
	int		n;
	t_pixel	p;

	p.x = mlx->draw->start_x;
	while (p.x < mlx->draw->end_x)
	{
		p.y = mlx->draw->start_y;
		while (p.y < mlx->draw->end_y)
		{
			n = mandelbrot(&p, mlx->draw->max_iter, mlx->draw->zoom);
			p.color = get_color(n, mlx->draw->max_iter);
			put_pixel(mlx, p);
			p.y++;
		}
		p.x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}

int	handlebrot(t_mlx *mlx)
{
	if (mlx->draw->redraw)
	{
		draw_mandelbrot(mlx);
		mlx->draw->redraw = false;
	}
	return (0);
}

void	load_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, destroy_and_free,
		mlx);
	mlx_key_hook(mlx->win, key_hook, mlx);
	mlx_mouse_hook(mlx->win, mouse_hook, mlx);
	mlx_loop_hook(mlx->ptr, handlebrot, mlx);
}

int	main(void)
{
	t_mlx	mlx;
	t_image	image;
	t_draw	draw;

	init(&mlx, &image, &draw);
	load_hooks(&mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
