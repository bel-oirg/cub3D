/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_getset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:14:04 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/05/10 23:52:57 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftlib.h"

static t_gclist	*g_gc = NULL;


void set_gclist()
{
	if (g_gc)
		return;
	g_gc = (t_gclist *)malloc(sizeof(t_gclist));
	if (!g_gc)
		return;
	g_gc->head = NULL;
	g_gc->tail = NULL;
	g_gc->node_used = 0;
	g_gc->malloc_call = 0;
	g_gc->free_call = 0;
	g_gc->data_size = sizeof(t_gclist);
}

t_gclist *get_gclist()
{
	return (g_gc);
}