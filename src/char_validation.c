/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/08/09 21:45:25 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

void	check_type_and_fill_2(t_cub *cub, char **sep_line)
{
	if (!ft_strcmp(sep_line[0], "EA"))
	{
		if (cub->e_side)
			raise_exception(cub, "duplicateed EA");
		cub->e_side = ft_strdup(sep_line[1]);
	}
	if (!ft_strcmp(sep_line[0], "F"))
	{
		if (cub->floor)
			raise_exception(cub, "duplicateed Floor");
		cub->floor = ft_strdup(sep_line[1]);
	}
	else if (!ft_strcmp(sep_line[0], "C"))
	{
		if (cub->ceiling)
			raise_exception(cub, "duplicateed Ceiling");
		cub->ceiling = ft_strdup(sep_line[1]);
	}
	else
		raise_exception(cub, "error scenario, shakespeer!");
}

void	check_type_and_fill(t_cub *cub, char **sep_line)
{
	if (!ft_strcmp(sep_line[0], "NO"))
	{
		if (cub->n_side)
			raise_exception(cub, "duplicateed NO");
		cub->n_side = ft_strdup(sep_line[1]);
	}
	else if (!ft_strcmp(sep_line[0], "SO"))
	{
		if (cub->s_side)
			raise_exception(cub, "duplicateed SW");
		cub->s_side = ft_strdup(sep_line[1]);
	}
	else if (!ft_strcmp(sep_line[0], "WE"))
	{
		if (cub->w_side)
			raise_exception(cub, "duplicateed WE");
		cub->w_side = ft_strdup(sep_line[1]);
	}
	else
		check_type_and_fill_2(cub, sep_line);
	cub->data_count++;
}

// split the line itself, expected result "NO" "./path_to_the_north_texture"
// step validation the check elements number matches exactly the typical scenario ex. "NO ./path_to_the_north_texture" must output 2 elements
// req: step validation that check if we acquired the full requirements e.g NO,SW
// data_count++

void	set_param(t_cub *cub, int line_num)
{
	cub->temp_sep_line = ft_split(cub->splitted_lines[line_num], ' ');
	if (!cub->temp_sep_line || arr_len(cub->temp_sep_line) != 2)
		raise_exception(cub, "line error");
	check_type_and_fill(cub, cub->temp_sep_line);
	free_2d_array(&cub->temp_sep_line);
		// we free it cuz we gonna use it one more time
}

// changing the return value means that: if i reached the map
int	line_leading_character(t_cub *cub, int line_num)
{
	int	i;
	int	option;

	option = 0;
	i = 0;
	while (cub->splitted_lines[line_num][i] == ' ')
		i++;
	if (ft_isalpha(cub->splitted_lines[line_num][i]))
		set_param(cub, line_num);
	else if (cub->splitted_lines[line_num][i] == '1')
	{
		if (cub->data_count != 6)
			raise_exception(cub, "missing secenario requirements");
		option++;
	}
	else if (cub->splitted_lines[line_num][i] != '\0')
		raise_exception(cub, "");
	return (option);
}

void	extend_map(t_cub *cub, int line_num)
{
}

// line_iterating on each line in the file,
//	if it reaches the map(line has zeros and ones)
// it calls extend map and start to parse the map from the line we stop at

void	line_iterating(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->splitted_lines[i])
	{
		if (line_leading_character(cub, i))
			break ;
		i++;
	}
	mini_parse(cub);
	// this for validatin the paths we stored an the rgb colors
	extend_map(cub, i); // here we start parse the map
}
