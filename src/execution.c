/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 12:20:19 by moabed            #+#    #+#             */
/*   Updated: 2026/08/17 23:55:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

void	init_player_vectors(t_cub *cub)
{
	cub->exec.pos.x = (double)cub->exec.int_position.x + 0.5;
	cub->exec.pos.y = (double)cub->exec.int_position.y + 0.5;
	if (cub->exec.direction == 'N' || cub->exec.direction == 'S')
	{
		cub->exec.dir.x = 0.0;
		cub->exec.dir.y = 1.0;
		if (cub->exec.direction == 'N')
			cub->exec.dir.y = -1.0;
		cub->exec.plane.x = 0.66;
		if (cub->exec.direction == 'S')
			cub->exec.plane.x = -0.66;
		cub->exec.plane.y = 0.0;
	}
	else if (cub->exec.direction == 'W' || cub->exec.direction == 'E')
	{
		cub->exec.dir.x = 1.0;
		if (cub->exec.direction == 'W')
			cub->exec.dir.x = -1.0;
		cub->exec.dir.y = 0.0;
		cub->exec.plane.x = 0.0;
		cub->exec.plane.y = 0.66;
		if (cub->exec.direction == 'W')
			cub->exec.plane.y = -0.66;
	}
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
}

int	close_handler(t_cub *cub)
{
	free_cub(cub);
	exit(0);
	return (0);
}

int	game_loop(t_cub *cub)
{
	render_background(cub);
	raycast(cub);
	mlx_put_image_to_window(cub->mlx_ops.connection, cub->mlx_ops.window,
		cub->mlx_ops.img.img_ptr, 0, 0);
	return (0);
}

void	execution(t_cub *cub)
{
	init_player_vectors(cub);
	mlx(cub);
	load_images(cub);
	mlx_hook(cub->mlx_ops.window, DestroyNotify, StructureNotifyMask,
		(int (*)(void))(void *)close_handler, cub);
	mlx_hook(cub->mlx_ops.window, KeyPress, KeyPressMask,
		(int (*)(void))(void *)handle_keypress, cub);
	mlx_loop_hook(cub->mlx_ops.connection,
		(int (*)(void))(void *)game_loop, cub);
	mlx_loop(cub->mlx_ops.connection);
}
