/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 14:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/08/17 23:49:17 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

void	initiate_cub(t_cub *cub)
{
	if (!cub)
		return ;
	ft_bzero(cub, sizeof(t_cub));
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
		mlx_destroy_image(cub->mlx_ops.connection, cub->mlx_ops.img.img_ptr);
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
