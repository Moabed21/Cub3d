/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:07:05 by melshata          #+#    #+#             */
/*   Updated: 2026/01/12 15:52:17 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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

int	check_extention(char *path, char const *ber)
{
	int	i;
	int	num_match;

	i = 0;
	while (path[i])
		i++;
	i -= 4;
	num_match = 0;
	while (path[i])
	{
		if (path[i] == ber[num_match])
			num_match++;
		i++;
	}
	if (num_match != 4)
		return (0);
	return (1);
}
