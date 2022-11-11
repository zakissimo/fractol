/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:06:17 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/11 08:29:18 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	key_hook(int key, t_mlx *mlx)
{
	if (key == XK_Escape)
		destroy_and_free(mlx);
	else
	{
		if (key == XK_c)
			pick_color_range(mlx->draw, 0);
		if (key == XK_s)
		{
			if (mlx->draw->smooth)
				mlx->draw->smooth = false;
			else
				mlx->draw->smooth = true;
		}
		if (key == XK_r)
			reset(mlx);
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
		mlx->draw->zoom = mlx->draw->zoom * 1.05 + 1;
	if (key == 5)
		mlx->draw->zoom /= 1.05;
	if (mlx->draw->zoom > ZOOM_MAX)
		mlx->draw->zoom = ZOOM_MAX;
	if (mlx->draw->zoom < ZOOM_MIN)
		mlx->draw->zoom = ZOOM_MIN;
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
		if (mlx->draw->mandelbrot)
			draw_fractal(mlx, &mandelbrot);
		else if (mlx->draw->julia)
			draw_fractal(mlx, &julia);
		else if (mlx->draw->newton)
			draw_fractal(mlx, &newton);
		mlx->draw->redraw = false;
	}
	return (0);
}

static int	key_press_hook(int key, t_mlx *mlx)
{
	int	x;
	int	y;

	if (key == XK_f && mlx->draw->julia)
	{
		mlx_mouse_get_pos(mlx->ptr, mlx->win, &x, &y);
		mlx->draw->c_a = (long double)(x - mlx->draw->x_offset)
			/ mlx->draw->zoom;
		mlx->draw->c_b = (long double)(y - mlx->draw->y_offset)
			/ mlx->draw->zoom;
		mlx->draw->redraw = true;
	}
	return (0);
}

void	load_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask,
		destroy_and_free, mlx);
	mlx_hook(mlx->win, 2, 1L, key_press_hook, mlx);
	mlx_key_hook(mlx->win, key_hook, mlx);
	mlx_mouse_hook(mlx->win, mouse_hook, mlx);
	mlx_loop_hook(mlx->ptr, handle_fractal, mlx);
}
