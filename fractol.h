/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:44:47 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/10 14:59:30 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <stdbool.h>

# define WIDTH 1200
# define HEIGHT 800
# define ZOOM_MAX 100000000000000000
# define ZOOM_MIN 10

typedef struct s_pixel
{
	long double	a;
	long double	b;
	int			x;
	int			y;
	int			color;
}				t_pixel;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_image;

typedef struct s_draw
{
	bool		redraw;
	size_t		zoom;
	int			max_iter;
	int			x_offset;
	int			y_offset;
	int			color_range[7];
	int			color_range_len;
	long double	z;
	long double	x_mouse;
	long double	y_mouse;
	long double	x_key;
	long double	y_key;
	long double	x_max;
	long double	x_min;
	long double	y_max;
	long double	y_min;
	bool		julia;
	bool		smooth;
	float		c_a;
	float		c_b;
}				t_draw;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	t_image		*img;
	t_draw		*draw;
}				t_mlx;

void			usage(void);
float			ft_atof(char *str, void (*panic)(void));
void			init(t_mlx *mlx, t_image *image, t_draw *draw);
void			reset(t_mlx *mlx);
int				destroy_and_free(t_mlx *mlx);
void			load_hooks(t_mlx *mlx);
void			compute_key_offset(int key, t_draw *draw);
void			draw_fractal(t_mlx *mlx);
void			pick_color_range(t_draw *draw, int reset);
int				get_color(t_draw *draw, int n, int max_iter);

#endif
