/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:20:32 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/05/10 23:52:16 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftlib.h"

static void gc_remove_cases(t_gclist *g_gc,t_gcnode *node,t_gcnode *prev, t_gcnode *next)
{
	free(node->address);
	g_gc->free_call++;
	g_gc->node_used--;
	if (g_gc->head == node && g_gc->tail == node) // 1
	{
		g_gc->head = NULL;
		g_gc->tail = NULL;
	}
	else if (g_gc->tail == node && g_gc->head != node)
	{
		g_gc->tail = prev;
		g_gc->tail->next = NULL;
	}
	else if (g_gc->head == node && g_gc->tail != node)
		g_gc->head = node->next;
	else
		prev->next = next;
	free(node);
}


void gc_remove(void *address)
{
	t_gclist *g_gc;
	t_gcnode *current;
	t_gcnode *prev;
	t_gcnode *next;
	
	g_gc = get_gclist();
	if (!g_gc)
		return;
	current = g_gc->head;
	prev = NULL;
	next = NULL;
	while(current)
	{
		if (current->address == address)
			return (gc_remove_cases(g_gc,current,prev,next));
		prev = current;
		next = current->next;
		current = current->next;	
	}
	g_gc->data_size -= sizeof(t_gcnode);
}


void gc_add(t_gcnode *node)
{
	t_gclist *g_gc;

	g_gc = get_gclist();
	if (!g_gc)
		return;
	if (!g_gc->head && !g_gc->tail)
	{
		g_gc->head = node;
		g_gc->tail = node;
		g_gc->malloc_call++;
		g_gc->node_used++;
	}
	g_gc->tail->next = node;
	g_gc->tail = node;
	g_gc->malloc_call++;
	g_gc->node_used++;
	g_gc->data_size += sizeof(t_gcnode);
}
