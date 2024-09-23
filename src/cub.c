/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:21:22 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/22 23:41:31 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	game_loop(void *ml)	// game loop
{
	t_mlx	*mlx;

	mlx = ml;
	if (!mlx->mlx_p || !mlx->img) // already checked on the init
		printf("non\n");
	mlx_delete_image(mlx->mlx_p, mlx->img);	
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	hook(mlx, 0, 0);
	cast_rays(mlx);
	render_sp(mlx);
	mini_map(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0); // put the image to the window
}

void init_the_player(t_mlx *mlx)	// init the player structure
{
	mlx->ply->plyr_x = mlx->dt->p_x * TILE_SIZE + TILE_SIZE / 2;
	mlx->ply->plyr_y = mlx->dt->p_y * TILE_SIZE + TILE_SIZE / 2;
	mlx->ply->fov_rd = (FOV * M_PI) / 180;
	mlx->ply->angle = M_PI;

	mlx->ply->l_r = 0;
	mlx->ply->rot = 0;
	mlx->ply->u_d = 0;
}

void	start_the_game(t_mlx *mlx)
{
	init_the_player(mlx);
	sprited(mlx);
	mlx_loop_hook(mlx->mlx_p, &game_loop, mlx);
	mlx_key_hook(mlx->mlx_p, &mlx_key, mlx);
	mlx_loop(mlx->mlx_p);
}