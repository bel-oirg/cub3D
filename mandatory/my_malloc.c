/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:37:28 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/29 04:46:43 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	dataclear(t_gdata **hold)
{
	t_gdata	*tmp;
	t_gdata	*ptr;

	if (!hold || !*hold)
		return ;
	tmp = *hold;
	while (tmp)
	{
		ptr = tmp;
		tmp = tmp->next;
		free(ptr->data);
		free(ptr);
	}
	*hold = NULL;
}

void	*my_malloc(size_t size, int mode)
{
	static t_gdata	*head;
	t_gdata			*node;
	void			*data;

	if (mode == 1)
	{
		data = malloc(size);
		if (!data)
			return (dataclear(&head), exit(1), NULL);
		node = malloc(sizeof(t_data));
		if (!node)
			return (dataclear(&head), exit(1), NULL);
		node->data = data;
		node->next = NULL;
		(head) && (node->next = head);
		head = node;
		return (data);
	}
	if (!mode)
	{
		printf("Error\n");
		return (dataclear(&head), exit(1), NULL);
	}
	return (dataclear(&head), exit(0), NULL);
}
