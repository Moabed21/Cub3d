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

static int	check_color_format(char *str)
{
	int	i;
	int	commas;

	if (!str || !*str)
		return (1);
	i = 0;
	commas = 0;
	while (str[i])
	{
		if (str[i] == ',')
			commas++;
		else if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	if (commas != 2)
		return (1);
	return (0);
}

// validation on floor and ceiling values,
// if option is 1 then apply f operations if 0 apply c operations
void	seperator(t_cub *cub, int option)
{
	char	*str;

	if (option)
		str = cub->floor;
	else
		str = cub->ceiling;
	if (check_color_format(str))
		handle_exit(cub, ERR_COLOR_RANGE, 1);
	cub->temp_sep_line = ft_split(str, ',');
	if (!cub->temp_sep_line || arr_len(cub->temp_sep_line) != 3)
		handle_exit(cub, ERR_COLOR_RANGE, 1);
}

void	f_c_values_validation(t_cub *cub, int option)
{
	int	i;
	int	val;

	i = 0;
	while (i < 3)
	{
		if (!cub->temp_sep_line[i] || ft_strlen(cub->temp_sep_line[i]) > 3)
			handle_exit(cub, ERR_COLOR_RANGE, 1);
		val = ft_atoi(cub->temp_sep_line[i]);
		if (val > 255 || val < 0)
			handle_exit(cub, ERR_COLOR_RANGE, 1);
		if (option)
			cub->exec.f_rgb[i] = val;
		else
			cub->exec.c_rgb[i] = val;
		i++;
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
