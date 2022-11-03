/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 07:58:03 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/03 08:20:26 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft/libft.h"
#include "mlx/mlx.h"

void	destroy_and_free(t_mlx mlx)
{
	mlx_clear_window(mlx.ptr, mlx.win);
	mlx_destroy_image(mlx.ptr, mlx.img->img);
	mlx_destroy_window(mlx.ptr, mlx.win);
	mlx_destroy_display(mlx.ptr);
	free(mlx.ptr);
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
	my_mlx_pixel_put(&image, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx.ptr, mlx.win, image.img, 0, 0);
	mlx.img = &image;
	mlx_hook(mlx.win, 2, 1L << 0, close, &mlx);
	mlx_loop(mlx.ptr);
	destroy_and_free(mlx);
	return (0);
}
