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
	validate_borders(cub, cub->splitted_lines + line_num);
	cub->map = cub->splitted_lines + line_num;
}

void	read_file(t_cub *cub, char *file)
{
	char	*line;
	char	*str;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		raise_exception(cub, ERR_FILE_OPEN);
	str = NULL;
	line = get_next_line(fd);
	while (line)
	{
		str = extend_str(str, line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	cub->lines = str;
	cub->splitted_lines = ft_split(cub->lines, '\n');
	if (!cub->splitted_lines)
		raise_exception(cub, ERR_EMPTY);
}
