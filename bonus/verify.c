/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 00:54:29 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/27 01:50:03 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

void local_vars(t_mlx *mlx, char ***map, t_ivector *pos, t_ivector *i_pos)
{
	map = &mlx->dt->map2d;
	pos->x = mlx->dt->w_map;
	pos->y = mlx->dt->h_map;
	i_pos->x = 0;
	i_pos->y = 0;
}

void first_and_last(t_mlx *mlx)
{
	char *first;
	char *last;

	first = mlx->dt->map2d[0];
	last = mlx->dt->map2d[mlx->dt->h_map];
	while (*first)
	{
		if (*first != ' ' && *first != '1')
			exit(before_exit(mlx,1));
		first++;
	}
	while (*last)
	{
		if (*last != ' ' && *last != '1')
			exit(before_exit(mlx,1));
		last++;
	}
}

int door_logic(t_mlx *mlx,int i, int j)
{
	char limits[4];
	
	limits[0] = mlx->dt->map2d[i-1][j];
	limits[1] = mlx->dt->map2d[i][j-1];
	limits[2] = mlx->dt->map2d[i][j+1];
	limits[3] = mlx->dt->map2d[i+1][j];
	if ((limits[0] == '1' && limits[3] == '1') && (limits[1] == '1' || limits[2] == '1'))
			return (0);
	if (limits[0] == ' ' || limits[1] == ' ' || limits[2] == ' ' || limits[3] == ' ')
		return (0);
	if (limits[0] == '\0' || limits[1] == '\0' || limits[2] == '\0' || limits[3] == '\0')
		return (0);
	if (limits[0] == 'D' || limits[1] == 'D' || limits[2] == 'D' || limits[3] == 'D')
		return (0);
	if (limits[0] == '0' && limits[3] == '0' && limits[1] == '0' && limits[2] == '0')
		return (0);
	if (limits[0] != '1' && limits[3] != '1' && limits[1] == '1' && limits[2] == '1')
		return (1);
	if (limits[0] == '1' && limits[3] == '1' && limits[1] != '1' && limits[2] != '1')
		return (1);
	else
		return (0);
}

int srounded(t_mlx *mlx,int i, int j, int is_dor)
{
	char limits[4];

	if (i == 0 || j == 0 || i == mlx->dt->w_map - 1 || i == mlx->dt->h_map - 1)
		return (0);
	limits[0] = mlx->dt->map2d[i-1][j];
	limits[1] = mlx->dt->map2d[i][j-1];
	limits[2] = mlx->dt->map2d[i][j+1];
	limits[3] = mlx->dt->map2d[i+1][j];
	if (is_dor)
		return (door_logic(mlx,i,j));
	if (limits[0] == ' ' || limits[1] == ' ' || limits[2] == ' ' || limits[3] == ' ' || limits[2] == '\0')
		return (0);
	is_dor = 0;
	return (1);
}

void player(t_mlx *mlx)
{
	char **map;
	t_ivector pos;
	t_ivector i_pos;
	int player_count;
	char c;

	local_vars(mlx,&map,&pos,&i_pos);
	map = mlx->dt->map2d;
	player_count = 0;
	while(i_pos.y < (pos.y))
	{
		i_pos.x = 0;
		while (i_pos.x < pos.x)
		{
			c = map[i_pos.y][i_pos.x];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				player_count++;
				mlx->dt->p_x = i_pos.x;
				mlx->dt->p_y = i_pos.y;
			}
			i_pos.x++;
		}
		i_pos.y++;
	}
	if (player_count != 1 || !srounded(mlx,mlx->dt->p_y,mlx->dt->p_x,0))
		exit(before_exit(mlx,1));
}

void check_map(t_mlx *mlx)
{
	char **map;
	int i;
	int j;

	first_and_last(mlx);
	player(mlx);
	map = mlx->dt->map2d;
	i = 0;
	while (i < mlx->dt->h_map)
	{
		j  = 0;
		while (j < mlx->dt->w_map)
		{
			if (map[i][j] == '0' && !srounded(mlx,i,j,0))
				exit(before_exit(mlx,1));
			else if (map[i][j] == 'D' && !srounded(mlx,i,j,1))
				exit(before_exit(mlx,1));
			j++;
		}
		i++;
	}
}
