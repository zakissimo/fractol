/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 07:58:03 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/09 15:16:56 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_image	image;
	t_draw	draw;

	if ((ac == 2 && ft_strncmp(av[1], "mandelbrot", 10))
		|| ac == 1 || ac > 4 || ac == 3
		|| (ac == 4 && ft_strncmp(av[1], "julia", 5)))
		usage();
	init(&mlx, &image, &draw);
	load_hooks(&mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
