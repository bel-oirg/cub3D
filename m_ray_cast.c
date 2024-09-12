/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_ray_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:36:20 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/12 11:42:48 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
    1_find the angle for the first ray

    2_Loop for each ray.

    3_Get the horizontal intersection

    4_Get the vertical interception

    5_Calculate the distance

    6_Take the closest distance
*/

int hit_wall(t_mlx raw, double x_inter, double y_inter)
{
    int x;
    int y;

    x = floor(x_inter / TILE_SIZE);
    y = floor(y_inter / TILE_SIZE);
    return (x >= S_W || y >= S_H || raw.dt->map2d[x][y])
}

double  h_inter(t_mlx raw)
{
    double  y_inter;
    double  x_inter;
    double  x_step;
    double  y_step;
    
    y_inter = floor(raw.ply->plyr_y / (float)TILE_SIZE) * TILE_SIZE;
    x_inter = raw.ply->plyr_x + (y_inter - raw.ply->plyr_y)/tan(raw.ply->angle);

    y_step = TILE_SIZE;
    x_step = y_step / tan(raw.ply->angle);

    while (!hit_wall(raw, x_inter, y_inter))
    {
        x_inter += x_step;
        y_inter += y_step;
    }
    return (sqrt(x_inter * x_inter + y_inter * y_inter));
}

double  v_inter(t_mlx raw)
{
    double  y_inter;
    double  x_inter;
    double  x_step;
    double  y_step;
    
    y_inter = raw.ply->plyr_y - tan(raw.ply->angle) * (x_inter - raw.ply->plyr_x);
    x_inter = floor(raw.ply->plyr_x / (float)TILE_SIZE) * TILE_SIZE + TILE_SIZE;

    y_step = x_step * tan(raw.ply->angle);
    x_step = TILE_SIZE;

    while (!hit_wall(raw, x_inter, y_inter))
    {
        x_inter += x_step;
        y_inter += y_step;
    }
    return (sqrt(x_inter * x_inter + y_inter * y_inter));
}

void    rayed(t_mlx raw)
{
    int     f_ray;
    int     f_x;
    double  _h;
    double  _v;

    f_ray = raw.ply->angle - FOV/2 ;
    f_x = -1;
    while (++f_x < S_W)
    {
        _h = h_inter(mlx, fx)
        _v = v_inter(mlx, fx)

        f_ray += FOV/S_W;
    }
}