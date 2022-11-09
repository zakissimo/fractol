/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:44:47 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/09 07:43:26 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include <math.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

# define WIDTH 1200
# define HEIGHT 800
# define ZOOM_MAX 100000000000000000

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
	long double	x_mouse;
	long double	y_mouse;
	long double	x_key;
	long double	y_key;
	long double	x_max;
	long double	x_min;
	long double	y_max;
	long double	y_min;
}				t_draw;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	t_image		*img;
	t_draw		*draw;
}				t_mlx;

void			init(t_mlx *mlx, t_image *image, t_draw *draw);
int				destroy_and_free(t_mlx *mlx);
int				key_hook(int key, t_mlx *mlx);
int				mouse_hook(int key, int x, int y, t_mlx *mlx);
int				handlebrot(t_mlx *mlx);
void			load_hooks(t_mlx *mlx);
void			put_pixel(t_mlx *mlx, t_pixel p);
void			draw_mandelbrot(t_mlx *mlx);

#endif
