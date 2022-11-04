/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:07:45 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/04 12:47:34 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(t_image *img, t_pixel p)
{
	char	*dst;

	p.x += WIDTH / 2;
	p.y += HEIGHT / 2;
	dst = img->addr + (p.y * img->line_len + p.x * (img->bpp / 8));
	*(unsigned int *)dst = p.color;
}

void	draw_circle(t_mlx *mlx, int radius)
{
	t_pixel	p;

	p.x = -radius;
	p.color = 0x000000FF;
	while (p.x < radius)
	{
		p.y = -radius;
		while (p.y < radius)
		{
			if (sqrt(pow(p.x, 2) + pow(p.y, 2)) <= radius)
				put_pixel(mlx->img, p);
			p.y++;
		}
		p.x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}

void	draw_square(t_mlx *mlx, int len)
{
	t_pixel	p;

	p.x = -len;
	p.color = 0x00FF0000;
	while (p.x < len)
	{
		p.y = -len;
		while (p.y < len)
		{
			put_pixel(mlx->img, p);
			p.y++;
		}
		p.x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}