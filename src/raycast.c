/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 21:00:00 by moabed            #+#    #+#             */
/*   Updated: 2026/08/17 23:55:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

static void	init_ray(t_cub *cub, int x)
{
	cub->raycast.camera_x = 2.0 * x / (double)WIDTH - 1.0;
	cub->raycast.ray_dir.x = cub->exec.dir.x + cub->exec.plane.x
		* cub->raycast.camera_x;
	cub->raycast.ray_dir.y = cub->exec.dir.y + cub->exec.plane.y
		* cub->raycast.camera_x;
	cub->raycast.map.x = (int)cub->exec.pos.x;
	cub->raycast.map.y = (int)cub->exec.pos.y;
	if (cub->raycast.ray_dir.x == 0)
		cub->raycast.delta_dist.x = 1e30;
	else
		cub->raycast.delta_dist.x = fabs(1.0 / cub->raycast.ray_dir.x);
	if (cub->raycast.ray_dir.y == 0)
		cub->raycast.delta_dist.y = 1e30;
	else
		cub->raycast.delta_dist.y = fabs(1.0 / cub->raycast.ray_dir.y);
	cub->raycast.hit = 0;
}

static void	init_step(t_cub *cub)
{
	if (cub->raycast.ray_dir.x < 0)
	{
		cub->raycast.step.x = -1;
		cub->raycast.side_dist.x = (cub->exec.pos.x - cub->raycast.map.x)
			* cub->raycast.delta_dist.x;
	}
	else
	{
		cub->raycast.step.x = 1;
		cub->raycast.side_dist.x = (cub->raycast.map.x + 1.0 - cub->exec.pos.x)
			* cub->raycast.delta_dist.x;
	}
	if (cub->raycast.ray_dir.y < 0)
	{
		cub->raycast.step.y = -1;
		cub->raycast.side_dist.y = (cub->exec.pos.y - cub->raycast.map.y)
			* cub->raycast.delta_dist.y;
	}
	else
	{
		cub->raycast.step.y = 1;
		cub->raycast.side_dist.y = (cub->raycast.map.y + 1.0 - cub->exec.pos.y)
			* cub->raycast.delta_dist.y;
	}
}

static void	perform_dda(t_cub *cub)
{
	while (cub->raycast.hit == 0)
	{
		if (cub->raycast.side_dist.x < cub->raycast.side_dist.y)
		{
			cub->raycast.side_dist.x += cub->raycast.delta_dist.x;
			cub->raycast.map.x += cub->raycast.step.x;
			cub->raycast.side = 0;
		}
		else
		{
			cub->raycast.side_dist.y += cub->raycast.delta_dist.y;
			cub->raycast.map.y += cub->raycast.step.y;
			cub->raycast.side = 1;
		}
		if (cub->raycast.map.y < 0 || !cub->map[cub->raycast.map.y])
			break ;
		if (cub->raycast.map.x < 0 || cub->raycast.map.x >= (int)ft_strlen(
				cub->map[cub->raycast.map.y]))
			break ;
		if (cub->map[cub->raycast.map.y][cub->raycast.map.x] == '1')
			cub->raycast.hit = 1;
	}
}

static void	calc_wall_height(t_cub *cub)
{
	if (cub->raycast.side == 0)
		cub->raycast.perp_wall_dist = cub->raycast.side_dist.x
			- cub->raycast.delta_dist.x;
	else
		cub->raycast.perp_wall_dist = cub->raycast.side_dist.y
			- cub->raycast.delta_dist.y;
	if (cub->raycast.perp_wall_dist < 0.0001)
		cub->raycast.perp_wall_dist = 0.0001;
	cub->raycast.line_height = (int)(HEIGHT / cub->raycast.perp_wall_dist);
	cub->raycast.draw_start = -cub->raycast.line_height / 2 + HEIGHT / 2;
	if (cub->raycast.draw_start < 0)
		cub->raycast.draw_start = 0;
	cub->raycast.draw_end = cub->raycast.line_height / 2 + HEIGHT / 2;
	if (cub->raycast.draw_end >= HEIGHT)
		cub->raycast.draw_end = HEIGHT - 1;
}

void	raycast(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(cub, x);
		init_step(cub);
		perform_dda(cub);
		if (cub->raycast.hit)
		{
			calc_wall_height(cub);
			draw_wall_stripe(cub, x);
		}
		x++;
	}
}
