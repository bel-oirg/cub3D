/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:15:15 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/05/27 18:54:40 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftlib.h"

// void *gc_malloc(size_t size)
// {
// 	void *address;
// 	t_gcnode *node;

// 	address = malloc(size);
// 	node = malloc(sizeof(t_gcnode));
//     if(!address || !node)
// 	{
//         gc_clear(node);
//         printf("Error\ncould not allocate memory\n");
//         exit(0);
//     }
// 	node->address = address;
// 	node->next = NULL;
// 	gc_add(node);
// 	return (address);
// }
void *gc_malloc(size_t size)
{
    void *address;
    t_gcnode *node;

    address = malloc(size);
    if (!address)
    {
        printf("Error\ncould not allocate memory\n");
        exit(0);
    }

    node = malloc(sizeof(t_gcnode));
    if (!node)
    {
        free(address); // Free the previously allocated memory
        printf("Error\ncould not allocate memory\n");
        exit(0);
    }

    node->address = address;
    node->next = NULL;
    gc_add(node);
    return (address);
}

void gc_free(void *address)
{
	if (!address)
		return;
	gc_remove(address);
}


void gc_clear()
{
	t_gcnode *current;
	t_gcnode *save;
	t_gclist *g_gc;

	g_gc = get_gclist();
	if (!g_gc)
		return;
	if (g_gc->node_used <= 0)
	{		
		free(g_gc);
		g_gc = NULL;
		return;
	}
	current = g_gc->head;
	save = current;
	while(current)
	{
		free(current->address);
		save = current;
		current = current->next;
		free(save);
	}
	free(g_gc);
	g_gc = NULL;
}