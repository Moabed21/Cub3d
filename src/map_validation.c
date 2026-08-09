/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/07/23 18:30:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

/* TODO: Rework — Cub3D maps are NOT rectangular, rows can differ in length.
** Spaces are valid and must be treated like walls for enclosure.
** Current so_long logic assumes uniform row lengths. */

/* TODO: cub3d map validation functions will go here:
** - flood-fill enclosure check (spaces = walls)
** - exactly 1 player (N/S/E/W)
** - valid characters only (0, 1, N, S, E, W, space)
*/
