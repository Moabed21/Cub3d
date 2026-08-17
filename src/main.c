/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:20:17 by moabed            #+#    #+#             */
/*   Updated: 2026/08/10 12:20:05 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

/*
** Program Flow Summary:
** 1. Zero out t_cub struct pointers & primitives to ensure memory safety.
** 2. Validate argument count (must receive exactly 1 argument: the .cub map
* path).
** 3. Verify file extension ending with '.cub'.
** 4. Read file line-by-line via GNL into cub->splitted_lines.
** 5. Iterate lines to parse header elements (NO, SO, WE, EA, F, C).
** 6. Mini-parse: validate texture file paths and floor/ceiling RGB values
* (0-255).
** 7. Parse map: validate characters, single player position (store coords/dir),
**    and 4-way wall enclosure boundaries.
** 8. Store validated map pointer (cub->map) and clean up memory.
*/
int	main(int ac, char **av)
{
	t_cub	cub;

	initiate_cub(&cub);
	if (ac != 2)
		handle_exit(&cub, ERR_ARG_COUNT, 1);
	if (!check_extention(av[1], ".cub"))
		handle_exit(&cub, ERR_FILE_EXT, 1);
	read_file(&cub, av[1]);
	parsing(&cub);
	execution(&cub);
	free_cub(&cub);
	return (0);
}
