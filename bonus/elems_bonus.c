/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 00:54:32 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/29 09:46:02 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

int	id_check(char *id)
{
	char	*elems;
	int		i;

	i = 0;
	elems = "NSWEFCOOEA";
	if (!id)
		return (-1);
	while (i < 6)
	{
		if (id[0] == elems[i])
			break ;
		i++;
	}
	if (i == 6)
		return (-1);
	if (i < 4 && (id[1] != elems[i + 6] || id[2] != '\0'))
		return (-1);
	if ((i == 4 || i == 5) && id[1] != '\0')
		return (-1);
	return (i);
}

int	check_arg(char **args, int *rgb)
{
	int	i;
	int	j;

	i = 0;
	while (args[i] != NULL && i < 3)
	{
		j = 0;
		rgb[i] = 0;
		while (args[i][j])
		{
			if (!(args[i][j] >= '0' && args[i][j] <= '9'))
				return (0);
			rgb[i] = rgb[i] * 10 + (args[i][j] - '0');
			if (!(rgb[i] >= 0 && rgb[i] <= 255))
				return (0);
			j++;
		}
		i++;
	}
	if (i != 3 || args[3] != NULL)
		return (0);
	return (1);
}

void	check_color(t_mlx *mlx, char *line, int id)
{
	char	**rgb;
	int		rgb2[3];

	rgb = ft_split2(line, ',');
	if (!check_arg(rgb, rgb2))
		before_exit(mlx, 1);
	mlx->dt->rgb[id][0] = rgb2[0];
	mlx->dt->rgb[id][1] = rgb2[1];
	mlx->dt->rgb[id][2] = rgb2[2];
}

void	load_png(t_mlx *mlx, char *line, int id)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(line);
	if (!texture)
		before_exit(mlx, 1);
	if (id == 0)
		mlx->dt->txtr->no = texture;
	else if (id == 1)
		mlx->dt->txtr->so = texture;
	else if (id == 2)
		mlx->dt->txtr->we = texture;
	else
		mlx->dt->txtr->ea = texture;
}

void	check_data(t_mlx *mlx, int id, char *line)
{
	if (id < 4)
	{
		if (!line)
			before_exit(mlx, 1);
		file_check(mlx, line, ".png");
		load_png(mlx, line, id);
	}
	else
	{
		if (!line)
			before_exit(mlx, 1);
		check_color(mlx, line, id - 4);
	}
}
