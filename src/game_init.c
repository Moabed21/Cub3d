/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 14:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/07/18 14:30:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"
#include <fcntl.h>

// Initializes all t_cub pointers to NULL and primitives to 0 for memory safety
void	initiate_cub(t_cub *cub)
{
	if (!cub)
		return ;
	cub->exec.player_start_point.x = 0;
	cub->exec.player_start_point.y = 0;
	cub->direction = 0;
	cub->n_side = NULL;
	cub->s_side = NULL;
	cub->e_side = NULL;
	cub->w_side = NULL;
	cub->ceiling = NULL;
	cub->floor = NULL;
	cub->lines = NULL;
	cub->temp_sep_line = NULL;
	cub->splitted_lines = NULL;
	cub->data_count = 0;
}

void	free_2d_array(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		two_step_free((void **)&((*arr)[i]));
		i++;
	}
	two_step_free((void **)arr);
}

void	free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	two_step_free((void **)&cub->n_side);
	two_step_free((void **)&cub->s_side);
	two_step_free((void **)&cub->e_side);
	two_step_free((void **)&cub->w_side);
	two_step_free((void **)&cub->ceiling);
	two_step_free((void **)&cub->floor);
	two_step_free((void **)&cub->lines);
	free_2d_array(&cub->temp_sep_line);
	free_2d_array(&cub->splitted_lines);
	cub->data_count = 0;
	cub->direction = 0;
	cub->exec.player_start_point.x = 0;
	cub->exec.player_start_point.y = 0;
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
void	read_file(t_cub *cub, char *file)
{
	char	*line;
	char	*str;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		raise_exception(cub, "error in file opening");
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
		raise_exception(cub, "malloc failure");
}

void	two_step_free(void **var)
{
	if (var && *var) // not || cuz thep ointer is always pointing
	{
		free(*var);
		*var = NULL;
	}
}