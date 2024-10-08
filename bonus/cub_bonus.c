/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:21:22 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/29 09:45:50 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

void	game_loop(void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	hook(mlx, 0, 0);
	cast_rays(mlx);
	render_sp(mlx);
	mini_map(mlx);
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

void	mouse_mod_updating(mouse_key_t key, action_t action,
		modifier_key_t mods, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	(void)mods;
	if (key == MLX_MOUSE_BUTTON_LEFT && (action == MLX_PRESS
			|| action == MLX_REPEAT))
		mlx->sprite->is_sp = 1;
}

void	mouse_movement(double xpos, double ypos, void *param)
{
	static double	lastx = 0;
	static double	lasty = 0;
	t_mlx			*mlx;
	double			xoffset;
	double			yoffset;

	mlx = (t_mlx *)param;
	xoffset = xpos - lastx;
	yoffset = lasty - ypos;
	lastx = xpos;
	lasty = ypos;
	mlx->ply->angle += xoffset * 0.005;
	mlx->ply->u_d += yoffset * 0.005;
	if (mlx->ply->angle > 2 * M_PI)
		mlx->ply->angle -= 2 * M_PI;
	else if (mlx->ply->angle < 0)
		mlx->ply->angle += 2 * M_PI;
}

void	start_the_game(t_mlx *mlx)
{
	init_the_player(mlx);
	sprited(mlx);
	mlx_set_mouse_pos(mlx->mlx_p, S_W / 2, S_H / 2);
	mlx_loop_hook(mlx->mlx_p, &game_loop, mlx);
	mlx_key_hook(mlx->mlx_p, &mlx_key, mlx);
	mlx_cursor_hook(mlx->mlx_p, &mouse_movement, mlx);
	mlx_mouse_hook(mlx->mlx_p, &mouse_mod_updating, mlx);
	mlx_loop(mlx->mlx_p);
}
