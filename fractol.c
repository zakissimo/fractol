/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 07:58:03 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/02 15:50:10 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft/libft.h"
#include "mlx/mlx.h"

void	destroy_and_free(void *mlx_id, void *mlx_win)
{
	mlx_destroy_window(mlx_id, mlx_win);
	mlx_destroy_display(mlx_id);
	free(mlx_id);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	void	*mlx_id;
	void	*mlx_win;
	t_data	img;

	mlx_id = mlx_init();
	mlx_win = mlx_new_window(mlx_id, WIDTH, HEIGHT, "KIKOOLOLMDR");
	img.img = mlx_new_image(mlx_id, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx_id, mlx_win, img.img, 0, 0);
	mlx_loop(mlx_id);
	destroy_and_free(mlx_id, mlx_win);
	return (0);
}
