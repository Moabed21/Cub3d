/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/07/23 18:30:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

/* TODO: Rework — Cub3D maps are NOT rectangular, rows can differ in length.
** Spaces are valid and must be treated like walls for enclosure.
** Current so_long logic assumes uniform row lengths. */
int	map_walls_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[0][i] && map[0][i] == '1')
		i++;
	if (map[0][i] != '\0')
		return (0);
	j = 0;
	while (map[j] && map[j][0] == '1' && map[j][i - 1] == '1')
		j++;
	i = 0;
	while (map[j - 1][i] && map[j - 1][i] == '1')
		i++;
	if (map[j - 1][i] != '\0')
		return (0);
	return (1);
}

/* TODO: REMOVE or rework — Cub3D maps do NOT need to be rectangular.
** Rows can have different lengths. This check would reject valid maps. */
int	map_check_rect(char **map)
{
	int	i;
	int	l;
	int	old_l;

	i = 0;
	old_l = 0;
	while (map[i])
	{
		l = 0;
		while (map[i][l])
			l++;
		if (old_l != 0 && old_l != l)
			return (0);
		old_l = l;
		i++;
	}
	return (1);
}

/* TODO: Adapt for ENCLOSURE checking instead of reachability.
** So_long: counts reachable C's and E's from player.
** Cub3D: flood from player, if reach edge/open space -> map not closed.
** Spaces should be treated as walls during flood-fill. */
int	reach(char **map, t_point xy, char to_count, int firstcall)
{
	int	counter;

	counter = 0;
	if (map[xy.y][xy.x] == to_count)
		counter++;
	map[xy.y][xy.x] = 'F';
	if (map[xy.y][xy.x + 1] != '1' && map[xy.y][xy.x + 1] != 'F')
		counter += reach(map, (t_point){xy.x + 1, xy.y}, to_count, 0);
	if (map[xy.y][xy.x - 1] != '1' && map[xy.y][xy.x - 1] != 'F')
		counter += reach(map, (t_point){xy.x - 1, xy.y}, to_count, 0);
	if (map[xy.y + 1][xy.x] != '1' && map[xy.y + 1][xy.x] != 'F')
		counter += reach(map, (t_point){xy.x, xy.y + 1}, to_count, 0);
	if (map[xy.y - 1][xy.x] != '1' && map[xy.y - 1][xy.x] != 'F')
		counter += reach(map, (t_point){xy.x, xy.y - 1}, to_count, 0);
	if (firstcall)
		freemap(map, NULL);
	return (counter);
}
