/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nuke.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:07:21 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/12 08:11:14 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	free_canvas(t_image *img)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		free(img->canvas[i]);
		i++;
	}
	free(img->canvas);
}

int	destroy_and_free(t_mlx *mlx)
{
	free_canvas(mlx->img);
	mlx_destroy_image(mlx->ptr, mlx->img->img);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}

void	reset(t_mlx *mlx)
{
	bool	smooth;

	mlx_destroy_image(mlx->ptr, mlx->img->img);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	smooth = false;
	if (mlx->draw->smooth)
		smooth = true;
	free_canvas(mlx->img);
	init_canvas(mlx->img);
	init(mlx, mlx->img, mlx->draw);
	mlx->draw->smooth = smooth;
	load_hooks(mlx);
	mlx_loop(mlx->ptr);
}
