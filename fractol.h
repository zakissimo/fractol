/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:44:47 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/05 12:32:10 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include <math.h>

typedef struct s_pixel
{
	int		x;
	int		y;
	double	a;
	double	b;
	int		color;
}			t_pixel;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_image;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_image	*img;
}			t_mlx;

void		init(t_mlx *mlx, t_image *image);
int			destroy_and_free(t_mlx *mlx);
void		put_pixel(t_image *img, t_pixel p);
int			close_all(int key, t_mlx *mlx);
void		load_hooks(t_mlx *mlx);
void		draw_square(t_mlx *mlx, int len);
void		draw_circle(t_mlx *mlx, int radius);
void		draw_mandelbrot(t_mlx *mlx);

# define WIDTH 1920
# define HEIGHT 1080

#endif
