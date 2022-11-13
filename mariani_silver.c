/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mariani_silver.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:15:10 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/13 11:10:35 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft/libft.h"

void	complete_canvas(t_mlx *mlx, int (*fractal)(t_pixel *p, t_draw *draw))
{
	t_pixel	p;

	p.x = 0;
	while (p.x < WIDTH)
	{
		p.y = 0;
		while (p.y < HEIGHT)
		{
			if (mlx->img->canvas[p.x][p.y] == -1)
			{
				translate_coordinates(mlx, &p);
				fractal(&p, mlx->draw);
				put_pixel(mlx, p);
			}
			p.y++;
		}
		p.x++;
	}
}

void	translate_coordinates(t_mlx *mlx, t_pixel *p)
{
	p->a = (long double)(p->x - mlx->draw->x_offset) / mlx->draw->zoom
		- mlx->draw->x_mouse - mlx->draw->x_key;
	p->b = (long double)(p->y - mlx->draw->y_offset) / mlx->draw->zoom
		- mlx->draw->y_mouse - mlx->draw->y_key;
}

void	color_sub_region(t_boundries *b, t_mlx *mlx)
{
	int		i;
	int		j;
	t_pixel	p;

	i = b->start_x;
	p.color = b->color;
	while (i < b->end_x)
	{
		j = b->start_y;
		while (j < b->end_y)
		{
			p.x = i;
			p.y = j;
			put_pixel(mlx, p);
			j++;
		}
		i++;
	}
}

t_boundries	init_sub_screens(int n, t_boundries b)
{
	if (n == 0)
	{
		b.end_x = (b.end_x - b.start_x) / 2;
		b.end_y = (b.end_y - b.start_y) / 2;
	}
	else if (n == 1)
	{
		b.start_x = (b.end_x - b.start_x) / 2;
		b.end_y = (b.end_y - b.start_y) / 2;
	}
	else if (n == 2)
	{
		b.start_x = (b.end_x - b.start_x) / 2;
		b.start_y = (b.end_y - b.start_y) / 2;
	}
	else if (n == 3)
	{
		b.start_y = (b.end_y - b.start_y) / 2;
		b.end_x = (b.end_x - b.start_x) / 2;
	}
	return (b);
}

t_boundries	copy_b(t_boundries b)
{
	return (b);
}

void	rec(_boundries b, t_mlx *mlx,
		int (*fractal)(t_pixel *p, t_draw *draw))
{
	t_boundries	sub_screen;
	int			i;

	if (check_color_perimiter(&b, mlx, fractal))
		color_sub_region(&b, mlx);
	else if (b.end_x > b.start_x
		&& b.end_y > b.start_y
		&& (b.end_x - b.start_x) > 2
		&& (b.end_y - b.start_y) > 2)
	{
		i = 0;
		while (i < 4)
		{
			ft_printf("-------------------------------------\n");
			ft_printf("i is %d\n", i);
			sub_screen = init_sub_screens(i, b);
			ft_printf("sx %d, sy %d, ex %d, ey %d\n", b.start_x, b.start_y, b.end_x, b.end_y);
			ft_printf("subx %d, suby %d, subex %d, subey %d\n", sub_screen.start_x, sub_screen.start_y, sub_screen.end_x, sub_screen.end_y);
			ft_printf("-------------------------------------\n");
			rec(sub_screen, mlx, fractal);
			i++;
		}
	}
}

void	ms(t_mlx *mlx, int (*fractal)(t_pixel *p, t_draw *draw))
{
	t_boundries	b;

	b.start_x = 0;
	b.start_y = 0;
	b.end_x = (WIDTH - 1);
	b.end_y = (HEIGHT - 1);
	// complete_canvas(mlx, fractal);
	rec(b, mlx, fractal);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}
