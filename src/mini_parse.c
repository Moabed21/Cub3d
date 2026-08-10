/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 01:29:27 by moabed            #+#    #+#             */
/*   Updated: 2026/08/10 11:30:08 by moabed           ###   ########.fr       */
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
		raise_exception(cub, "error in direction path");
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
		raise_exception(cub, "malloc failed");
}

void	f_c_values_validation(t_cub *cub, int option)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (check_size_and_datatype(cub->temp_sep_line[i]))
			raise_exception(cub, "wrong color degree");
		if (option)
		{
			cub->exec.f_rgb[i] = ft_atoi(cub->temp_sep_line[i]);
			if (cub->exec.f_rgb[i] > 255 || cub->exec.f_rgb[i] < 0)
				raise_exception(cub, "wrong color degree");
		}
		else
		{
			cub->exec.c_rgb[i] = ft_atoi(cub->temp_sep_line[i]);
			if (cub->exec.c_rgb[i] > 255 || cub->exec.c_rgb[i] < 0)
				raise_exception(cub, "wrong color degree");
		}
	}
}

void	mini_parse(t_cub *cub)
{
	star_validation(cub, 0);
	seperator(cub,1);
	f_c_values_validation(cub, 1);
	free_2d_array(&cub->temp_sep_line);
	seperator(cub,0);
	f_c_values_validation(cub, 0);
	free_2d_array(&cub->temp_sep_line);
}
