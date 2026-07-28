/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 14:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/07/18 14:30:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

void	initiate_cub(t_cub *cub)
{
	cub->player_start_point.x = 0;
	cub->player_start_point.y = 0;
	cub->direction = 0;
	cub->n_side = NULL;
	cub->s_side = NULL;
	cub->e_side = NULL;
	cub->w_side = NULL;
	cub->map = NULL;
}

void	initiate_game(t_game *game, t_cub *cub)
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
	initiate_cub(cub);
}

void	two_step_free(void *var)
{
	// tatakae
}

void	handle_exit(t_game *game, t_cub *cub, int exit_code, const char *msg)
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
	free_cub()
	exit(exit_code);
}

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_exit(game, 0, NULL);
	return (0);
}
