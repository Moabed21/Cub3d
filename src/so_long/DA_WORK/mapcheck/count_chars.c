/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:57:13 by melshata          #+#    #+#             */
/*   Updated: 2026/07/18 15:22:08 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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

static void	count_msg(int cc, int pc, int ec)
{
	if (pc != 1 && ec != 1 && cc < 1)
		printf ("\nError\nWanna play with dust??\n\n");
	else if (pc != 1)
		printf ("\nError\nplaying from 3rd world???\n\n");
	else if (cc != 1)
		printf ("\nError\nCollect some oxygen bro\n\n");
	else if (ec != 1)
		printf ("\nError\nNot even emergency exit?\n\n");
}

int	phasing(char **text)
{
	int	i;
	int	ccount;
	int	pcount;
	int	ecount;

	ccount = 0;
	pcount = 0;
	ecount = 0;
	i = 0;
	while ((*text)[i] && (*text)[i] == '\n')
		i++;
	while ((*text)[i] && isvalid(&((*text)[i]), &ccount, &pcount, &ecount))
		i++;
	while ((*text)[i] && (*text)[i] == '\n')
		i++;
	if ((*text)[i])
		printf ("\nError\ninvalid character or map shape\n\n");
	else if (pcount != 1 || ecount != 1 || ccount < 1)
		count_msg (ccount, pcount, ecount);
	else
		return (1);
	return (0);
}
