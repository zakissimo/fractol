/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:07:45 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/07 19:19:20 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(t_mlx *mlx, t_pixel p)
{
	char	*dst;

	if (p.x >= 0 && p.x <= WIDTH && p.y >= 0 && p.y <= HEIGHT)
	{
		dst = mlx->img->addr + (p.y * mlx->img->line_len + p.x * (mlx->img->bpp / 8));
		*(unsigned int *)dst = p.color;
	}
}
