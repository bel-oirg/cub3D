/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:04:00 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/26 11:05:48 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

char* ft_strcat(char* dst, const char* src)
{
	char* start;

	start = dst;
	while (*dst != '\0')
		dst++;
	while (*src != '\0')
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return start;
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)(c))
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

int ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

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