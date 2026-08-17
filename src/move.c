/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 23:47:34 by moabed            #+#    #+#             */
/*   Updated: 2026/08/17 23:47:40 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

// treats anything that isn't a walkable floor tile as solid: walls ('1'),
// spaces (outside the map), and out-of-bounds rows/cols
static int	is_wall(char **map, int x, int y)
{
	if (y < 0 || !map[y])
		return (1);
	if (x < 0 || (size_t)x >= ft_strlen(map[y]))
		return (1);
	return (map[y][x] == '1' || map[y][x] == ' ');
}

// moves along x and y independently so the player can slide along a wall
// instead of getting fully blocked when only one axis collides
void	move_player(t_cub *cub, double dx, double dy)
{
	double	new_x;
	double	new_y;
	double	margin_x;
	double	margin_y;

	new_x = cub->exec.pos.x + dx;
	new_y = cub->exec.pos.y + dy;
	if (dx > 0)
		margin_x = 0.15;
	else
		margin_x = -0.15;
	if (dy > 0)
		margin_y = 0.15;
	else
		margin_y = -0.15;
	if (!is_wall(cub->map, (int)(new_x + margin_x), (int)cub->exec.pos.y))
		cub->exec.pos.x = new_x;
	if (!is_wall(cub->map, (int)cub->exec.pos.x, (int)(new_y + margin_y)))
		cub->exec.pos.y = new_y;
}

// standard 2D rotation matrix applied to both dir and plane together,
// otherwise the camera plane drifts out of sync with the view direction
void	rotate_direction(t_cub *cub, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->exec.dir.x;
	cub->exec.dir.x = cub->exec.dir.x * cos(angle) - cub->exec.dir.y
		* sin(angle);
	cub->exec.dir.y = old_dir_x * sin(angle) + cub->exec.dir.y * cos(angle);
	old_plane_x = cub->exec.plane.x;
	cub->exec.plane.x = cub->exec.plane.x * cos(angle) - cub->exec.plane.y
		* sin(angle);
	cub->exec.plane.y = old_plane_x * sin(angle) + cub->exec.plane.y
		* cos(angle);
}

int	handle_keypress(int keysym, t_cub *cub)
{
	if (keysym == KEY_ESC)
		handle_exit(cub, ERR_NONE, 0);
	else if (keysym == KEY_UP || keysym == 'w' || keysym == 'W')
		move_player(cub, cub->exec.dir.x * MOVE_SPEED, cub->exec.dir.y
			* MOVE_SPEED);
	else if (keysym == KEY_DOWN || keysym == 's' || keysym == 'S')
		move_player(cub, -cub->exec.dir.x * MOVE_SPEED, -cub->exec.dir.y
			* MOVE_SPEED);
	else if (keysym == 'a' || keysym == 'A')
		move_player(cub, cub->exec.dir.y * MOVE_SPEED, -cub->exec.dir.x
			* MOVE_SPEED);
	else if (keysym == 'd' || keysym == 'D')
		move_player(cub, -cub->exec.dir.y * MOVE_SPEED, cub->exec.dir.x
			* MOVE_SPEED);
	else if (keysym == KEY_LEFT)
		rotate_direction(cub, -ROT_SPEED);
	else if (keysym == KEY_RIGHT)
		rotate_direction(cub, ROT_SPEED);
	return (0);
}
