/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:44:47 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/14 09:50:45 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "mlx/mlx.h"
# include <stdbool.h>
# include "libft/libft.h"
# include "mlx/mlx_int.h"

# define WIDTH 1200
# define HEIGHT 800
# define MAX_ITER 51
# define ZOOM 300
# define ZOOM_MIN 10
# define ZOOM_MAX 100000000000000000
# define TOL 0.0001

typedef struct s_complex
{
	float		real;
	float		imaginary;
}				t_complex;

typedef struct s_boundries
{
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		color;
	bool	same;
}	t_boundries;

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
	int			**canvas;
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
	bool		mandelbrot;
	bool		julia;
	bool		newton;
	bool		burning_ship;
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
void			init_fractal(char **av, t_draw *draw);
void			init_canvas(t_mlx *mlx);
void			reset(t_mlx *mlx);
void			free_canvas(t_image *img);
int				destroy_and_free(t_mlx *mlx);
void			load_hooks(t_mlx *mlx);
void			get_boundries(t_draw *draw);
void			compute_key_offset(int key, t_draw *draw);
int				mandelbrot(t_pixel *p, t_draw *draw);
int				julia(t_pixel *p, t_draw *draw);
int				newton(t_pixel *p, t_draw *draw);
int				burning_ship(t_pixel *p, t_draw *draw);
void			put_pixel(t_mlx *mlx, t_pixel p);
void			pick_color_range(t_draw *draw, int reset);
int				get_color(t_draw *draw, int n, int max_iter);
t_complex		add(t_complex *a, t_complex *b);
t_complex		substract(t_complex *a, t_complex *b);
t_complex		product(t_complex *a, t_complex *b);
t_complex		divide(t_complex *a, t_complex *b);
t_complex		power(t_complex *a, int n);
bool			check_color_perimiter(t_boundries *b, t_mlx *mlx,
					int (*fractal)(t_pixel *p, t_draw *draw));
void			translate_coordinates(t_mlx *mlx, t_pixel *p);
void			ms(t_mlx *mlx, int (*fractal)(t_pixel *p, t_draw *draw));
void			color_sub_screen(t_boundries *b, t_mlx *mlx);
t_boundries		init_sub_screen(int n, t_boundries b);
bool			b_is_valid(t_boundries b);

#endif
