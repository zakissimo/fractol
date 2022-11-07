/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:06:17 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/07 20:08:47 by zhabri           ###   ########.fr       */
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
	if (key == 4)
		mlx->draw->zoom += 7;
	if (key == 5)
		mlx->draw->zoom -= 7;
	mlx->draw->x_mouse = (x - mlx->draw->x_offset) / mlx->draw->zoom;
	mlx->draw->y_mouse = (y - mlx->draw->y_offset) / mlx->draw->zoom;
	mlx->draw->x_offset = x;
	mlx->draw->y_offset = y;
	mlx->draw->redraw = true;
	return (0);
}
