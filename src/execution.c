/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 12:20:19 by moabed            #+#    #+#             */
/*   Updated: 2026/08/10 17:28:40 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

// void	fractal_init(t_fractal *fractal)
// {
// 	fractal->mlx_connection = mlx_init();
// 	data_init(fractal);
// 	if (fractal->mlx_connection == NULL)
// 		error();
// 	fractal->mlx_window = mlx_new_window(fractal->mlx_connection, WIDTH, HEIGHT,
// 			fractal->name);
// 	if (fractal->mlx_window == NULL)
// 	{
// 		mlx_destroy_display(fractal->mlx_connection);
// 		free(fractal->mlx_connection);
// 		error();
// 	}
// 	fractal->img.img = mlx_new_image(fractal->mlx_connection, WIDTH, HEIGHT);
// 	if (fractal->img.img == NULL)
// 	{
// 		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
// 		mlx_destroy_display(fractal->mlx_connection);
// 		free(fractal->mlx_connection);
// 		error();
// 	}
// 	fractal->img.pixel_ptr = mlx_get_data_addr(fractal->img.img,
// 			&fractal->img.bits_per_pixel, &fractal->img.line_length,
// 			&fractal->img.endian);
// }

// first of all we render the main frame of the window to prevent flickering 
// if we draw entire 3D frame once
void	mlx(t_cub *cub)
{
	cub->mlx_ops.connection = mlx_init();
	if (!cub->mlx_ops.connection)
		raise_exception(cub, ERR_MLX_INIT);
	cub->mlx_ops.window = mlx_new_window(cub->mlx_ops.connection, WIDTH, HEIGHT,
			"Cub3d");
	if (!cub->mlx_ops.window)
	{
		mlx_destroy_display(cub->mlx_ops.connection);
		free(cub->mlx_ops.connection);
		raise_exception(cub, ERR_MLX_WIN);
	}
	cub->mlx_ops.img.img_ptr = mlx_new_image(cub->mlx_ops.connection, WIDTH,
			HEIGHT);
	if (!cub->mlx_ops.img.img_ptr)
		raise_exception(cub, ERR_MLX_INIT);
	cub->mlx_ops.img.addr = mlx_get_data_addr(cub->mlx_ops.img.img_ptr,
			&cub->mlx_ops.img.bpp, &cub->mlx_ops.img.line_len,
			&cub->mlx_ops.img.endian);
	mlx_put_image_to_window(cub->mlx_ops.connection, cub->mlx_ops.window,
		cub->mlx_ops.img.img_ptr, 0, 0);
	mlx_loop(cub->mlx_ops.connection);
}

void	execution(t_cub *cub)
{
	// startin with initiatin mlx first canvas
	mlx(cub);
}