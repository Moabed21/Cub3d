/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 14:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/08/18 12:09:42 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

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

static void	check_consecutive_newlines(t_cub *cub, int line_num)
{
	char	*p;

	p = ft_strnstr(cub->lines, cub->splitted_lines[line_num],
			ft_strlen(cub->lines));
	if (!p)
		handle_exit(cub, ERR_MAP_CONTENT, 1);
	while (*p)
	{
		if (*p == '\n')
		{
			p++;
			while (*p == ' ' || *p == '\t' || *p == '\r')
				p++;
			if (*p == '\n')
				handle_exit(cub, ERR_MAP_CONTENT, 1);
			continue ;
		}
		p++;
	}
}

void	parse_map(t_cub *cub, int line_num)
{
	check_consecutive_newlines(cub, line_num);
	check_map_content(cub, line_num);
	validate_borders(cub, cub->splitted_lines + line_num);
	cub->map = cub->splitted_lines + line_num;
	cub->exec.int_position.y -= line_num;
}
