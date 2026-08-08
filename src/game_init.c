/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 14:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/07/18 14:30:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"
#include <fcntl.h>

// Initializes all t_cub pointers to NULL and primitives to 0 for memory safety
void	initiate_cub(t_cub *cub)
{
	if (!cub)
		return ;
	cub->player_start_point.x = 0;
	cub->player_start_point.y = 0;
	cub->direction = 0;
	cub->n_side = NULL;
	cub->s_side = NULL;
	cub->e_side = NULL;
	cub->w_side = NULL;
	cub->ceiling = NULL;
	cub->floor = NULL;
	cub->lines = NULL;
	cub->temp_sep_line = NULL;
	cub->splitted_lines = NULL;
	cub->data_count = 0;
}

// Safely frees every allocated pointer in t_cub and resets each to NULL
void	free_cub(t_cub *cub)
{
	int	i;

	if (!cub)
		return ;
	if (cub->n_side)
	{
		free(cub->n_side);
		cub->n_side = NULL;
	}
	if (cub->s_side)
	{
		free(cub->s_side);
		cub->s_side = NULL;
	}
	if (cub->e_side)
	{
		free(cub->e_side);
		cub->e_side = NULL;
	}
	if (cub->w_side)
	{
		free(cub->w_side);
		cub->w_side = NULL;
	}
	if (cub->ceiling)
	{
		free(cub->ceiling);
		cub->ceiling = NULL;
	}
	if (cub->floor)
	{
		free(cub->floor);
		cub->floor = NULL;
	}
	if (cub->lines)
	{
		free(cub->lines);
		cub->lines = NULL;
	}
	if (cub->temp_sep_line)
	{
		i = 0;
		while (cub->temp_sep_line[i])
		{
			free(cub->temp_sep_line[i]);
			cub->temp_sep_line[i] = NULL;
			i++;
		}
		free(cub->temp_sep_line);
		cub->temp_sep_line = NULL;
	}
	if (cub->splitted_lines)
	{
		i = 0;
		while (cub->splitted_lines[i])
		{
			free(cub->splitted_lines[i]);
			cub->splitted_lines[i] = NULL;
			i++;
		}
		free(cub->splitted_lines);
		cub->splitted_lines = NULL;
	}
	cub->data_count = 0;
	cub->direction = 0;
	cub->player_start_point.x = 0;
	cub->player_start_point.y = 0;
}

char	*extend_str(char *s1, char *s2)
{
	char	*ss;
	ssize_t	i;
	ssize_t	j;

	ss = malloc(ll(s1) + ll(s2) + 1);
	if (!ss)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			ss[i] = s1[i];
			i++;
		}
	}
	free(s1);
	j = 0;
	if (s2)
		while (s2[j])
			ss[i++] = s2[j++];
	free(s2);
	ss[i] = '\0';
	return (ss);
}
void	read_file(t_cub *cub,char *file)
{
	char	*line;
	char	*str;
	int 	fd;

	fd = open(file, O_RDONLY);
	if(fd == -1)
		raise_exception(cub, "error in file opening");
	str = NULL;
	line = get_next_line(fd);
	while (line)
	{
		str = extend_str(str, line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	cub->lines = str;
	cub->splitted_lines = ft_split(cub->lines,'\n');
	if(!cub->splitted_lines)
		raise_exception(cub, "malloc failure");
}

void	initiate_game(char *file,t_game *game, t_cub *cub)
{
	game->mlx = NULL;
	game->win = NULL;
	// game->_base = NULL;
	// game->_grid = NULL;
	game->wall_img = NULL;
	game->floor_img = NULL;
	game->player_img = NULL;
	game->collect_img = NULL;
	game->exit_img = NULL;
	game->player_x = 0;
	game->player_y = 0;
	// game->_x = 0;
	// game->_y = 0;
	initiate_cub(cub);
	read_file(cub, file);
}

void	two_step_free(void *var)
{
	if(var)
		free(var);
	var = NULL;
}

void	handle_exit(t_game *game, t_cub *cub, int exit_code, const char *msg)
{
	if (msg)
		printf("\n\n%s\n\n", msg);
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->collect_img)
		mlx_destroy_image(game->mlx, game->collect_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	freemap(game->map_base, NULL);
	freemap(game->map_grid, NULL);
	free_cub(cub);
	exit(exit_code);
}

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_exit(game, NULL, 0, NULL);
	return (0);
}
