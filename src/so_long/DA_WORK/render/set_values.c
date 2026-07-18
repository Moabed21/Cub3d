/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:56:32 by melshata          #+#    #+#             */
/*   Updated: 2026/07/18 15:22:08 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	initiate_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map_base = NULL;
	game->map_grid = NULL;
	game->wall_img = NULL;
	game->floor_img = NULL;
	game->player_img = NULL;
	game->collect_img = NULL;
	game->exit_img = NULL;
	game->player_x = 0;
	game->player_y = 0;
	game->map_x = 0;
	game->map_y = 0;
	game->collected = 0;
}

static void	*load_texture(t_game *game, char *path)
{
	int		w;
	int		h;
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
	if (!img)
	{
		printf("Error\nloading %s", path);
		handle_exit(game, 1, NULL);
	}
	return (img);
}

void	load_photos(t_game *game)
{
	game->wall_img = load_texture(game, "photos/wall.xpm");
	game->floor_img = load_texture(game, "photos/floor.xpm");
	game->player_img = load_texture(game, "photos/cat_right.xpm");
	game->collect_img = load_texture(game, "photos/collect.xpm");
	game->exit_img = load_texture(game, "photos/exit.xpm");
}

void	set_xy(t_game *game, char **map)
{
	game->collected = 0;
	game->player_x = xy_p(map).x;
	game->player_y = xy_p(map).y;
	game->map_base[game->player_y][game->player_x] = '0';
	game->map_y = 0;
	while (game->map_grid && game->map_grid[game->map_y])
		game->map_y++;
	game->map_x = 0;
	while (game->map_grid
		&& game->map_grid[0]
		&& game->map_grid[0][game->map_x])
		game->map_x++;
}
