/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 23:55:00 by moabed            #+#    #+#             */
/*   Updated: 2026/08/17 23:55:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

int	get_tex_index(t_cub *cub)
{
	if (cub->raycast.side == 0)
	{
		if (cub->raycast.ray_dir.x < 0)
			return (2);
		return (3);
	}
	if (cub->raycast.ray_dir.y < 0)
		return (0);
	return (1);
}

static unsigned int	get_tex_pixel(t_img *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->tex_width || y < 0 || y >= tex->tex_height)
		return (0);
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

static void	calc_tex_coords(t_cub *cub, t_img *tex)
{
	if (cub->raycast.side == 0)
		cub->raycast.wall_x = cub->exec.pos.y + cub->raycast.perp_wall_dist
			* cub->raycast.ray_dir.y;
	else
		cub->raycast.wall_x = cub->exec.pos.x + cub->raycast.perp_wall_dist
			* cub->raycast.ray_dir.x;
	cub->raycast.wall_x -= floor(cub->raycast.wall_x);
	cub->raycast.tex_x = (int)(cub->raycast.wall_x * tex->tex_width);
	if (cub->raycast.side == 0 && cub->raycast.ray_dir.x < 0)
		cub->raycast.tex_x = tex->tex_width - cub->raycast.tex_x - 1;
	if (cub->raycast.side == 1 && cub->raycast.ray_dir.y > 0)
		cub->raycast.tex_x = tex->tex_width - cub->raycast.tex_x - 1;
	cub->raycast.tex_step = 1.0 * tex->tex_height / cub->raycast.line_height;
	cub->raycast.tex_pos = (cub->raycast.draw_start - HEIGHT / 2
			+ cub->raycast.line_height / 2) * cub->raycast.tex_step;
}

void	draw_wall_stripe(t_cub *cub, int x)
{
	t_img			*tex;
	int				tex_y;
	int				y;
	unsigned int	color;

	tex = &cub->mlx_ops.walls[get_tex_index(cub)];
	calc_tex_coords(cub, tex);
	y = cub->raycast.draw_start;
	while (y <= cub->raycast.draw_end)
	{
		tex_y = (int)cub->raycast.tex_pos;
		if (tex_y >= tex->tex_height)
			tex_y = tex->tex_height - 1;
		if (tex_y < 0)
			tex_y = 0;
		cub->raycast.tex_pos += cub->raycast.tex_step;
		color = get_tex_pixel(tex, cub->raycast.tex_x, tex_y);
		my_mlx_pixel_put(&cub->mlx_ops.img, x, y, color);
		y++;
	}
}
