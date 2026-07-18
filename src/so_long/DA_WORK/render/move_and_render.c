/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:58:02 by melshata          #+#    #+#             */
/*   Updated: 2026/07/18 15:22:08 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	render_frame(t_game *game)
{
	t_point	xy;
	void	*img;

	xy.y = 0;
	while (xy.y < game->map_y)
	{
		xy.x = 0;
		while (xy.x < game->map_x)
		{
			img = game->floor_img;
			if (game->map_grid[xy.y][xy.x] == '1')
				img = game->wall_img;
			else if (game->map_grid[xy.y][xy.x] == 'P')
				img = game->player_img;
			else if (game->map_grid[xy.y][xy.x] == 'C')
				img = game->collect_img;
			else if (game->map_grid[xy.y][xy.x] == 'E')
				img = game->exit_img;
			mlx_put_image_to_window(game->mlx, game->win, img,
				xy.x * IMG_SIZE, xy.y * IMG_SIZE);
			xy.x++;
		}
		xy.y++;
	}
	return (0);
}

static void	move_player(t_game *game, int new_x, int new_y)
{
	char		new_xy_char;
	static int	count = 0;

	if (game->map_grid[new_y][new_x] == '1')
		return ;
	new_xy_char = game->map_grid[new_y][new_x];
	count++;
	printf("move: %d\n", count);
	if (new_xy_char == 'E' && game->collected == collect_num(game->map_base))
		handle_exit(game, 0, "**WELL DONE!**");
	else if (new_xy_char == 'C')
	{
		game->map_base[new_y][new_x] = 'c';
		game->collected++;
	}
	game->map_grid[game->player_y][game->player_x]
		= game->map_base[game->player_y][game->player_x];
	game->map_grid[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	render_frame(game);
}

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == KEY_ESC)
		handle_exit(game, 0, "exit with ESC");
	else if (keysym == KEY_UP || keysym == 'w')
		move_player(game, game->player_x, game->player_y - 1);
	else if (keysym == KEY_DOWN || keysym == 's')
		move_player(game, game->player_x, game->player_y + 1);
	else if (keysym == KEY_LEFT || keysym == 'a')
		move_player(game, game->player_x - 1, game->player_y);
	else if (keysym == KEY_RIGHT || keysym == 'd')
		move_player(game, game->player_x + 1, game->player_y);
	return (0);
}
