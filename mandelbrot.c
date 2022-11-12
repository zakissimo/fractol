/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 08:11:47 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/12 09:01:30 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(t_pixel *p, t_draw *draw)
{
	int		n;
	double	new_a;
	double	new_b;
	double	old_a;
	double	old_b;

	n = 0;
	old_a = p->a;
	old_b = p->b;
	get_boundries(p, draw);
	while (n < draw->max_iter && p->a * p->a + p->b * p->b < 100)
	{
		new_a = p->a * p->a - p->b * p->b;
		new_b = 2 * p->a * p->b;
		p->a = new_a + old_a;
		p->b = new_b + old_b;
		n++;
	}
	draw->z = p->a * p->a + p->b * p->b;
	p->color = get_color(draw, n, draw->max_iter);
	return (p->color);
}
