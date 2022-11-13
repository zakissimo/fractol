/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 07:37:18 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/13 15:42:53 by zhabri           ###   ########.fr       */
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
	draw->zoom = ZOOM;
	draw->redraw = true;
	draw->max_iter = MAX_ITER;
	draw->x_offset = WIDTH / 3 * 2;
	if (draw->julia || draw->newton)
		draw->x_offset = WIDTH / 2;
	draw->y_offset = HEIGHT / 2;
	draw->x_mouse = 0;
	draw->y_mouse = 0;
	draw->x_key = 0;
	draw->y_key = 0;
	draw->smooth = false;
	pick_color_range(draw, 1);
	mlx->img = image;
	mlx->draw = draw;
}

void	init_fractal(char **av, t_draw *draw)
{
	draw->mandelbrot = false;
	draw->julia = false;
	draw->newton = false;
	if (!strncmp(av[1], "mandelbrot", 10))
		draw->mandelbrot = true;
	if (!strncmp(av[1], "newton", 6))
		draw->newton = true;
	if (!ft_strncmp(av[1], "julia", 5))
	{
		draw->julia = true;
		draw->c_a = ft_atof(av[2], &usage);
		draw->c_b = ft_atof(av[3], &usage);
	}
}

void	init_canvas(t_image *img)
{
	int	x;
	int	y;

	x = 0;
	img->canvas = malloc(WIDTH * sizeof(int *));
	while (x < WIDTH)
	{
		y = 0;
		img->canvas[x] = malloc(HEIGHT * sizeof(int));
		while (y < HEIGHT)
		{
			img->canvas[x][y] = -1;
			y++;
		}
		x++;
	}
}
