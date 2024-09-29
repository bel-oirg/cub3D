/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:23:33 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/29 09:46:55 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

static size_t	word_count(const char *s, char c)
{
	size_t	i;
	int		flag;
	size_t	count;

	i = 0;
	count = 0;
	flag = 0;
	if (s == 0)
		return (0);
	while (s[i] && s[i] == c)
		(1) && (i++, flag++);
	while (s[i])
	{
		count++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
		{
			flag++;
			i++;
		}
	}
	if (flag != 2)
		return (0);
	return (count);
}

static char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*dst;

	i = 0;
	if (n == 0)
		return (NULL);
	dst = (char *)my_malloc(sizeof(char) * (n + 1), 1);
	if (!dst)
		return (NULL);
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	**free_alloc(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	**ft_split2(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;
	size_t	save;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	str = (char **)my_malloc(sizeof(char *) * (word_count(s, c) + 1), 1);
	if (!str)
		return (NULL);
	while (i < word_count(s, c) && s[j])
	{
		while (s[j] == c)
			j++;
		save = j;
		while (s[j] != c && s[j])
			j++;
		str[i] = ft_strndup(&s[save], j - save);
		if (str[i++] == 0)
			return (free_alloc(str));
	}
	str[i] = NULL;
	return (str);
}
