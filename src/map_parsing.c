/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 14:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/07/18 14:30:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

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

// Validates that path is non-null, has at least 4 characters,
// and ends with the given extension
int	check_extention(char *path,char const *cub)
{
	int	i;
	int	num_match;

	if (!path || !cub)
		return (0);
	i = 0;
	while (path[i])
		i++;
	if (i < 4)
		return (0);
	i -= 4;
	num_match = 0;
	while (path[i])
	{
		if (path[i] == cub[num_match])
			num_match++;
		i++;
	}
	if (num_match != 4)
		return (0);
	return (1);
}
