/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:03:49 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/18 11:54:34 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

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

void free_list(t_tmp *list)
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