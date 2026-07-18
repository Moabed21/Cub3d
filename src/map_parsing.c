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
#include <fcntl.h>

static char	*extend_str(char *s1, char *s2)
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

int	check_extention(char *path, char const *cub)
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
		if (path[i] == cub[num_match])
			num_match++;
		i++;
	}
	if (num_match != 4)
		return (0);
	return (1);
}

static char	*read_file(int fd)
{
	char	*line;
	char	*str;

	str = NULL;
	line = get_next_line(fd);
	while (line)
	{
		str = extend_str(str, line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (str);
}

char	**read_and_check_nums(char *path)
{
	int		fd;
	char	*text;
	char	**map;

	text = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf ("\nError\nOpenning file went wrong\n\n");
		return (NULL);
	}
	text = read_file(fd);
	close(fd);
	if (!text)
	{
		printf ("\nError\nMoving with fd??\n\n");
		return (NULL);
	}
	map = ft_split(text, '\n');
	if (phasing(&text) == 0 || !map)
		return (freemap(map, &text));
	free(text);
	return (map);
}

char	**map_manager(char *path)
{
	char	**map;

	if (check_extention(path, ".cub") == 0)
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
