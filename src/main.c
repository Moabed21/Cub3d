/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:20:17 by moabed            #+#    #+#             */
/*   Updated: 2026/07/18 15:25:14 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

// int	main(int ac, char **av)
// {
// 	t_game	game;
// 	t_cub	cub;

// 	initiate_game(&game, &cub);
// 	if (ac != 2)
// 		handle_exit(&game, &cub, 1, "Error\nmust take 1 map.cub as agument");
// 	game.map_base = map_manager(av[1]);  // todo: filemanager
// 	if (!game.map_base)
// 		handle_exit(&game, 1, NULL);
// 	game.map_grid = cpymap(game.map_base);
// 	if (!game.map_grid)
// 		handle_exit(&game, 1, "Error\ncreating map base went wrong");
// 	set_xy(&game, game.map_base);
// 	game.mlx = mlx_init();
// 	if (!game.mlx)
// 		return (1);
// 	load_photos(&game);
// 	game.win = mlx_new_window(game.mlx, game.map_x * IMG_SIZE,
// 			game.map_y * IMG_SIZE, "So Long Move");
// 	render_frame(&game);
// 	mlx_key_hook(game.win, handle_keypress, &game);
// 	mlx_hook(game.win, 17, 0, close_window, &game);
// 	mlx_loop(game.mlx);
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_game	game;
	t_cub	cub;

	initiate_game(&game, &cub);
	if (ac != 2)
		handle_exit(&game, &cub, 1, "Error\nmust take 1 map.cub as agument");
	map_manager(av[1], &cub);  // todo: file_manager

}
