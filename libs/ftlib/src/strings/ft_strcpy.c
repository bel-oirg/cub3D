/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:04:06 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/04/27 12:04:07 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftlib.h"

char* ft_strcpy(char* dst, const char* src)
{
    char* start;
    
    start = dst;
    if (!dst || !src)
        return (NULL);
    while (*src != '\0')
    {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';    
    return start;
}

int ft_strlcpy(char *res, char *line, int len)
{
	int i;
	
	i = 0;
	if (!res || !line)
		return (0);
	while(line[i] && i < len)
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return (i);
}