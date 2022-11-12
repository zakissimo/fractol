/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_canvas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 07:50:05 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/12 08:05:03 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_canvas(t_image *c)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
			ft_printf("c[%d][%d] = %d\n", i, j, c->canvas[i][j]);
	}
}
