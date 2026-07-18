/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rect_reach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:00:32 by melshata          #+#    #+#             */
/*   Updated: 2026/01/12 15:07:39 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
