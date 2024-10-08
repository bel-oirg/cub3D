/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:04:09 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/29 09:47:17 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

size_t	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(char *str)
{
	int		len;
	int		i;
	char	*new;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new = (char *)my_malloc(sizeof(char) * len + 1, 1);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	newlen;
	char	*new;

	newlen = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)my_malloc(sizeof(char) * (newlen + 1), 1);
	if (!new)
		return (NULL);
	if (s1 != NULL)
		ft_strcpy(new, s1);
	else
		new[0] = '\0';
	ft_strcat(new, s2);
	return (new);
}
