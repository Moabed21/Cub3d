/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 09:57:35 by melshata          #+#    #+#             */
/*   Updated: 2026/07/18 15:22:08 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	**freemap(char **map, char **str)
{
	int	i;

	i = 0;
	while (map && map[i])
		free(map[i++]);
	if (map)
		free(map);
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

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

char	**map_manager(char *path)
{
	char	**map;

	if (check_extention(path, ".ber") == 0)
	{
		printf ("\nError\nbad extention\n\n");
		exit (1);
	}
	map = read_and_check_nums(path);
	if (!map)
		return (NULL);
	if (map_walls_check(map) == 0 || map_check_rect(map) == 0)
		printf ("\nError\ncheck walls or check rectangle wrong\n\n");
	else if (reach(cpymap(map), xy_p(map), 'E', 1) != 1
		|| reach(cpymap(map), xy_p(map), 'C', 1) != collect_num(map))
		printf ("\nError\ncouldn't reach all C and E\n\n");
	else
		return (map);
	freemap(map, NULL);
	return (NULL);
}
