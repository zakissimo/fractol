/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:37:51 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/09 15:11:02 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pick_color_range(t_draw *draw)
{
	static int	n;
	int const	tokyo_night[7] = {0xF7768E, 0x9ECE6A, 0xE0AF68,
		0x7AA2F7, 0x9A7ECC, 0x4ABAAF, 0xA9B1D6};
	int const	blue_lancelot[7] = {0x7400b8, 0x6930c3, 0x5e60ce,
		0x5390d9, 0x4ea8de, 0x48bfe3, 0x56cfe1};
	int const	seventies[7] = {0x005f73, 0x0a9396, 0xe9d8a6,
		0xee9b00, 0xca6702, 0xbb3e03, 0x9b2226};
	int const	centiso[7] = {0x27293c, 0x2b2d42, 0x8d99ae,
		0xedf2f4, 0xef233c, 0xd80032, 0xdc1745};

	if (n % 4 == 0)
		ft_memcpy(draw->color_range, tokyo_night, 7 * sizeof(int));
	else if (n % 4 == 1)
		ft_memcpy(draw->color_range, blue_lancelot, 7 * sizeof(int));
	else if (n % 4 == 2)
		ft_memcpy(draw->color_range, seventies, 7 * sizeof(int));
	else if (n % 4 == 3)
		ft_memcpy(draw->color_range, centiso, 7 * sizeof(int));
	draw->color_range_len = 7;
	n++;
}
