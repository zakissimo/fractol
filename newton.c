/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 08:06:33 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/11 16:49:06 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

float	c_abs(t_complex z)
{
	return (sqrt(z.real * z.real + z.imaginary * z.imaginary));
}

int	color_from_distance(t_complex z)
{
	t_complex	root_one;
	t_complex	root_two;
	t_complex	root_three;
	t_complex	diff;

	root_one.real = 1;
	root_one.imaginary = 0;
	root_two.real = -.5;
	root_two.imaginary = sqrt(3) / 2;
	root_three.real = -.5;
	root_three.imaginary = -sqrt(3) / 2;
	diff = substract(&z, &root_one);
	if (fabsl(diff.real) < TOL && fabsl(diff.imaginary) < TOL)
		return (0x00BE211E);
	diff = substract(&z, &root_two);
	if (fabsl(diff.real) < TOL && fabsl(diff.imaginary) < TOL)
		return (0x004ED337);
	diff = substract(&z, &root_three);
	if (fabsl(diff.real) < TOL && fabsl(diff.imaginary) < TOL)
		return (0x003947D5);
	return (0x00000000);
}

t_complex	*compute_new_z(t_complex *z, t_complex *one, t_complex *three)
{
	t_complex	f;
	t_complex	d;
	t_complex	tmp;

	tmp = power(z, 3);
	f = substract(&tmp, one);
	tmp = power(z, 2);
	d = product(&tmp, three);
	tmp = divide(&f, &d);
	*z = substract(z, &tmp);
	return (z);
}

int	newton(t_pixel *p, t_draw *draw)
{
	int			n;
	t_complex	z;
	t_complex	one;
	t_complex	three;

	n = 0;
	z.real = p->a;
	z.imaginary = p->b;
	one.real = 1;
	one.imaginary = 0;
	three.real = 3;
	three.imaginary = 0;
	get_boundries(p, draw);
	while (n < draw->max_iter && c_abs(z) > TOL)
	{
		z = *compute_new_z(&z, &one, &three);
		n++;
	}
	p->color = color_from_distance(z);
	return (n);
}
