/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:02:15 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/29 09:45:31 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

void	allocate_t_tmp(t_mlx *raw)
{
	int	i;

	raw->tmp = (t_tmp *)my_malloc(sizeof(t_tmp), 1);
	raw->tmp->elems = (char ***)my_malloc(6 * sizeof(char **), 1);
	i = -1;
	while (++i < 6)
		raw->tmp->elems[i] = NULL;
	raw->tmp->map_head = NULL;
	raw->tmp->map_tail = NULL;
	raw->tmp->y = 0;
	raw->tmp->max_x = 0;
}

void	add_node(t_tmp *list, char *line)
{
	t_node	*new_node;

	new_node = my_malloc(sizeof(t_node), 1);
	new_node->line = read_map(line, &new_node->x);
	if (new_node->x > list->max_x)
		list->max_x = new_node->x;
	new_node->next = NULL;
	if (list->map_head == NULL)
		list->map_head = new_node;
	else
		list->map_tail->next = new_node;
	list->map_tail = new_node;
}

void	data_creating(t_mlx *mlx)
{
	mlx->dt->config = (t_config *)my_malloc(sizeof(t_config), 1);
	mlx->dt->rgb = (int **)my_malloc(sizeof(int *) * 2, 1);
	mlx->dt->rgb[0] = (int *)my_malloc(sizeof(int) * 3, 1);
	mlx->dt->rgb[1] = (int *)my_malloc(sizeof(int) * 3, 1);
	mlx->dt->txtr = (t_texture *)my_malloc(sizeof(t_texture), 1);
	mlx->dt->map2d = NULL;
	mlx->dt->txtr->ea = NULL;
	mlx->dt->txtr->we = NULL;
	mlx->dt->txtr->no = NULL;
	mlx->dt->txtr->so = NULL;
	mlx->dt->txtr->door = mlx_load_png(DOOR);
	if (!mlx->dt->txtr->door)
		before_exit(mlx, 1);
	mlx->dt->h_map = 0;
	mlx->dt->w_map = 0;
	mlx->dt->p_x = 0;
	mlx->dt->p_y = 0;
}

int	before_exit(t_mlx *mlx, int error)
{
	int	index;

	index = -1;
	if (error)
		printf("Error\n");
	if (mlx->dt->txtr->ea)
		mlx_delete_texture(mlx->dt->txtr->ea);
	if (mlx->dt->txtr->no)
		mlx_delete_texture(mlx->dt->txtr->no);
	if (mlx->dt->txtr->we)
		mlx_delete_texture(mlx->dt->txtr->we);
	if (mlx->dt->txtr->so)
		mlx_delete_texture(mlx->dt->txtr->so);
	while (++index < SP_FRAMES)
		if (mlx->sprite->txt[index])
			mlx_delete_texture(mlx->sprite->txt[index]);
	if (mlx->dt->txtr->door)
		mlx_delete_texture(mlx->dt->txtr->door);
	if (mlx->img)
		mlx_delete_image(mlx->mlx_p, mlx->img);
	my_malloc(0, 14);
	return (0);
}

t_mlx	*create_mlx_struct(void)
{
	t_mlx	*mlx;
	int		index;

	mlx = (t_mlx *)my_malloc(sizeof(t_mlx), 1);
	mlx->ray = (t_ray *)my_malloc(sizeof(t_ray), 1);
	mlx->ply = (t_player *)my_malloc(sizeof(t_player), 1);
	mlx->dt = (t_data *)my_malloc(sizeof(t_data), 1);
	mlx->sprite = my_malloc(sizeof(t_sp), 1);
	allocate_t_tmp(mlx);
	index = -1;
	while (++index < SP_FRAMES)
		mlx->sprite->txt[index] = NULL;
	mlx->mlx_p = mlx_init(S_W, S_H, "cub3d", true);
	if (!mlx->mlx_p)
		my_malloc(0, 0);
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	if (!mlx->img)
		(1) && (mlx_terminate(mlx->mlx_p), my_malloc(0, 0));
	mlx->wall_ty = 0;
	data_creating(mlx);
	mlx->mouse_hidden = 0;
	mlx->ray->distance = 0;
	mlx->ray->ray_ngl = 0;
	mlx->ray->flag = 0;
	return (mlx);
}
