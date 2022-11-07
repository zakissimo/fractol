/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:44:47 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/07 09:52:04 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include <math.h>
# include <stdbool.h>

# define WIDTH 1200
# define HEIGHT 800

typedef struct s_pixel
{
	long double	a;
	long double	b;
	int			x;
	int			y;
	int			color;
}			t_pixel;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_image;

typedef struct s_draw
{
	bool	redraw;
	int		zoom;
	int		max_iter;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
}			t_draw;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_image	*img;
	t_draw	*draw;
}			t_mlx;

void		init(t_mlx *mlx, t_image *image, t_draw *draw);
int			destroy_and_free(t_mlx *mlx);
int			key_hook(int key, t_mlx *mlx);
int			mouse_hook(int key, int x, int y, t_mlx *mlx);
int			handlebrot(t_mlx *mlx);
void		load_hooks(t_mlx *mlx);
void		put_pixel(t_image *img, t_pixel p);
void		draw_square(t_mlx *mlx, int len);
void		draw_circle(t_mlx *mlx, int radius);
void		draw_mandelbrot(t_mlx *mlx);

#endif
