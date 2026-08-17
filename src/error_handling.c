/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 14:08:00 by moabed            #+#    #+#             */
/*   Updated: 2026/08/17 23:49:10 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

char	*get_parsing_err_msg(t_err_code code)
{
	if (code == ERR_ARG_COUNT)
		return ("Usage: ./cub3D map.cub");
	if (code == ERR_FILE_EXT)
		return ("Invalid file extension (.cub required)");
	if (code == ERR_FILE_OPEN)
		return ("Error opening map file");
	if (code == ERR_MALLOC)
		return ("Memory allocation failed");
	if (code == ERR_DUPLICATE_ELEMENT)
		return ("Duplicate texture or color element");
	if (code == ERR_MISSING_REQUIREMENTS)
		return ("Missing required elements before map");
	if (code == ERR_COLOR_RANGE)
		return ("RGB color value out of range (0-255)");
	if (code == ERR_MAP_CONTENT)
		return ("Invalid character in map content");
	if (code == ERR_PLAYER_COUNT)
		return ("wanna party or play?");
	if (code == ERR_MAP_OPEN)
		return ("Error, map is open");
	if (code == ERR_EMPTY)
		return ("file is empty!");
	return (NULL);
}

char	*get_exec_err_msg(t_err_code code)
{
	if (code == ERR_MLX_INIT)
		return ("mlx connection failed.");
	if (code == ERR_MLX_WIN)
		return ("mlx window connection failed.");
	return (NULL);
}

char	*get_error_msg(t_err_code code)
{
	char	*msg;

	msg = get_parsing_err_msg(code);
	if (msg)
		return (msg);
	msg = get_exec_err_msg(code);
	if (msg)
		return (msg);
	return ("Unknown error");
}

void	handle_exit(t_cub *cub, t_err_code err_code, int exit_code)
{
	char	*msg;

	if (cub)
		cub->err_code = err_code;
	msg = get_error_msg(err_code);
	if (msg && exit_code == 1)
	{
		write(2, "Error\n", 6);
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	if (cub)
		free_cub(cub);
	exit(exit_code);
}

void	two_step_free(void **var)
{
	if (var && *var)
	{
		free(*var);
		*var = NULL;
	}
}
