/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:40:05 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/29 09:51:06 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

void	copy_content(t_mlx *mlx)
{
	t_node	*current;
	char	*line;
	int		i;
	int		j;

	i = 0;
	current = mlx->tmp->map_head;
	while (current != NULL)
	{
		j = 0;
		line = current->line;
		while (*line)
		{
			if (!valid_char(*line))
				exit(before_exit(mlx, 1));
			if (*line == '\t')
				j += 3;
			else
				mlx->dt->map2d[i][j] = *line;
			j++;
			line++;
		}
		i++;
		current = current->next;
	}
}

void	preparing_2d(t_mlx *mlx)
{
	int		i;
	int		j;
	char	**map;
	char	*line;

	map = mlx->dt->map2d;
	i = mlx->dt->h_map;
	j = mlx->dt->w_map;
	while (i >= 0)
	{
		line = my_malloc(sizeof(char) * (j + 1), 1);
		if (!line)
			exit(before_exit(mlx, 1));
		ft_memset(line, ' ', j);
		map[i] = line;
		i--;
	}
}

void	to_2d(t_mlx *mlx)
{
	int	max;
	int	i;

	i = 0;
	max = mlx->tmp->max_x;
	mlx->dt->h_map = mlx->tmp->y;
	mlx->dt->w_map = max;
	mlx->dt->map2d = (char **)my_malloc(sizeof(char *) * (mlx->tmp->y + 1), 1);
	while (i <= mlx->tmp->y)
	{
		mlx->dt->map2d[i] = my_malloc(sizeof(char) * mlx->dt->w_map, 1);
		if (!mlx->dt->map2d[i])
			exit(before_exit(mlx, 1));
		i++;
	}
	if (!mlx->dt->map2d)
		exit(before_exit(mlx, 1));
	preparing_2d(mlx);
	copy_content(mlx);
}

void	verify_elements(t_mlx *mlx)
{
	int		i;
	int		id;
	char	*check_list;

	i = 0;
	id = -1;
	check_list = ft_strdup("NSWEFCOOEA");
	while (i < 6 && mlx->tmp->elems[i] != NULL)
	{
		id = id_check(mlx->tmp->elems[i][0]);
		if (id < 0 || id > 5)
			exit(before_exit(mlx, 1));
		if (mlx->tmp->elems[i][0][0] != check_list[id])
			exit(before_exit(mlx, 1));
		check_data(mlx, id, mlx->tmp->elems[i][1]);
		if (mlx->tmp->elems[i][2] != NULL)
			exit(before_exit(mlx, 1));
		check_list[id] = '-';
		i++;
	}
}

void	parse(t_mlx *mlx, char *file_name)
{
	int	fd;

	file_check(mlx, file_name, ".cub");
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(before_exit(mlx, 1));
	read_file(mlx, fd);
	verify_elements(mlx);
	to_2d(mlx);
	check_map(mlx);
	close(fd);
}
