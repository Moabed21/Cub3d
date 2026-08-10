/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 14:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/08/10 11:43:00 by moabed           ###   ########.fr       */
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
int	check_extention(char *path, char const *cub)
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

char	*extend_str(char *s1, char *s2)
{
	char	*ss;
	ssize_t	i;
	ssize_t	j;

	ss = malloc(ll(s1) + ll(s2) + 1);
	if (!ss)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			ss[i] = s1[i];
			i++;
		}
	}
	free(s1);
	j = 0;
	if (s2)
		while (s2[j])
			ss[i++] = s2[j++];
	free(s2);
	ss[i] = '\0';
	return (ss);
}

void	parse_map(t_cub *cub, int line_num)
{
	check_map_content(cub, line_num);
	// this now points on first line in map
	validate_borders(cub, cub->splitted_lines + line_num);
	// now the map is successfully validated, lets store it
	cub->map = cub->splitted_lines + line_num;
}

void	raise_exception(t_cub *cub, char *message)
{
	size_t	size;

	if (message)
	{
		write(2, "Error\n", 6);
		size = ft_strlen(message);
		write(2, message, size);
		if (size > 0 && message[size - 1] != '\n')
			write(2, "\n", 1);
	}
	if (cub)
		free_cub(cub);
	exit(1);
}
