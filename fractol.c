/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 07:58:03 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/12 08:13:59 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_image	image;
	t_draw	draw;

	if ((ac == 2 && (ft_strncmp(av[1], "mandelbrot", 10)
				&& ft_strncmp(av[1], "newton", 6)))
		|| ac == 1 || ac > 4 || ac == 3
		|| (ac == 4 && ft_strncmp(av[1], "julia", 5)))
		usage();
	init_fractal(av, &draw);
	init_canvas(&image);
	init(&mlx, &image, &draw);
	load_hooks(&mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
