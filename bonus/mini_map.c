/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:39:01 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/26 11:06:30 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

void    lil_cube(t_mlx *raw, int x, int y, int color)
{
	int old_x;
	int old_y;

	old_x = x;
	old_y = y;
	while (++y < old_y + MINI_SIZE)
	{
		x = old_x;
		while (++x < old_x + MINI_SIZE)
		{
			if (x < S_W && y < S_H)
				my_mlx_pixel_put(raw, x ,y, color);
		}
	}
}

void draw_circle(t_mlx *mlx)
{
	int center;
	int x;
	int y;
	int r;

	r = 8;
	center = MINI_SIZE * CUB_MAP + (MINI_SIZE / 2);
	y = -r;
	while (++y < r)
	{
		x = -r;
		while (++x < r)
		{
			if (x*x + y*y <= r*r)
				my_mlx_pixel_put(mlx, center + x, center + y, 0xFF0000FF);
			else
				my_mlx_pixel_put(mlx, center + x, center + y, 0xFF81F8AA);
		}
	}
}

void mini_map(t_mlx *raw)
{
	int             x;
	int             y;
	int             x_tile;
	int             y_tile;

	x_tile = raw->ply->plyr_x / TILE_SIZE;
	y_tile = raw->ply->plyr_y / TILE_SIZE;
	y = y_tile - CUB_MAP;
	while (++y < y_tile + CUB_MAP)
	{
		x = x_tile - CUB_MAP;
		while (++x < x_tile + CUB_MAP)
		{
			if (!(x >= 0 && x < raw->dt->w_map && y >= 0 && y < raw->dt->h_map))
				continue ;
			if (raw->dt->map2d[y][x] == '1')
				lil_cube(raw, (x - x_tile + CUB_MAP) * MINI_SIZE, (y - y_tile + CUB_MAP) * MINI_SIZE, 0xFF00A00A);
			else if (raw->dt->map2d[y][x] == 'D')
				lil_cube(raw, (x - x_tile + CUB_MAP) * MINI_SIZE, (y - y_tile + CUB_MAP) * MINI_SIZE, 0xCCFFE0AF);
			else if (x == x_tile && y == y_tile)
				draw_circle(raw);
			else
				lil_cube(raw, (x - x_tile + CUB_MAP) * MINI_SIZE, (y - y_tile + CUB_MAP) * MINI_SIZE, 0xFF81F8AA);
		}
	}
}
