/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:06:17 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/09 11:42:05 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft/libft.h"
#include "mlx/mlx.h"
#include <limits.h>
#include <stdlib.h>

void	init(t_mlx *mlx, t_image *image, t_draw *draw)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "Fractol");
	image->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	image->addr = mlx_get_data_addr(image->img, &image->bpp, &image->line_len,
			&image->endian);
	draw->zoom = 300;
	draw->redraw = true;
	draw->max_iter = 100;
	draw->x_offset = WIDTH / 3 * 2;
	draw->y_offset = HEIGHT / 2;
	draw->x_mouse = 0;
	draw->y_mouse = 0;
	draw->x_key = 0;
	draw->y_key = 0;
	pick_color_range(draw);
	mlx->img = image;
	mlx->draw = draw;
}

int	destroy_and_free(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->img->img);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}

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

void	pick_color_range(t_draw *draw)
{
	static int	n;
	int const	tokyo_night[7] = {0xF7768E, 0x9ECE6A, 0xE0AF68, 0x7AA2F7, 0x9A7ECC, 0x4ABAAF, 0xA9B1D6};
	int const	blue_lancelot[7] = {0x7400b8, 0x6930c3, 0x5e60ce, 0x5390d9, 0x4ea8de, 0x48bfe3, 0x56cfe1};
	int const	seventies[7] = {0x005f73, 0x0a9396, 0xe9d8a6, 0xee9b00, 0xca6702, 0xbb3e03, 0x9b2226};

	if (n % 2 == 0)
		ft_memcpy(draw->color_range, tokyo_night, 7 * sizeof(int));
	if (n % 2 == 1)
		ft_memcpy(draw->color_range, blue_lancelot, 7 * sizeof(int));
	if (n % 3 == 2)
		ft_memcpy(draw->color_range, seventies, 7 * sizeof(int));
	draw->color_range_len = 7;
	n++;
}

int	key_hook(int key, t_mlx *mlx)
{
	if (key == XK_Escape)
	{
		destroy_and_free(mlx);
		exit(0);
	}
	else
	{
		if (key == 99)
			pick_color_range(mlx->draw);
		if (key == XK_Right || key == XK_Left || key == XK_Up || key == XK_Down)
			compute_key_offset(key, mlx->draw);
		mlx->draw->redraw = true;
	}
	return (0);
}

int	mouse_hook(int key, int x, int y, t_mlx *mlx)
{
	long double	prev_mouse_x;
	long double	prev_mouse_y;
	long double	new_mouse_x;
	long double	new_mouse_y;

	prev_mouse_x = (long double)(x - mlx->draw->x_offset) / mlx->draw->zoom;
	prev_mouse_y = (long double)(y - mlx->draw->y_offset) / mlx->draw->zoom;
	if (key == 4)
		mlx->draw->zoom += mlx->draw->zoom / 20 + 1;
	if (key == 5)
		mlx->draw->zoom -= mlx->draw->zoom / 20;
	if (mlx->draw->zoom > ZOOM_MAX)
		mlx->draw->zoom = ZOOM_MAX;
	new_mouse_x = (long double)(x - mlx->draw->x_offset) / mlx->draw->zoom;
	new_mouse_y = (long double)(y - mlx->draw->y_offset) / mlx->draw->zoom;
	mlx->draw->x_mouse += new_mouse_x - prev_mouse_x;
	mlx->draw->y_mouse += new_mouse_y - prev_mouse_y;
	mlx->draw->redraw = true;
	return (0);
}
