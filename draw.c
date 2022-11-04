/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:07:45 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/04 10:13:08 by zhabri           ###   ########.fr       */
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

void	draw_square(t_mlx *mlx)
{
	t_pixel	p;

	p.x = -WIDTH / 4;
	p.color = 0x00FF0000;
	while (p.x < WIDTH / 4)
	{
		p.y = -HEIGHT / 4;
		while (p.y < HEIGHT / 4)
		{
			put_pixel(mlx->img, p);
			p.y++;
		}
		p.x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
}
