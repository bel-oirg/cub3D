/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:02:15 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/07/10 16:42:23 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

t_parse *parse_list(void)
{
    t_parse *list;
	int i;

	i = 0;
    list = malloc(sizeof(t_parse));
    if (!list)
        return (NULL);
	while(i < 6)
	{
		list->elems[i] = NULL;
		i++;
	}
    list->map_head = NULL;
    list->map_tail = NULL;
    list->y = 0;
	list->max_x = 0;
    return (list);
}

void add_node(t_parse *list, char *line)
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

t_config* create_configs(void) 
{
	t_config *config;

	config = malloc(sizeof(t_config));
	if (config == NULL)
		return NULL;
    config->path[0] = "";
    config->path[1] = "";
    config->path[2] = "";
    config->path[3] = "";
	config->rgb[0][0] = 0;
    config->rgb[0][1] = 0;  
    config->rgb[0][2] = 0;  
    config->rgb[1][0] = 0;  
    config->rgb[1][1] = 0;
    config->rgb[1][2] = 0;
	return(config);
}

t_map	*create_map(void)
{
	t_map  *map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->player_pos.x = 0;
	map->player_pos.y = 0;
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	map->player_dir = '-';
	return (map);
}

t_data	*create_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->config = create_configs();
	if (!data->config) 
	{
        free(data);
        return (NULL);
    }
	data->map = create_map();
	if (!data->map) 
	{
        free(data->config);
        free(data);
        return (NULL);
    }
	return (data);
}
