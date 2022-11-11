/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 08:06:33 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/11 12:45:43 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	product(t_complex a, t_complex b)
{
	t_complex	ret;

	ret.real = a.real * b.real - a.imaginary * b.imaginary;
	ret.imaginary = a.real * b.imaginary - a.imaginary * b.real;
	return (ret);
}

t_complex	divide(t_complex a, t_complex b)
{
	double		m;
	t_complex	tmp;

	m = b.imaginary * b.imaginary + b.real * b.real;
	tmp.real = b.real / m;
	tmp.imaginary = -b.imaginary / m;
	return (product(a, tmp));
}

t_complex	power(t_complex a, int n)
{
	t_complex	ret;

	ret = product(a, a);
	while (n - 2)
	{
		ret = product(ret, a);
		n--;
	}
	return (ret);
}

t_complex	substract(t_complex a, t_complex b)
{
	t_complex	ret;

	ret.real = a.real - b.real;
	ret.imaginary = a.imaginary - b.imaginary;
	return (ret);
}

float	c_abs(t_complex z)
{
	return (sqrt(z.real * z.real + z.imaginary * z.imaginary));
}

int	newton(t_pixel *p, t_draw *draw)
{
	int			n;
	double		tol;
	t_complex	z;
	t_complex	f;
	t_complex	d;
	t_complex	fraction;
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
	n = 0;
	tol = 0.0001;
	get_boundries(p, draw);
	z.real = p->a;
	z.imaginary = p->b;
	p->color = 0x00000000;
	while (n < draw->max_iter)
	{
		f = power(z, 3);
		f.real -= 1;
		d = power(z, 2);
		d.real *= 3;
		fraction = divide(f, d);
		z.real -= fraction.real;
		z.imaginary -= fraction.imaginary;
		n++;
		diff = substract(z, root_one);
		if (fabsl(diff.real) < tol && fabsl(diff.imaginary) < tol)
			p->color = 0xffff0000;
		diff = substract(z, root_two);
		if (fabsl(diff.real) < tol && fabsl(diff.imaginary) < tol)
			p->color = 0xff00ff00;
		diff = substract(z, root_three);
		if (fabsl(diff.real) < tol && fabsl(diff.imaginary) < tol)
			p->color = 0xff0000ff;
	}
	return (n);
}
