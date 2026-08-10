/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/08/10 11:43:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

// optimizing the cpymap fun. now it copies the map no matter its shape
char	**cpymap(char **map)
{
	int		i;
	int		j;
	char	**cmap;

	i = 0;
	while (map[i])
		i++;
	cmap = malloc(sizeof(char *) * (i + 1));
	if (!cmap)
		return (NULL);
	cmap[i] = NULL;
	i = 0;
	while (map[i])
	{
		j = ft_strlen(map[i]);
		cmap[i] = malloc(j + 1);
		if (!cmap[i])
			return (freemap(cmap, NULL));
		j = 0;
		while (map[i][j])
		{
			cmap[i][j] = map[i][j];
			j++;
		}
		cmap[i][j] = '\0';
		i++;
	}
	return (cmap);
}

// a helper function that checks the player facing location
int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
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
			if (is_player(map[xy_point.y][xy_point.x]))
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

// Compares two strings and returns ASCII difference (0 if equal)
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	arr_len(char **arr)
{
	int len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}