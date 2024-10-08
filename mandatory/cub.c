/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:21:22 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/27 08:40:24 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	game_loop(void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	hook(mlx, 0, 0);
	cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
}

void	init_the_player(t_mlx *mlx)
{
	char	dir;

	mlx->ply->plyr_x = mlx->dt->p_x * TILE_SIZE + TILE_SIZE / 2;
	mlx->ply->plyr_y = mlx->dt->p_y * TILE_SIZE + TILE_SIZE / 2;
	mlx->ply->fov_rd = (FOV * M_PI) / 180;
	dir = mlx->dt->map2d[mlx->dt->p_y][mlx->dt->p_x];
	if (dir == 'N')
		mlx->ply->angle = NORTH;
	else if (dir == 'S')
		mlx->ply->angle = SOUTH;
	else if (dir == 'E')
		mlx->ply->angle = 0;
	else
		mlx->ply->angle = M_PI;
	mlx->ply->l_r = 0;
	mlx->ply->rot = 0;
	mlx->ply->u_d = 0;
}

void	start_the_game(t_mlx *mlx)
{
	init_the_player(mlx);
	mlx_loop_hook(mlx->mlx_p, &game_loop, mlx);
	mlx_key_hook(mlx->mlx_p, &mlx_key, mlx);
	mlx_loop(mlx->mlx_p);
}
