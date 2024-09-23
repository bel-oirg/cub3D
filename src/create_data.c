/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:02:15 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/21 20:04:48 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

t_tmp *allocate_t_tmp(void)
{
    t_tmp *tmp;
    int i;

    tmp = (t_tmp *)malloc(sizeof(t_tmp));
    if (!tmp)
		return (NULL);
    tmp->elems = (char ***)malloc(6 * sizeof(char **));
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

    new_node = malloc(sizeof(t_node));
    new_node->line = read_map(line,&new_node->x);
	new_node->line = line;
	if (new_node->x > list->max_x)
		list->max_x = new_node->x;
    new_node->next = NULL;
    if (list->map_head == NULL)
        list->map_head = new_node;
    else
        list->map_tail->next = new_node;
    list->map_tail = new_node;
}

void free_tmp(t_tmp *tmp)
{
    int i;

    if (tmp)
	{
        if (tmp->elems)
		{
            i = 0;
            while (i < 6)
			{
                if (tmp->elems[i])
                    free(tmp->elems[i]);
                i++;
            }
            free(tmp->elems);
        }
        free(tmp);
    }
}

/*
	this function will be used
	to free before exit i will use
	a variable to know where step
	im
	1 : error allocation of data
	2 : error at parsing
	3 : error at rendring
	typedef struct s_mlx	//the mlx structure
	{
		mlx_image_t		*img;	// the image
		mlx_t			*mlx_p;	// the mlx pointer
		t_ray			*ray;	// the ray structure
		t_data			*dt;	// the data structure
		t_player		*ply;	// the player structure
	}	t_mlx;
*/

int data_creating(t_data *data)
{
	data->config = (t_config *)malloc(sizeof(t_config));
	if (!data->config)
		return (0);
	data->map2d = NULL;
	data->config->path = (char **)malloc(sizeof(char *) * 4);
	data->config->path[0] = NULL;
	data->config->path[1] = NULL;
	data->config->path[2] = NULL;
	data->config->path[3] = NULL;
	if (!data->config->path)
		return (0);
	data->config->rgb = (int **)malloc(sizeof(int *) * 2);
	data->config->rgb[0] = (int *)malloc(sizeof(int) * 3);
	data->config->rgb[1] = (int *)malloc(sizeof(int) * 3);
	if (!data->config->rgb)
		return (0);
	data->txtr = (t_texture *)malloc(sizeof(t_texture));
	data->txtr->EA = NULL;
	data->txtr->WE = NULL;
	data->txtr->NO = NULL;
	data->txtr->SO = NULL;
	return(1);
}

// void before_exit(t_mlx *mlx, int error_flag)
// {
// 	int i;

// 	i = -1;
// 	if (error_flag)
// 		printf("Error\n");
// 	if (mlx->dt)
// 	{
// 		if (mlx->dt->config)
// 		{
// 			while(mlx->dt->config->path[++i])
// 				free(mlx->dt->config->path[i]);
// 			i = -1;
// 			if (mlx->dt->config->rgb[0])
// 				free(mlx->dt->config->rgb[0]);
// 			if (mlx->dt->config->rgb[1])
// 				free(mlx->dt->config->rgb[1]);
// 			i = -1;
// 			if (mlx->dt->map2d)
// 				while (mlx->dt->map2d[++i])
// 					free(mlx->dt->map2d[i]);	
// 		}
// 	}
// 	(mlx->ray) ,(free(mlx->ray));
// 	(mlx->ply) ,(free(mlx->ply));
// 	(mlx->img) ,(free(mlx->img));
// 	(mlx->tmp) ,(free_tmp(mlx->tmp));
// 	(mlx), (free(mlx));
// }
void free_config_and_map(t_data *dt)
{
    int i;

    i = -1;
    if (dt)
	{
		if (dt->config)
		{
        	while (dt->config->path[++i])
        	    free(dt->config->path[i]);
        	i = -1;
        	if (dt->config->rgb[0])
        	    free(dt->config->rgb[0]);
        	if (dt->config->rgb[1])
        	    free(dt->config->rgb[1]);
		}
        i = -1;
        if (dt->map2d)
            while (dt->map2d[++i])
                free(dt->map2d[i]);
		free(dt);
    }
}

void before_exit(t_mlx *mlx, int error_flag)
{
    int i;

    i = -1;
    if (error_flag)
	{
        printf("Error\n");
		return ;
	}
    if (mlx->dt)
        free_config_and_map(mlx->dt);
    if (mlx->ray)
        free(mlx->ray);
    if (mlx->ply)
        free(mlx->ply);
    if (mlx->img)
        free(mlx->img);
    if (mlx->tmp)
        free_tmp(mlx->tmp);
    free(mlx);
	mlx_delete_image(mlx->mlx_p, mlx->img); // delete the image
	mlx_close_window(mlx->mlx_p); // close the window
	mlx_terminate(mlx->mlx_p); // terminate the mlx pointer
	exit(1);
}

/*
	i will allocate for the new
	data struct

	typedef struct s_data	//the data structure
	{
		t_config *config;
		char	**map2d;	// the map
		int		p_x;		// player x position in the map
		int		p_y;		// player y position in the map
		int		w_map;		// map width
		int		h_map;		// map height
	}	t_data;
*/
t_mlx *create_mlx_struct(void)
{
	t_mlx *mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
		before_exit(NULL,1);
	mlx->mlx_p = mlx_init(S_W,S_H,"cub3d",0);
	if (!mlx->mlx_p)
		before_exit(mlx,1);
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H); //TODO why malloc here
	if (!mlx->img)
		before_exit(mlx,1); 
	mlx->ply = (t_player *)malloc(sizeof(t_player));
	if (!mlx->ply)
		before_exit(mlx,1);
	mlx->ray = (t_ray *)malloc(sizeof(t_ray));
	if (!mlx->ray)
		before_exit(mlx,1);
	mlx->ray->distance = 0;
	mlx->ray->ray_ngl = 0;
	mlx->ray->flag = 0;
	mlx->dt = (t_data *)malloc(sizeof(t_data));
	if (!mlx->dt || !data_creating(mlx->dt))
		before_exit(mlx,1);

	mlx->sprite = malloc(sizeof(t_sp));
	int i;
	i = -1;
	while(++i <= SP_FRAMES)
		mlx->sprite->txt[i] = malloc(sizeof(mlx_texture_t) * SP_FRAMES);
	
	mlx->tmp = allocate_t_tmp();
	if (!mlx->tmp)
		before_exit(mlx,1);
	return (mlx);
}
