/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:46:28 by melshata          #+#    #+#             */
/*   Updated: 2026/07/18 15:22:08 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	handle_exit(t_game *game, int exit_code, const char *msg)
{
	if (msg)
		printf("\n\n%s\n\n", msg);
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->collect_img)
		mlx_destroy_image(game->mlx, game->collect_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	freemap(game->map_base, NULL);
	freemap(game->map_grid, NULL);
	exit(exit_code);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	initiate_game(&game);
	if (ac != 2)
		handle_exit(&game, 1, "Error\nmust take 1 map.ber as agument");
	game.map_base = map_manager(av[1]);
	if (!game.map_base)
		handle_exit(&game, 1, NULL);
	game.map_grid = cpymap(game.map_base);
	if (!game.map_grid)
		handle_exit(&game, 1, "Error\ncreating map base went wrong");
	set_xy(&game, game.map_base);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	load_photos(&game);
	game.win = mlx_new_window(game.mlx, game.map_x * IMG_SIZE,
			game.map_y * IMG_SIZE, "So Long Move");
	render_frame(&game);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, handle_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
