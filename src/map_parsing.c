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

// changes: added split in the function to return 2d arr (lines)
static char	**read_file(int fd)
{
	char	*line;
	char	*str;
	char	**map;

	str = NULL;
	line = get_next_line(fd);
	while (line)
	{
		str = extend_str(str, line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	map = ft_split(str, '\n');
	free(str);
	return (map);
}

void	read_and_check_nums(char *path, t_cub *cub)
{
	int		fd;
	char	*text;
	char	**map;

	text = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nOpening file failed\n");
		return ;
	}
	cub->map = read_file(fd);
	close(fd);
	if (!cub->map)
	{
		printf("Error\nFailed to read file\n");
		return ;
	}
	// TODO: the data in text isn't the map only
	// add a extraction step here
	if (phasing(&(cub->map)) == 0 || !(cub->map))
		return (freemap((cub->map), &text));
	free(text);
}

void	map_manager(char *path, t_cub *cub)
{
	char	**map;

	if (check_extention(path, ".cub") == 0)
	{
		printf("Error\nBad file extension\n");
		return (NULL);
	}
	map = read_and_check_nums(path, cub);
	if (!map)
		return (NULL);
	/* TODO: Implement header parsing (textures NO,SO,WE,EA & colors F,C)
	   and flood-fill enclosure check. */
	if (map_walls_check(map) == 0)
		printf("Error\nCheck walls wrong\n");
	else
		return (map);
	freemap(map, NULL);
	return (NULL);
}
