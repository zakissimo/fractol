/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 07:58:03 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/07 08:30:56 by zhabri           ###   ########.fr       */
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
	p->a = (double)p->x / zoom;
	p->b = (double)p->y / zoom;
	old_a = p->a;
	old_b = p->b;
	while (n < max_iter && fabs(p->a + p->b) < 3)
	{
		new_a = p->a * p->a - p->b * p->b;
		new_b = 2 * p->a * p->b;
		p->a = new_a + old_a;
		p->b = new_b + old_b;
		n++;
	}
	return (n);
}

void	draw_mandelbrot(t_mlx *mlx, int zoom)
{
	t_pixel	p;
	int		n;
	int		max_iter;

	max_iter = 100;
	p.x = -WIDTH / 3.0 * 2.0;
	while (p.x < WIDTH / 3.0)
	{
		p.y = -HEIGHT / 2.0;
		while (p.y < HEIGHT / 2.0)
		{
			n = mandelbrot(&p, max_iter, zoom);
			p.color = get_color(n, max_iter);
			put_pixel(mlx->img, p);
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
		draw_mandelbrot(mlx, mlx->draw->zoom);
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
