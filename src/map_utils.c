/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/07/23 18:30:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

char	**cpymap(char **map)
{
	int		i;
	int		j;
	char	**cmap;

	i = 0;
	while (map[i])
		i++;
	j = 0;
	while (map[0][j])
		j++;
	cmap = malloc(sizeof(char *) * (i + 1));
	cmap[i] = NULL;
	i = 0;
	while (map[i])
	{
		cmap[i] = malloc(j + 1);
		if (!cmap[i])
			return (freemap(cmap, NULL));
		j = 0;
		while (map[i][j++])
			cmap[i][j - 1] = map[i][j - 1];
		cmap[i][j - 1] = '\0';
		i++;
	}
	return (cmap);
}

/* TODO: REMOVE — No collectibles in Cub3D. */
int	collect_num(char **map)
{
	int	c_num;
	int	x;
	int	y;

	c_num = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C' || map[y][x] == 'c')
				c_num++;
			x++;
		}
		y++;
	}
	return (c_num);
}

/* TODO: Adapt — Find N/S/E/W instead of P, and store direction.
** In Cub3D the player char tells you their starting orientation. */
t_point	xy_p(char **map)
{
	int		found;
	t_point	xy_point;

	found = 0;
	xy_point.y = 0;
	while (map[xy_point.y])
	{
		xy_point.x = 0;
		while (map[xy_point.y][xy_point.x])
		{
			if (map[xy_point.y][xy_point.x] == 'P')
			{
				found = 1;
				break ;
			}
			xy_point.x++;
		}
		if (found)
			break ;
		xy_point.y++;
	}
	return (xy_point);
}
