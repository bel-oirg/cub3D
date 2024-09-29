/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:18:12 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/29 09:50:48 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

float	v_inter_ft(t_mlx *raw, float rad, int *wall_ty)
{
	float	y_inter;
	float	x_inter;
	float	x_step;
	float	y_step;
	int		pxl;

	pxl = 0;
	x_step = TILE_SIZE;
	y_step = x_step * tan(rad);
	x_inter = v_x_inter(raw->ply->plyr_x, rad, &x_step, &pxl);
	y_inter = v_y_inter(raw->ply, x_inter, rad, &y_step);
	while (1)
	{
		*wall_ty = wall_hit(x_inter + pxl, y_inter, raw);
		if (*wall_ty)
			break ;
		x_inter += x_step;
		y_inter += y_step;
	}
	raw->ray->v_inter.y = y_inter;
	raw->ray->v_inter.x = x_inter;
	return (sqrt(pow(x_inter - raw->ply->plyr_x, 2) + pow(y_inter
				- raw->ply->plyr_y, 2)));
}

float	h_inter_ft(t_mlx *raw, float rad, int *wall_ty)
{
	float	y_inter;
	float	x_inter;
	float	x_step;
	float	y_step;
	int		pxl;

	pxl = 0;
	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(rad);
	y_inter = h_y_inter(raw->ply->plyr_y, &y_step, rad, &pxl);
	x_inter = h_x_inter(raw->ply, &x_step, y_inter, rad);
	while (1)
	{
		*wall_ty = wall_hit(x_inter, y_inter + pxl, raw);
		if (*wall_ty)
			break ;
		x_inter += x_step;
		y_inter += y_step;
	}
	raw->ray->h_inter.y = y_inter;
	raw->ray->h_inter.x = x_inter;
	return (sqrt(pow(x_inter - raw->ply->plyr_x, 2) + pow(y_inter
				- raw->ply->plyr_y, 2)));
}

void	cast_rays(t_mlx *mlx)
{
	float	h_inter;
	float	v_inter;
	int		h_wall_ty;
	int		v_wall_ty;
	int		ray;

	ray = -1;
	mlx->ray->ray_ngl = mlx->ply->angle - (mlx->ply->fov_rd / 2);
	while (++ray < S_W)
	{
		mlx->ray->flag = 0;
		v_inter = v_inter_ft(mlx, nor_angle(mlx->ray->ray_ngl), &v_wall_ty);
		h_inter = h_inter_ft(mlx, nor_angle(mlx->ray->ray_ngl), &h_wall_ty);
		if (v_inter < h_inter)
			(1) && (mlx->wall_ty = v_wall_ty, mlx->ray->distance = v_inter);
		else
		{
			mlx->wall_ty = h_wall_ty;
			mlx->ray->distance = h_inter;
			mlx->ray->flag = 1;
		}
		render_wall(mlx, ray);
		mlx->ray->ray_ngl += (mlx->ply->fov_rd / S_W);
	}
}
