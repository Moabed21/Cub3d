/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 01:29:27 by moabed            #+#    #+#             */
/*   Updated: 2026/08/10 17:30:56 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"
#include <fcntl.h>

// first start with the 4 directions
void	star_validation(t_cub *cub, int option)
{
	int	fd;

	fd = open(cub->n_side, O_RDONLY);
	if (fd == -1)
		option = 1;
	else
		close(fd);
	fd = open(cub->s_side, O_RDONLY);
	if (fd == -1)
		option = 1;
	else
		close(fd);
	fd = open(cub->e_side, O_RDONLY);
	if (fd == -1)
		option = 1;
	else
		close(fd);
	fd = open(cub->w_side, O_RDONLY);
	if (fd == -1)
		option = 1;
	else
		close(fd);
	if (option)
		handle_exit(cub, ERR_FILE_OPEN, 1);
}

int	check_size_and_datatype(char *str)
{
	int	size;
	int	i;

	if (!str || !*str)
		return (1);
	i = 0;
	size = ft_strlen(str);
	if (size > 3)
		return (1);
	while (i < size)
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

// validation on floor and ceiling values,
// if option is 1 then apply f operations if 0 apply c operations
void	seperator(t_cub *cub, int option)
{
	if (option)
		cub->temp_sep_line = ft_split(cub->floor, ',');
	else
		cub->temp_sep_line = ft_split(cub->ceiling, ',');
	if (!cub->temp_sep_line || arr_len(cub->temp_sep_line) != 3)
		handle_exit(cub, ERR_MALLOC, 1);
}

void	f_c_values_validation(t_cub *cub, int option)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (check_size_and_datatype(cub->temp_sep_line[i]))
			handle_exit(cub, ERR_COLOR_RANGE, 1);
		if (option)
		{
			cub->exec.f_rgb[i] = ft_atoi(cub->temp_sep_line[i]);
			if (cub->exec.f_rgb[i] > 255 || cub->exec.f_rgb[i] < 0)
				handle_exit(cub, ERR_COLOR_RANGE, 1);
		}
		else
		{
			cub->exec.c_rgb[i] = ft_atoi(cub->temp_sep_line[i]);
			if (cub->exec.c_rgb[i] > 255 || cub->exec.c_rgb[i] < 0)
				handle_exit(cub, ERR_COLOR_RANGE, 1);
		}
	}
}

void	mini_parse(t_cub *cub)
{
	star_validation(cub, 0);
	seperator(cub, 1);
	f_c_values_validation(cub, 1);
	free_2d_array(&cub->temp_sep_line);
	seperator(cub, 0);
	f_c_values_validation(cub, 0);
	free_2d_array(&cub->temp_sep_line);
}
