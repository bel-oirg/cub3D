/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_helper_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:07:16 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/29 09:50:29 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

void	local_vars(t_mlx *mlx, char ***map, t_ivector *pos, t_ivector *i_pos)
{
	*map = mlx->dt->map2d;
	pos->x = mlx->dt->w_map;
	pos->y = mlx->dt->h_map;
	i_pos->x = 0;
	i_pos->y = -1;
}

void	first_and_last(t_mlx *mlx)
{
	char	*first;
	char	*last;

	first = mlx->dt->map2d[0];
	last = mlx->dt->map2d[mlx->dt->h_map];
	while (*first)
	{
		if (*first != ' ' && *first != '1')
			exit(before_exit(mlx, 1));
		first++;
	}
	while (*last)
	{
		if (*last != ' ' && *last != '1')
			exit(before_exit(mlx, 1));
		last++;
	}
}
