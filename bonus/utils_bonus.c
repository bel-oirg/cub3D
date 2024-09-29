/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:12:59 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/29 09:50:36 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

int	valid_char(char c)
{
	if (c != 'D' && c != '1' && c != ' ' && c != '\n' && c != 'E' && c != 'S'
		&& c != 'W' && c != 'N' && c != '0')
		return (0);
	return (1);
}

char	*ft_memset(char *str, int c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	get_max(t_tmp *list)
{
	t_node	*current;
	int		max;

	max = 0;
	current = list->map_head;
	while (current)
	{
		if (current->x > max)
			max = current->x;
		current = current->next;
	}
	return (max);
}

int	tab_spaces(char *dst, char *line)
{
	int	i;

	i = 0;
	while (*line)
	{
		if (*line == '\t')
		{
			*dst++ = ' ';
			*dst++ = ' ';
			*dst++ = ' ';
			*dst++ = ' ';
			i += 3;
		}
		else
			*dst++ = *line;
		line++;
		i++;
	}
	*dst = '\0';
	return (i);
}
