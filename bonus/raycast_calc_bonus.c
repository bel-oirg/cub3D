/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:09:33 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/29 09:49:04 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

int	wall_hit(float x, float y, t_mlx *mlx)
{
	int	x_m;
	int	y_m;
	int	x_p;
	int	y_p;

	if (x < 0 || y < 0)
		return (1);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if ((y_m >= mlx->dt->h_map || x_m >= mlx->dt->w_map))
		return (1);
	if (mlx->dt->map2d[y_m] && mlx->dt->map2d[y_m][x_m])
	{
		if (mlx->dt->map2d[y_m][x_m] == '1')
			return (1);
		if (mlx->dt->map2d[y_m][x_m] == 'D')
		{
			x_p = floor(mlx->ply->plyr_x / TILE_SIZE);
			y_p = floor(mlx->ply->plyr_y / TILE_SIZE);
			if ((abs(x_m - x_p) < 3) && abs(y_m - y_p < 3))
				return (0);
			return (2);
		}
	}
	return (0);
}

float	v_y_inter(t_player *ply, float x_inter, float rad, float *y_step)
{
	float	y_inter;

	y_inter = ply->plyr_y + tan(rad) * (x_inter - ply->plyr_x);
	if ((*y_step < 0 && rad < M_PI && rad >= 0) || (*y_step > 0 && rad >= M_PI
			&& rad < 2 * M_PI))
		*y_step *= -1;
	return (y_inter);
}

float	v_x_inter(int plyr_x, float rad, float *x_step, int *pxl)
{
	float	x_inter;

	x_inter = floor(plyr_x / TILE_SIZE) * TILE_SIZE;
	if (!(rad > M_PI / 2 && rad < 3 * M_PI / 2))
		x_inter += TILE_SIZE;
	else
	{
		*x_step *= -1;
		*pxl = -1;
	}
	return (x_inter);
}

float	h_y_inter(int plyr_y, float *y_step, float rad, int *pxl)
{
	double	y_inter;

	y_inter = floor(plyr_y / TILE_SIZE) * TILE_SIZE;
	if (rad >= 0 && rad < M_PI)
		y_inter += TILE_SIZE;
	else
	{
		*y_step *= -1;
		*pxl = -1;
	}
	return (y_inter);
}

float	h_x_inter(t_player *ply, float *x_step, float y_inter, float rad)
{
	float	x_inter;

	x_inter = ply->plyr_x + (y_inter - ply->plyr_y) / tan(rad);
	if ((*x_step > 0 && rad >= M_PI / 2 && rad < M_PI * 3 / 2) || (*x_step < 0
			&& !(rad >= M_PI / 2 && rad < M_PI * 3 / 2)))
		*x_step *= -1;
	return (x_inter);
}
