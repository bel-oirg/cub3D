/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:39:01 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/29 09:51:19 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

void	lil_cube(t_mlx *raw, int x, int y, int color)
{
	int	old_x;
	int	old_y;

	old_x = x;
	old_y = y;
	while (++y < old_y + MINI_SIZE)
	{
		x = old_x;
		while (++x < old_x + MINI_SIZE)
		{
			if (x < S_W && y < S_H)
				my_mlx_pixel_put(raw, x, y, color);
		}
	}
}

void	draw_circle(t_mlx *mlx)
{
	int	center;
	int	x;
	int	y;
	int	r;

	r = 8;
	center = MINI_SIZE * CUB_MAP + (MINI_SIZE / 2);
	y = -r;
	while (++y < r)
	{
		x = -r;
		while (++x < r)
		{
			if (x * x + y * y <= r * r)
				my_mlx_pixel_put(mlx, center + x, center + y, 0xFF0000FF);
			else
				my_mlx_pixel_put(mlx, center + x, center + y, 0xFF81F8AA);
		}
	}
}

void	calculate_positions(t_mlx *raw, t_ivector *tile, t_ivector *grid)
{
	tile->x = raw->ply->plyr_x / TILE_SIZE;
	tile->y = raw->ply->plyr_y / TILE_SIZE;
	grid->y = tile->y - CUB_MAP;
}

void	draw_mini_map(t_mlx *raw, t_ivector *tile, t_ivector *grid)
{
	while (++grid->y < tile->y + CUB_MAP)
	{
		grid->x = tile->x - CUB_MAP;
		while (++grid->x < tile->x + CUB_MAP)
		{
			if (!(grid->x >= 0 && grid->x < raw->dt->w_map
					&& grid->y >= 0 && grid->y < raw->dt->h_map))
				continue ;
			if (raw->dt->map2d[grid->y][grid->x] == '1')
				lil_cube(raw, (grid->x - tile->x + CUB_MAP) * MINI_SIZE,
					(grid->y - tile->y + CUB_MAP) * MINI_SIZE, 0xFF00A00A);
			else if (raw->dt->map2d[grid->y][grid->x] == 'D')
				lil_cube(raw, (grid->x - tile->x + CUB_MAP) * MINI_SIZE,
					(grid->y - tile->y + CUB_MAP) * MINI_SIZE, 0xCCFFE0AF);
			else if (grid->x == tile->x && grid->y == tile->y)
				draw_circle(raw);
			else
				lil_cube(raw, (grid->x - tile->x + CUB_MAP) * MINI_SIZE,
					(grid->y - tile->y + CUB_MAP) * MINI_SIZE, 0xFF81F8AA);
		}
	}
}

void	mini_map(t_mlx *raw)
{
	t_ivector	grid;
	t_ivector	tile;

	calculate_positions(raw, &tile, &grid);
	draw_mini_map(raw, &tile, &grid);
}
