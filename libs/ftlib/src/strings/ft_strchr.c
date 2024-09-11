/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:04:03 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/04/27 12:04:04 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftlib.h"

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