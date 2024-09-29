/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mv_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:20:19 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/29 09:51:01 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

void	rotate_player(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->ply->angle += ROTATION_SPEED;
		if (mlx->ply->angle > 2 * M_PI)
			mlx->ply->angle -= 2 * M_PI;
	}
	else
	{
		mlx->ply->angle -= ROTATION_SPEED;
		if (mlx->ply->angle < 0)
			mlx->ply->angle += 2 * M_PI;
	}
}

int	check_new_position(t_mlx *mlx, t_ivector new_cor)
{
	if (new_cor.x / TILE_SIZE >= mlx->dt->w_map
		|| new_cor.y / TILE_SIZE >= mlx->dt->h_map
		|| mlx->dt->map2d[new_cor.y / TILE_SIZE][new_cor.x / TILE_SIZE] == '1')
		return (0);
	return (1);
}

void	update_position(t_mlx *mlx, double move_x, double move_y, t_ivector new)
{
	t_ivector	map_grid;

	map_grid.x = mlx->ply->plyr_x / TILE_SIZE;
	map_grid.y = mlx->ply->plyr_y / TILE_SIZE;
	if (move_x > 0)
	{
		if (mlx->dt->map2d[map_grid.y][(new.x + BUFFER_DISTANCE)
			/ TILE_SIZE] != '1')
			mlx->ply->plyr_x = new.x;
	}
	else if (mlx->dt->map2d[map_grid.y][(new.x - BUFFER_DISTANCE)
		/ TILE_SIZE] != '1')
		mlx->ply->plyr_x = new.x;
	if (move_y > 0)
	{
		if (mlx->dt->map2d[(new.y + BUFFER_DISTANCE)
				/ TILE_SIZE][map_grid.x] != '1')
			mlx->ply->plyr_y = new.y;
	}
	else if (mlx->dt->map2d[(new.y - BUFFER_DISTANCE)
			/ TILE_SIZE][map_grid.x] != '1')
		mlx->ply->plyr_y = new.y;
}

void	move_player(t_mlx *mlx, double move_x, double move_y)
{
	t_ivector	map_grid;
	t_ivector	new_cor;

	new_cor.x = roundf(mlx->ply->plyr_x + move_x);
	new_cor.y = roundf(mlx->ply->plyr_y + move_y);
	map_grid.x = mlx->ply->plyr_x / TILE_SIZE;
	map_grid.y = mlx->ply->plyr_y / TILE_SIZE;
	if (!check_new_position(mlx, new_cor))
		return ;
	update_position(mlx, move_x, move_y, new_cor);
}

void	hook(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->ply->rot == 1)
		rotate_player(mlx, 1);
	if (mlx->ply->rot == -1)
		rotate_player(mlx, 0);
	if (mlx->ply->l_r == 1)
	{
		move_x = -sin(mlx->ply->angle) * PLAYER_SPEED;
		move_y = cos(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->l_r == -1)
	{
		move_x = sin(mlx->ply->angle) * PLAYER_SPEED;
		move_y = -cos(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->u_d == 1)
	{
		move_x = cos(mlx->ply->angle) * PLAYER_SPEED;
		move_y = sin(mlx->ply->angle) * PLAYER_SPEED;
	}
	if (mlx->ply->u_d == -1)
	{
		move_x = -cos(mlx->ply->angle) * PLAYER_SPEED;
		move_y = -sin(mlx->ply->angle) * PLAYER_SPEED;
	}
	move_player(mlx, move_x, move_y);
}
