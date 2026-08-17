/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 11:41:00 by moabed            #+#    #+#             */
/*   Updated: 2026/08/17 23:55:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

int	get_color(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr || x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_background(t_cub *cub)
{
	int	x;
	int	y;
	int	c_color;
	int	f_color;

	c_color = get_color(cub->exec.c_rgb);
	f_color = get_color(cub->exec.f_rgb);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				my_mlx_pixel_put(&cub->mlx_ops.img, x, y, c_color);
			else
				my_mlx_pixel_put(&cub->mlx_ops.img, x, y, f_color);
			x++;
		}
		y++;
	}
}

static void	load_texture(t_cub *cub, t_img *tex, char *path)
{
	int	width;
	int	height;

	tex->img_ptr = mlx_xpm_file_to_image(cub->mlx_ops.connection, path, &width,
			&height);
	if (!tex->img_ptr)
		handle_exit(cub, ERR_FILE_OPEN, 1);
	tex->tex_width = width;
	tex->tex_height = height;
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
}

void	load_images(t_cub *cub)
{
	load_texture(cub, &cub->mlx_ops.walls[0], cub->n_side);
	load_texture(cub, &cub->mlx_ops.walls[1], cub->s_side);
	load_texture(cub, &cub->mlx_ops.walls[2], cub->w_side);
	load_texture(cub, &cub->mlx_ops.walls[3], cub->e_side);
}
