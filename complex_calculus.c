/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_calculus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:07:48 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/11 15:17:58 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	add(t_complex *a, t_complex *b)
{
	t_complex	ret;

	ret.real = a->real + b->real;
	ret.imaginary = a->imaginary + b->imaginary;
	return (ret);
}

t_complex	substract(t_complex *a, t_complex *b)
{
	t_complex	ret;

	ret.real = a->real - b->real;
	ret.imaginary = a->imaginary - b->imaginary;
	return (ret);
}

t_complex	product(t_complex *a, t_complex *b)
{
	t_complex	ret;

	ret.real = a->real * b->real - a->imaginary * b->imaginary;
	ret.imaginary = a->real * b->imaginary + a->imaginary * b->real;
	return (ret);
}

t_complex	divide(t_complex *a, t_complex *b)
{
	double		m;
	t_complex	tmp;

	m = b->imaginary * b->imaginary + b->real * b->real;
	tmp.real = b->real / m;
	tmp.imaginary = -b->imaginary / m;
	return (product(a, &tmp));
}

t_complex	power(t_complex *a, int n)
{
	t_complex	ret;

	ret = product(a, a);
	while (n - 2)
	{
		ret = product(&ret, a);
		n--;
	}
	return (ret);
}
