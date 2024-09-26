/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:20:19 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/26 11:22:59 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	ft_reles(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		mlx->ply->l_r = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		mlx->ply->l_r = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		mlx->ply->u_d = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		mlx->ply->u_d = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		mlx->ply->rot = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		mlx->ply->rot = 0;
}

void mlx_key(mlx_key_data_t keydata, void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		exit(before_exit(mlx,0));
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		mlx->ply->l_r = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) 
		mlx->ply->l_r = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		mlx->ply->u_d = -1;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		mlx->ply->u_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT ))
		mlx->ply->rot = -1;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		mlx->ply->rot = 1;
	ft_reles(keydata, mlx);
}

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

void	move_player(t_mlx *mlx, double move_x, double move_y)
{
	int 	map_grid_x;
	int  	map_grid_y;
	int		new_x;
	int		new_y;
	
	double 		d_map_grid_x;
	double  	d_map_grid_y;
	double 		nd_x;
	double 		nd_y;
	double		d_new_x;
	double		d_new_y;
	int 	r_x;
	int 	r_y;

	new_x = roundf(mlx->ply->plyr_x + move_x);
	new_y = roundf(mlx->ply->plyr_y + move_y);
	d_new_x = mlx->ply->plyr_x + move_x;
	d_new_y = mlx->ply->plyr_y + move_y;
	map_grid_x = (new_x / TILE_SIZE);
	map_grid_y = (new_y / TILE_SIZE);
	d_map_grid_x = (d_new_x / TILE_SIZE);
	d_map_grid_y = (d_new_y / TILE_SIZE);
	nd_x = d_map_grid_x + 0.5;
	nd_y = d_map_grid_y + 0.5;
	r_x = roundf(d_map_grid_x);
	r_y = roundf(d_map_grid_y);

	
	printf("---------------------------\n");
	printf("n_x:%d n_y%d\n",new_x,new_y);
	printf("n_x:%F n_y%F\n",d_new_x,d_new_y);
	printf("the float is x:%F y:%F\n",d_map_grid_x,d_map_grid_y);
	printf("the original is x:%d y:%d\n",map_grid_x,map_grid_y);
	printf("the round is x:%d y:%d\n",r_x,r_y);
	printf("the nd_x%F nd_y%F\n",nd_x,nd_y);
	printf("the round of nd_x%f nd_y%f\n",roundf(nd_x),roundf(nd_y));
	printf("---------------------------\n");
	
	// if (mlx->dt->map2d[map_grid_y][map_grid_x] != '1' && \
	// (mlx->dt->map2d[map_grid_y][mlx->ply->plyr_x / TILE_SIZE] != '1' && \
	// mlx->dt->map2d[mlx->ply->plyr_y / TILE_SIZE][map_grid_x] != '1')) 
	// {
	// 	mlx->ply->plyr_x = new_x;
	// 	mlx->ply->plyr_y = new_y;
	// }
	if (mlx->dt->map2d[r_y][r_x] != '1' && \
	(mlx->dt->map2d[map_grid_y][mlx->ply->plyr_x / TILE_SIZE] != '1' && \
	mlx->dt->map2d[mlx->ply->plyr_y / TILE_SIZE][map_grid_x] != '1')) 
	{
		mlx->ply->plyr_x = new_x;
		mlx->ply->plyr_y = new_y;
	}
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
