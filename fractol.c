/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 07:58:03 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/02 11:53:23 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft/libft.h"
#include "mlx/mlx.h"

int		WIDTH = 500;
int		LENGTH = 500;

void	ft_exit(int ret, char *msg)
{
	if (msg)
		ft_printf("%s\n", msg);
	exit(ret);
}

int	main(void)
{
	void	*mlx_id;
	void	*mlx_win;

	mlx_id = mlx_init();
	if (!mlx_id)
		ft_exit(1, "Can't initialize mlx :(");
	mlx_win = mlx_new_window(mlx_id, 500, 500, "KIKOOLOLMDR");
	mlx_new_image(mlx_id, 500, 500);
	if (!mlx_win)
		ft_exit(1, "Can't open window :(");
	mlx_loop(mlx_id);
	return (0);
}
