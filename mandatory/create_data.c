/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:02:15 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/26 11:07:35 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

t_tmp *allocate_t_tmp(void)
{
	t_tmp *tmp;
	int i;

	tmp = (t_tmp *)my_malloc(sizeof(t_tmp),1);
	if (!tmp)
		return (NULL);
	tmp->elems = (char ***)my_malloc(6 * sizeof(char **),1);
	if (!(tmp->elems))
		return (free(tmp),NULL);
	i = 0;
	while (i < 6)
	{
		tmp->elems[i] = NULL;
		i++;
	}
	tmp->map_head = NULL;
	tmp->map_tail = NULL;
	tmp->y = 0;
	tmp->max_x = 0;
	return (tmp);
}

void add_node(t_tmp *list, char *line)
{
	t_node *new_node;

	new_node = my_malloc(sizeof(t_node),1);
	new_node->line = read_map(line,&new_node->x);
	if (new_node->x > list->max_x)
		list->max_x = new_node->x;
	new_node->next = NULL;
	if (list->map_head == NULL)
		list->map_head = new_node;
	else
		list->map_tail->next = new_node;
	list->map_tail = new_node;
}


int data_creating(t_data *data)
{
	data->config = (t_config *)my_malloc(sizeof(t_config),1);
	data->rgb = (int **)my_malloc(sizeof(int *) * 2,1);
	data->rgb[0] = (int *)my_malloc(sizeof(int) * 3,1);
	data->rgb[1] = (int *)my_malloc(sizeof(int) * 3,1);
	data->txtr = (t_texture *)my_malloc(sizeof(t_texture),1);
	if (!data->config || !data->rgb || !data->rgb[0] || !data->rgb[1] || !data->txtr)
		return (0);
	data->map2d = NULL;
	data->txtr->EA = NULL;
	data->txtr->WE = NULL;
	data->txtr->NO = NULL;
	data->txtr->SO = NULL;
	data->h_map = 0;
	data->w_map = 0;
	data->p_x = 0;
	data->p_y = 0;
	return (1);
}

int before_exit(t_mlx *mlx, int error)
{
	(void)mlx;
	if (error)
	{
		printf("Error\n");
		my_malloc(0,0);
		return (1);
	}
	my_malloc(0,14);
	return (0);
}

t_mlx *create_mlx_struct(void)
{
	t_mlx *mlx;

	mlx = (t_mlx *)my_malloc(sizeof(t_mlx),1);
	mlx->mlx_p = mlx_init(S_W,S_H,"cub3d",0);
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	mlx->ray = (t_ray *)my_malloc(sizeof(t_ray),1);
	mlx->ply = (t_player *)my_malloc(sizeof(t_player),1);
	mlx->dt = (t_data *)my_malloc(sizeof(t_data),1);
	mlx->tmp = allocate_t_tmp();
	if (!mlx || !mlx->mlx_p || !mlx->img || !mlx->ply || !mlx->ray || !mlx->tmp || !mlx->dt 
		|| !data_creating(mlx->dt) || !mlx->tmp)
		exit(before_exit(mlx,1));
	mlx->mouse_hidden = 0;
	mlx->ray->distance = 0;
	mlx->ray->ray_ngl = 0;
	mlx->ray->flag = 0;
	return (mlx);
}
