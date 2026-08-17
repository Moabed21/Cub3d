/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 14:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/08/10 17:27:08 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"
#include <fcntl.h>

// Initializes all t_cub pointers to NULL and primitives to 0 for memory safety
void	initiate_cub(t_cub *cub)
{
	int	i;

	if (!cub)
		return ;
	cub->exec.int_position.x = 0;
	cub->exec.int_position.y = 0;
	cub->exec.direction = 0;
	cub->err_code = ERR_NONE;
	cub->n_side = NULL;
	cub->s_side = NULL;
	cub->e_side = NULL;
	cub->w_side = NULL;
	cub->ceiling = NULL;
	cub->floor = NULL;
	cub->lines = NULL;
	cub->temp_sep_line = NULL;
	cub->map = NULL;
	cub->splitted_lines = NULL;
	cub->data_count = 0;
	cub->mlx_ops.connection = NULL;
	cub->mlx_ops.window = NULL;
	cub->mlx_ops.img.img_ptr = NULL;
	i = 0;
	while (i < 4)
	{
		cub->mlx_ops.walls[i].img_ptr = NULL;
		i++;
	}
}

void	free_2d_array(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		two_step_free((void **)&((*arr)[i]));
		i++;
	}
	two_step_free((void **)arr);
}

void	clean_mlx(t_cub *cub)
{
	int	i;

	if (!cub)
		return ;
	i = 0;
	while (i < 4)
	{
		if (cub->mlx_ops.walls[i].img_ptr)
			mlx_destroy_image(cub->mlx_ops.connection,
				cub->mlx_ops.walls[i].img_ptr);
		cub->mlx_ops.walls[i].img_ptr = NULL;
		i++;
	}
	if (cub->mlx_ops.img.img_ptr)
		mlx_destroy_image(cub->mlx_ops.connection,
			cub->mlx_ops.img.img_ptr);
	cub->mlx_ops.img.img_ptr = NULL;
	if (cub->mlx_ops.window)
		mlx_destroy_window(cub->mlx_ops.connection, cub->mlx_ops.window);
	cub->mlx_ops.window = NULL;
	if (cub->mlx_ops.connection)
	{
		mlx_destroy_display(cub->mlx_ops.connection);
		free(cub->mlx_ops.connection);
	}
	cub->mlx_ops.connection = NULL;
}

void	free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	clean_mlx(cub);
	two_step_free((void **)&cub->n_side);
	two_step_free((void **)&cub->s_side);
	two_step_free((void **)&cub->e_side);
	two_step_free((void **)&cub->w_side);
	two_step_free((void **)&cub->ceiling);
	two_step_free((void **)&cub->floor);
	two_step_free((void **)&cub->lines);
	free_2d_array(&cub->temp_sep_line);
	free_2d_array(&cub->splitted_lines);
	cub->map = NULL;
	cub->data_count = 0;
	cub->err_code = ERR_NONE;
	cub->exec.direction = 0;
	cub->exec.int_position.x = 0;
	cub->exec.int_position.y = 0;
}

void	read_file(t_cub *cub, char *file)
{
	char	*line;
	char	*str;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		handle_exit(cub, ERR_FILE_OPEN, 1);
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
	cub->splitted_lines = ft_split(cub->lines, '\n');
	if (!cub->splitted_lines)
		handle_exit(cub, ERR_MALLOC, 1);
}

void	two_step_free(void **var)
{
	if (var && *var) // not || cuz the pointer is always pointing
	{
		free(*var);
		*var = NULL;
	}
}