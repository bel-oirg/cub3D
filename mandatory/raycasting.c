/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:18:12 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/26 11:13:52 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

float	v_inter_ft(t_mlx *raw, float rad)
{
	float	y_inter;
	float	x_inter;
	float	x_step;
	float	y_step;
	int		pxl;

	pxl = 1;
	x_step = TILE_SIZE;
	y_step = x_step * tan(rad);
	x_inter = v_x_inter(raw->ply->plyr_x, rad, &x_step, &pxl);
	y_inter = v_y_inter(raw->ply, x_inter, rad, &y_step);
	while (wall_hit(x_inter + pxl, y_inter, raw))
	{
		x_inter += x_step;
		y_inter += y_step;
	}
	raw->ray->v_inter.y = y_inter;
	raw->ray->v_inter.x = x_inter;
	return (sqrt(pow(x_inter - raw->ply->plyr_x, 2)
			+ pow(y_inter - raw->ply->plyr_y, 2)));
}

float	h_inter_ft(t_mlx *raw, float rad)
{
	float	y_inter;
	float	x_inter;
	float	x_step;
	float	y_step;
	int		pxl;

	pxl = 1;
	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(rad);
	y_inter = h_y_inter(raw->ply->plyr_y, &y_step, rad, &pxl);
	x_inter = h_x_inter(raw->ply, &x_step, y_inter, rad);
	while (wall_hit(x_inter, y_inter + pxl, raw))
	{
		x_inter += x_step;
		y_inter += y_step;
	}
	raw->ray->h_inter.y = y_inter;
	raw->ray->h_inter.x = x_inter;
	return (sqrt(pow(x_inter - raw->ply->plyr_x, 2)
			+ pow(y_inter - raw->ply->plyr_y, 2)));
}

void	cast_rays(t_mlx *mlx)
{
	float	h_inter;
	float	v_inter;
	int		ray;

	ray = 0;
	mlx->ray->ray_ngl = mlx->ply->angle - (mlx->ply->fov_rd / 2);
	while (ray < S_W)
	{
		mlx->ray->flag = 0;
		h_inter = h_inter_ft(mlx, nor_angle(mlx->ray->ray_ngl));
		v_inter = v_inter_ft(mlx, nor_angle(mlx->ray->ray_ngl));
		if (v_inter <= h_inter)
			mlx->ray->distance = v_inter;
		else
		{
			mlx->ray->distance = h_inter;
			mlx->ray->flag = 1;
		}
		render_wall(mlx, ray);
		ray++;
		mlx->ray->ray_ngl += (mlx->ply->fov_rd / S_W);
	}
}
