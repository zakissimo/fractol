/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:06:17 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/08 15:03:56 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft/libft.h"
#include "mlx/mlx.h"

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

int	key_hook(int key, t_mlx *mlx)
{
	if (key == XK_Escape)
	{
		destroy_and_free(mlx);
		exit(0);
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
		mlx->draw->zoom += mlx->draw->zoom / 20;
	if (key == 5)
		mlx->draw->zoom -= mlx->draw->zoom / 20;
	new_mouse_x = (long double)(x - mlx->draw->x_offset) / mlx->draw->zoom;
	new_mouse_y = (long double)(y - mlx->draw->y_offset) / mlx->draw->zoom;
	mlx->draw->x_mouse += new_mouse_x - prev_mouse_x;
	mlx->draw->y_mouse += new_mouse_y - prev_mouse_y;
	printf("x is %d | y is %d\n", x, y);
	printf("x_mouse is %Lf | y_mouse is %Lf\n", mlx->draw->x_mouse, mlx->draw->y_mouse);
	mlx->draw->redraw = true;
	return (0);
}
