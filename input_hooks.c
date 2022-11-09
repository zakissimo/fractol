/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:06:17 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/09 14:50:47 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	compute_key_offset(int key, t_draw *draw)
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

static int	key_hook(int key, t_mlx *mlx)
{
	if (key == XK_Escape)
	{
		destroy_and_free(mlx);
		exit(0);
	}
	else
	{
		if (key == XK_c)
			pick_color_range(mlx->draw);
		if (key == XK_Right || key == XK_Left || key == XK_Up || key == XK_Down)
			compute_key_offset(key, mlx->draw);
		if (key == XK_minus)
			mlx->draw->max_iter -= 5;
		if (key == XK_equal)
			mlx->draw->max_iter += 5;
		mlx->draw->redraw = true;
	}
	return (0);
}

static int	mouse_hook(int key, int x, int y, t_mlx *mlx)
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

static int	handle_fractal(t_mlx *mlx)
{
	if (mlx->draw->redraw)
	{
		draw_fractal(mlx);
		mlx->draw->redraw = false;
	}
	return (0);
}

void	load_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, destroy_and_free,
		mlx);
	mlx_key_hook(mlx->win, key_hook, mlx);
	mlx_mouse_hook(mlx->win, mouse_hook, mlx);
	mlx_loop_hook(mlx->ptr, handle_fractal, mlx);
}
