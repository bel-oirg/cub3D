/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:46:21 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/29 09:48:40 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

void	get_limits(char (*limits)[4], t_mlx *mlx, int i, int j)
{
	(*limits)[0] = mlx->dt->map2d[i - 1][j];
	(*limits)[1] = mlx->dt->map2d[i][j - 1];
	(*limits)[2] = mlx->dt->map2d[i][j + 1];
	(*limits)[3] = mlx->dt->map2d[i + 1][j];
}

int	check_zero_conditions(char *limits)
{
	if ((limits[0] == '1' && limits[3] == '1') && (limits[1] == '1'
			|| limits[2] == '1'))
		return (0);
	if (limits[0] == ' ' || limits[1] == ' ' || limits[2] == ' '
		|| limits[3] == ' ')
		return (0);
	if (limits[0] == '\0' || limits[1] == '\0' || limits[2] == '\0'
		|| limits[3] == '\0')
		return (0);
	if (limits[0] == 'D' || limits[1] == 'D' || limits[2] == 'D'
		|| limits[3] == 'D')
		return (0);
	if (limits[0] == '0' && limits[3] == '0' && limits[1] == '0'
		&& limits[2] == '0')
		return (0);
	return (-1);
}

int	check_one_conditions(char *limits)
{
	if (limits[0] != '1' && limits[3] != '1' && limits[1] == '1'
		&& limits[2] == '1')
		return (1);
	if (limits[0] == '1' && limits[3] == '1' && limits[1] != '1'
		&& limits[2] != '1')
		return (1);
	return (-1);
}

int	door_logic(t_mlx *mlx, int i, int j)
{
	char	limits[4];
	int		zero_check;
	int		one_check;

	get_limits(&limits, mlx, i, j);
	zero_check = check_zero_conditions(limits);
	if (zero_check != -1)
		return (zero_check);
	one_check = check_one_conditions(limits);
	if (one_check != -1)
		return (one_check);
	return (0);
}

int	srounded(t_mlx *mlx, int i, int j, int is_dor)
{
	char	limits[4];

	if (i == 0 || j == 0 || i == mlx->dt->w_map - 1 || i == mlx->dt->h_map - 1)
		return (0);
	limits[0] = mlx->dt->map2d[i - 1][j];
	limits[1] = mlx->dt->map2d[i][j - 1];
	limits[2] = mlx->dt->map2d[i][j + 1];
	limits[3] = mlx->dt->map2d[i + 1][j];
	if (is_dor)
		return (door_logic(mlx, i, j));
	if (limits[0] == ' ' || limits[1] == ' ' || limits[2] == ' '
		|| limits[3] == ' ' || limits[2] == '\0')
		return (0);
	is_dor = 0;
	return (1);
}
