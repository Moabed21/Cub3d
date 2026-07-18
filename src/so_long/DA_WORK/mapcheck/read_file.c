/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:01:21 by melshata          #+#    #+#             */
/*   Updated: 2026/07/18 15:22:08 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
