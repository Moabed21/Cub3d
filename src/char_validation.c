/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/07/23 18:30:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

/*TODO
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

/* TODO: Rewrite — so_long valid chars are 0,1,C,P,E.
** Cub3D valid chars are: 0, 1, N, S, E, W, and space.
** Must check for exactly 1 player (N/S/E/W), no collectibles or exit. */
static int	isvalid(char *c, int *ccount, int *pcount, int *ecount)
{
	if (*c == '0' || *c == '1'
		|| *c == 'C' || *c == 'P' || *c == 'E'
		|| (*(c) == '\n' && *(c + 1) != '\n' && *(c - 1) != '\n'))
	{
		if (*c == 'C')
			(*ccount)++;
		if (*c == 'P')
			(*pcount)++;
		if (*c == 'E')
			(*ecount)++;
		return (1);
	}
	return (0);
}

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
void	line_leading_character(t_cub *cub, int line_num, int space_counted)
{
	int	i;

	i = 0;
	if (space_counted == 0)
		while (cub->map[line_num][i] == ' ')
			i++;
	if (ft_isalpha(cub->map[line_num][i]))
		set_param(cub);
	else if (cub->map[line_num][i] == '1')
		extend_map();
	else if (cub->map[line_num][i] != '\0')
	{
		write(2, "Error\n", 6);
		free_cub();
		exit (1)
	}

}

/*
11111    11111
10001111110001
10000000000001

10110000001101
11111111111111
*/


/*
loop on each line
call line leading function to detect which type of data contains
*/
void	line_iterating(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->map[i])
	{
		i++;
	}
	// if ((*text)[i])
	// 	printf ("\nError\ninvalid character or map shape\n\n");
	// else if (pcount != 1 || ecount != 1 || ccount < 1)
	// 	count_msg (ccount, pcount, ecount);
	// else
	// 	return (1);
	// return (0);
}
