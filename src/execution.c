/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 12:20:19 by moabed            #+#    #+#             */
/*   Updated: 2026/08/12 16:21:30 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

int	get_color(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	mlx(t_cub *cub)
{
	cub->mlx_ops.connection = mlx_init();
	if (!cub->mlx_ops.connection)
		handle_exit(cub, ERR_MLX_INIT, 1);
	cub->mlx_ops.window = mlx_new_window(cub->mlx_ops.connection, WIDTH, HEIGHT,
			"Cub3d");
	if (!cub->mlx_ops.window)
		handle_exit(cub, ERR_MLX_WIN, 1);
	cub->mlx_ops.img.img_ptr = mlx_new_image(cub->mlx_ops.connection, WIDTH,
			HEIGHT);
	if (!cub->mlx_ops.img.img_ptr)
		handle_exit(cub, ERR_MLX_INIT, 1);
	cub->mlx_ops.img.addr = mlx_get_data_addr(cub->mlx_ops.img.img_ptr,
			&cub->mlx_ops.img.bpp, &cub->mlx_ops.img.line_len,
			&cub->mlx_ops.img.endian);
	mlx_put_image_to_window(cub->mlx_ops.connection, cub->mlx_ops.window,
		cub->mlx_ops.img.img_ptr, 0, 0);
}

int	close_handler(t_cub *cub)
{
	free_cub(cub);
	exit(0);
	return (0);
}

void	execution(t_cub *cub)
{
	init_player_vectors(cub);
	mlx(cub);
	load_images(cub);
	render_background(cub);
	// raycast(cub);
	mlx_put_image_to_window(cub->mlx_ops.connection, cub->mlx_ops.window,
		cub->mlx_ops.img.img_ptr, 0, 0);
	
	mlx_hook(cub->mlx_ops.window, DestroyNotify, StructureNotifyMask,
		(int (*)())close_handler, cub);
	mlx_loop(cub->mlx_ops.connection);
}