/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 00:54:29 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/29 09:50:22 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

void	player(t_mlx *mlx)
{
	char		**map;
	t_ivector	pos;
	t_ivector	i_pos;
	int			player_count;
	char		c;

	local_vars(mlx, &map, &pos, &i_pos);
	map = mlx->dt->map2d;
	player_count = 0;
	while (++i_pos.y < (pos.y))
	{
		i_pos.x = -1;
		while (++i_pos.x < pos.x)
		{
			c = map[i_pos.y][i_pos.x];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				player_count++;
				mlx->dt->p_x = i_pos.x;
				mlx->dt->p_y = i_pos.y;
			}
		}
	}
	if (player_count != 1 || !srounded(mlx, mlx->dt->p_y, mlx->dt->p_x, 0))
		before_exit(mlx, 1);
}

void	check_map(t_mlx *mlx)
{
	char	**map;
	int		i;
	int		j;

	first_and_last(mlx);
	player(mlx);
	map = mlx->dt->map2d;
	i = 0;
	while (i < mlx->dt->h_map)
	{
		j = 0;
		while (j < mlx->dt->w_map)
		{
			if (map[i][j] == '0' && !srounded(mlx, i, j, 0))
				exit(before_exit(mlx, 1));
			else if (map[i][j] == 'D' && !srounded(mlx, i, j, 1))
				exit(before_exit(mlx, 1));
			j++;
		}
		i++;
	}
}
