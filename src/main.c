/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:20:17 by moabed            #+#    #+#             */
/*   Updated: 2026/08/08 21:13:20 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

/*
** Program Flow Summary:
** 1. Zero out t_cub struct pointers & primitives to ensure memory safety.
** 2. Validate argument count (must receive exactly 1 argument: the .cub map path).
** 3. Verify file extension ending with '.cub'.
** 4. Open file (O_RDONLY), read line-by-line via GNL into cub->splitted_lines.
** 5. Iterate through lines to parse header elements (NO, SO, WE, EA, F, C).
*/
int	main(int ac, char **av)
{
	t_cub	cub;

	initiate_cub(&cub);
	if (ac != 2)
		raise_exception(&cub, "must take 1 map.cub as argument");
	if (!check_extention(av[1], ".cub"))
		raise_exception(&cub, "Invalid map file extension (.cub required)");
	read_file(&cub, av[1]);
	line_iterating(&cub);
	free_cub(&cub);
	return (0);
}
