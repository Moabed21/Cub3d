/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/08/08 22:46:42 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

/*TODO
// the map 
     11111
1111111111111111
1100000000000011
1100011111100011
1100011  1100011
1100011111100011
1100000000000011
1111111111111111

1234
2314
3241
4132

*/

/* TODO: Rewrite — so_long checks for P, C, E counts.
** Cub3D needs: exactly 1 player (N/S/E/W), no collectibles.
** Also: the .cub file has a header section (textures + colors)
** before the map, so phasing can't assume entire file is the map. */
static void	count_msg(int cc, int pc, int ec)
{
	if (pc != 1 && ec != 1 && cc < 1)
		printf("\nError\nWanna play with dust??\n\n");
	else if (pc != 1)
		printf ("\nError\nplaying from 3rd world???\n\n");
	else if (cc != 1)
		printf ("\nError\nCollect some oxygen bro\n\n");
	else if (ec != 1)
		printf ("\nError\nNot even emergency exit?\n\n");
}


/*
detect the first character 
if alpha -> send to set param
if 1 (wall of a map) -> send to extend map
else error for any wrong character
*/
// Writes Error and message to stderr, frees all cub data, and exits with 1

void	check_type_and_fill_2(t_cub *cub, char **sep_line)
{
	if (!ft_strcmp(sep_line[0],"EA"))
	{
		if(cub->e_side)
			raise_exception(cub,"duplicateed EA");
		cub->e_side = ft_strdup(sep_line[1]);
	}
	if (!ft_strcmp(sep_line[0],"F"))
	{
		if(cub->floor)
			raise_exception(cub,"duplicateed Floor");
		cub->floor = ft_strdup(sep_line[1]);
	}
	else if(!ft_strcmp(sep_line[0],"C"))
	{
		if(cub->ceiling)
			raise_exception(cub,"duplicateed Ceiling");
		cub->ceiling = ft_strdup(sep_line[1]);
	}
	else
		raise_exception(cub, "error scenario, shakespeer!");
}

void	check_type_and_fill(t_cub *cub, char **sep_line)
{
	if (!ft_strcmp(sep_line[0],"NO"))
	{
		if(cub->n_side)
			raise_exception(cub,"duplicateed NO");
		cub->n_side = ft_strdup(sep_line[1]);
	}
	else if (!ft_strcmp(sep_line[0],"SO"))
	{
		if(cub->s_side)
			raise_exception(cub,"duplicateed SW");
		cub->s_side = ft_strdup(sep_line[1]);
	}
	else if (!ft_strcmp(sep_line[0],"WE"))
	{
		if(cub->w_side)
			raise_exception(cub,"duplicateed WE");
		cub->w_side = ft_strdup(sep_line[1]);	
	}
	else
		check_type_and_fill_2(cub,sep_line);
	cub->data_count++;
}

// split the line itself, expected result "NO" "./path_to_the_north_texture"
// step validation the check elements number matches exactly the typical scenario ex. "NO ./path_to_the_north_texture" must output 2 elements
// req: step validation that check if we acquired the full requirements e.g NO, SW
// data_count++
void	set_param(t_cub *cub,int line_num)
{
	cub->temp_sep_line = ft_split(cub->splitted_lines[line_num], ' ');
	if(!cub->temp_sep_line || arr_len(cub->temp_sep_line) != 2)
		raise_exception(cub,"line error");
	check_type_and_fill(cub,cub->temp_sep_line);
	free(cub->temp_sep_line);
}
void	line_leading_character(t_cub *cub, int line_num)
{
	int	i;

	i = 0;
	while (cub->splitted_lines[line_num][i] == ' ')
			i++;
	if (ft_isalpha(cub->splitted_lines[line_num][i]))
		set_param(cub,line_num);
	else if (cub->splitted_lines[line_num][i] == '1')
	{
		if(cub->data_count !=6)
			raise_exception(cub, "missing secenario requirements");
		extend_map(); // here we start parse the map
	}
	else if (cub->splitted_lines[line_num][i] != '\0')
	{
		raise_exception(cub,"");
	}

}
void	line_iterating(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->splitted_lines[i])
	{
		line_leading_character(cub,i);
		i++;
	}
}
