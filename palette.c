/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:37:51 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/10 17:21:14 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	rgb_to_int(int r, int g, int b)
{
	r %= 512;
	if (r > 255)
		r = 512 - r - 1;
	g %= 512;
	if (g > 255)
		g = 512 - g - 1;
	b %= 512;
	if (b > 255)
		b = 512 - b - 1;
	return (r << 16 | g << 8 | b);
}

static int	hsb_to_rgb(float h, float s, float b)
{
	float	c;
	float	x;
	float	m;

	h = fmod(h, 360.0);
	c = b * s;
	x = c * (1 - fabs(fmod((h / 60.0), 2) - 1));
	m = b - c;
	if (h >= 0 && h < 60)
		return (rgb_to_int((c + m) * 255, (x + m) * 255, m * 255));
	if (h >= 60 && h < 120)
		return (rgb_to_int((x + m) * 255, (c + m) * 255, m * 255));
	if (h >= 120 && h < 180)
		return (rgb_to_int(m * 255, (c + m) * 255, (x + m) * 255));
	if (h >= 180 && h < 240)
		return (rgb_to_int(m * 255, (x + m) * 255, (c + m) * 255));
	if (h >= 240 && h < 300)
		return (rgb_to_int((x + m) * 255, m * 255, (c + m) * 255));
	return (rgb_to_int((c + m) * 255, m * 255, (x + m) * 255));
}

int	get_color(t_draw *draw, int n, int max_iter)
{
	double	v;

	if (n == max_iter)
		return (0);
	if (draw->smooth)
	{
		v = n + 1 - log(log(sqrt(draw->z))) / M_LN2;
		return (hsb_to_rgb(15 * v + 150, 0.6, 1.0));
	}
	return (draw->color_range[n % draw->color_range_len]);
}

void	pick_color_range(t_draw *draw, int reset)
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

	if (reset && n)
		n--;
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
