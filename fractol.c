/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 07:58:03 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/04 09:07:47 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft/libft.h"
#include "mlx/mlx.h"

int	destroy_and_free(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->img->img);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}

void	put_pixel(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_all(int key, t_mlx *mlx)
{
	ft_printf("Key pressed: %d\n", key);
	if (key == XK_Escape)
	{
		destroy_and_free(mlx);
		exit(0);
	}
	return (0);
}

void	load_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, \
		destroy_and_free, mlx);
	mlx_key_hook(mlx->win, close_all, mlx);
	mlx_mouse_hook(mlx->win, close_all, mlx);
}

void	draw_square(t_mlx *mlx)
{
	int		x;
	int		y;

	x = 0;
	while (x < WIDTH / 2)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			put_pixel(mlx->img, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}

int	main(void)
{
	t_mlx	mlx;
	t_image	image;

	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, WIDTH, HEIGHT, "KIKOOLOLMDR");
	image.img = mlx_new_image(mlx.ptr, WIDTH, HEIGHT);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	mlx.img = &image;
	load_hooks(&mlx);
	draw_square(&mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
