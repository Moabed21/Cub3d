/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/08/10 11:43:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

int	check_type(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E'
		&& c != ' ')
		return (1);
	return (0);
}

void	store_player_location(t_cub *cub, int row, int col)
{
	cub->exec.player_start_point.x = row;
	cub->exec.player_start_point.y = col;
	cub->exec.direction = cub->splitted_lines[row][col];
}

// first lets check if the map contains any forbiddens , if so raise exception
void	check_map_content(t_cub *cub, int line_num)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	i = arr_len(cub->splitted_lines);
	while (line_num < i)
	{
		j = 0;
		while (cub->splitted_lines[line_num][j])
		{
			if (check_type(cub->splitted_lines[line_num][j]))
				raise_exception(cub, "Error in map content!");
			if (is_player(cub->splitted_lines[line_num][j]))
			{
				store_player_location(cub, line_num, j);
				player++;
			}
			j++;
		}
		line_num++;
	}
	if (player != 1)
		raise_exception(cub, "wanna party or play?");
}

// if we stand on a '0' on NSWE direction , we have to check above, below,
// left and right ,(need to be checked).
void	validate_current_location(t_cub *cub, int row, int col, char **map)
{
	// 1. Playable cell ('0' or player) must not touch spaces or boundaries
	if (map[row][col] == '0' || is_player(map[row][col]))
	{
		if (row == 0 || !map[row + 1] || col == 0 || !map[row][col + 1])
			raise_exception(cub, "Error, map is open");
		if (col >= ft_strlen(map[row - 1]) || col >= ft_strlen(map[row + 1]))
			raise_exception(cub, "Error, map is open");
		if (map[row - 1][col] == ' ' || map[row + 1][col] == ' '
			|| map[row][col - 1] == ' ' || map[row][col + 1] == ' ')
			raise_exception(cub, "Error, map is open");
	}

	// 2. Space (' ') must not touch any floor ('0') or player symbol
	if (map[row][col] == ' ')
	{
		// Top neighbor
		if (row > 0 && col < ft_strlen(map[row - 1])
			&& (map[row - 1][col] == '0' || is_player(map[row - 1][col])))
			raise_exception(cub, "Error, map is open");

		// Bottom neighbor
		if (map[row + 1] && col < ft_strlen(map[row + 1])
			&& (map[row + 1][col] == '0' || is_player(map[row + 1][col])))
			raise_exception(cub, "Error, map is open");

		// Left neighbor
		if (col > 0 && (map[row][col - 1] == '0' || is_player(map[row][col - 1])))
			raise_exception(cub, "Error, map is open");

		// Right neighbor
		if (map[row][col + 1]
			&& (map[row][col + 1] == '0' || is_player(map[row][col + 1])))
			raise_exception(cub, "Error, map is open");
	}
}

void	validate_borders(t_cub *cub, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			validate_current_location(cub, i, j, map);
			j++;
		}
		i++;
	}
}
