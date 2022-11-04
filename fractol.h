/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:44:47 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/04 08:52:07 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include <math.h>

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_image	*img;
}			t_mlx;

int			destroy_and_free(t_mlx *mlx);
void		put_pixel(t_image *data, int x, int y, int color);
int			close_all(int key, t_mlx *mlx);
void		load_hooks(t_mlx *mlx);
void		draw_square(t_mlx *mlx);

# define WIDTH 500
# define HEIGHT 500

#endif
