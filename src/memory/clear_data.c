/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:03:49 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/07/10 16:40:04 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"


// t_color  **clear_colors(t_color **colors)
// {
//     if (!colors)
//         return (NULL);
//     while(*colors++)
//     {
//         free(*colors);
//         *colors = NULL;
//     }
//     free(colors);
//     return (NULL);
// }

// t_texture **clear_texture(t_texture **texture)
// {
//     if(!texture)
//         return (NULL);
//     while (*texture++)
//     {
//         free(*texture);
//         *texture = NULL;
//     }
//     free(texture);
//     return (NULL);
// }

// t_map *clear_map(t_map *map)
// {
//     char **map2d;

//     map2d = map->map;
//     if (!map)
//         return (NULL);
//     if (map2d)
//     {
//         while(*map2d++)
//         {
//             free(*map2d);
//             *map2d = NULL;
//         }
//         free(map2d);
//         map->map = NULL;
//     }
//     free(map);
//     return (NULL);
// }

// t_parse *clear_parse(t_parse *parse)
// {
//     if (!parse)
//         return (NULL);
//     parse->colors = clear_colors(parse->colors);
//     parse->textures = clear_texture(parse->textures);
//     parse->map = clear_map(parse->map);
//     free(parse);
//     return (NULL);
// }

// void clear_data(t_data *data)
// {
//     if (!data)
//         return;
//     data->parse = clear_parse(data->parse);
//     free(data);
// }

void free_node_list(t_node *head)
{
    t_node *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        if (tmp->line != NULL)
            free(tmp->line);
        free(tmp);
    }
}

void free_list(t_parse *list)
{
	int i;

	i = 0;
    if (list != NULL)
    {
		while (i < 6)
		{
			free(list->elems[i]);
			i++;
		}
        free_node_list(list->map_head);
        free(list);
    }
}