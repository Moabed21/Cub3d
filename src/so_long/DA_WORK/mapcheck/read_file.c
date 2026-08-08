/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:01:21 by melshata          #+#    #+#             */
/*   Updated: 2026/08/08 20:50:08 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"





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
