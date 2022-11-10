/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:35:24 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/10 12:07:29 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	usage(void)
{
	ft_printf("\n");
	ft_printf("Usage: ./fractol \"FRACTAL set\" [a] [b]\n");
	ft_printf("\n");
	ft_printf("\tFRACTAL options:\n");
	ft_printf("\t\t-\"mandelbrot\"\n");
	ft_printf("\t\t-\"julia\"\n");
	ft_printf("\tNote:\n");
	ft_printf("\t\tIf julia is selected providing [a] and\
 [b] becomes mandatory.\n");
	ft_printf("\t\t[a] and [b] being two floats in the julia set plane.\n");
	ft_printf("\n");
	exit(1);
}
