/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:18:12 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/20 21:23:14 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	wall_hit(float x, float y, t_mlx *mlx)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	if ((y_m >= mlx->dt->h_map || x_m >= mlx->dt->w_map))
		return (0);
	if (mlx->dt->map2d[y_m] && mlx->dt->map2d[y_m][x_m])
		if (mlx->dt->map2d[y_m][x_m] == '1')
			return (0);
	return (1);
}

float v_y_inter(t_player *ply, float x_inter, float rad, float *y_step)
{
	float y_inter;

	y_inter = ply->plyr_y + tan(rad) * (x_inter - ply->plyr_x);
    if ((*y_step < 0 && rad < M_PI && rad >= 0)
        || (*y_step > 0 && rad >= M_PI && rad < 2 * M_PI))
        *y_step *= -1;
	return (y_inter);
}

float v_x_inter(int plyr_x, float rad, float *x_step, int *pxl)
{
	float	x_inter;

    x_inter = floor(plyr_x / TILE_SIZE) * TILE_SIZE;
	if (!(rad > M_PI / 2 && rad < 3 * M_PI / 2)) //RIGHT
        x_inter += TILE_SIZE;
    else //LEFT
    {
        *x_step *= -1;
        *pxl = -1;
    }
	return (x_inter);
}

float  v_inter_ft(t_mlx *raw, float rad)
{
    float  y_inter;
    float  x_inter;
    float  x_step;
    float  y_step;
    int     pxl;
    
    pxl = 1;
    x_step = TILE_SIZE;
    y_step = x_step * tan(rad);

    /*
        here will be the virtucal intersction x and y
    */
    x_inter = v_x_inter(raw->ply->plyr_x, rad, &x_step, &pxl);
    y_inter = v_y_inter(raw->ply, x_inter, rad, &y_step);
    while (wall_hit( x_inter + pxl, y_inter,raw))
    {
        x_inter += x_step;
        y_inter += y_step;
    }
    raw->ray->v_inter.y = y_inter;
    raw->ray->v_inter.x = x_inter;
    return (sqrt(pow(x_inter - raw->ply->plyr_x, 2) + pow(y_inter - raw->ply->plyr_y, 2)));
}

float	h_y_inter(int plyr_y, float *y_step, float rad, int *pxl)
{
    double  y_inter;

	y_inter = floor(plyr_y / TILE_SIZE) * TILE_SIZE;
    if (rad >= 0 && rad < M_PI) //DOWN
        y_inter += TILE_SIZE;
    else
    { //UP
        *y_step *= -1;
        *pxl = -1;
    }
	return (y_inter);
}

float	h_x_inter(t_player *ply, float *x_step, float y_inter, float rad)
{
    float  x_inter;
	
	x_inter = ply->plyr_x + (y_inter - ply->plyr_y)/tan(rad);
    if ((*x_step > 0 && rad >= M_PI / 2 && rad < M_PI * 3 / 2) //LEFT
        || (*x_step < 0 && !(rad >= M_PI / 2 && rad < M_PI * 3 / 2))) //RIGHT
        *x_step *= -1;
	return(x_inter);
}

float  h_inter_ft(t_mlx *raw, float rad)
{
    float  y_inter;
    float  x_inter;
    float  x_step;
    float  y_step;
    int     pxl;
    
    pxl = 1;
    y_step = TILE_SIZE;
    x_step = TILE_SIZE / tan(rad);
    /*
        here is the horisontal intersection x and y
    */
    y_inter = h_y_inter(raw->ply->plyr_y, &y_step, rad, &pxl);
    x_inter = h_x_inter(raw->ply, &x_step, y_inter, rad);
    while (wall_hit(x_inter, y_inter + pxl, raw))
    {
        x_inter += x_step;
        y_inter += y_step;
    }
    raw->ray->h_inter.y = y_inter;
    raw->ray->h_inter.x = x_inter;
    return (sqrt(pow(x_inter - raw->ply->plyr_x, 2) + pow(y_inter - raw->ply->plyr_y, 2)));
}

void	cast_rays(t_mlx *mlx)	// cast the rays
{
	float	h_inter;
	float	v_inter;
	int		ray;

	ray = 0;
	mlx->ray->ray_ngl = mlx->ply->angle - (mlx->ply->fov_rd / 2); // the start angle
	while (ray < S_W) // loop for the rays
	{
		mlx->ray->flag = 0; // flag for the wall
		h_inter = h_inter_ft(mlx, nor_angle(mlx->ray->ray_ngl)); // get the horizontal intersection
		v_inter = v_inter_ft(mlx, nor_angle(mlx->ray->ray_ngl)); // get the vertical intersection
		if (v_inter <= h_inter) // check the distance
			mlx->ray->distance = v_inter; // get the distance
		else
		{
			mlx->ray->distance = h_inter; // get the distance
			mlx->ray->flag = 1; // flag for the wall
		}
		render_wall(mlx, ray); // render the wall
		ray++; // next ray
		mlx->ray->ray_ngl += (mlx->ply->fov_rd / S_W); // next angle
	}
}