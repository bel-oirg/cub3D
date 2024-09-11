/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:04:09 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/05/04 00:34:10 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftlib.h"

char *ft_strdup(char *str)
{
    int len;
    int i;
    char *new;

    i = 0;
    if (!str)
        return (NULL);
    len = ft_strlen(str);
    new = (char *)gc_malloc(sizeof(char) * len + 1);
    while(str[i])
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

// char *ft_cstrdup(char *str, int len, int is_line)
// {
//     int len;
//     int i;
//     int j;
//     char *new;

//     i = 0;
//     j = 0;
//     if (!str)
//         return (NULL);
//     new = (char *)gc_malloc(sizeof(char) * len + 2);
//     while(i <= len)
//     {
//         new[i] = str[i];
//         str[i] = '\0';
//         i++;
//     }
//     new[i] = '\0';
//     while (i < BUFFER_SIZE && is_line)
//     {
//         str[j++] = str[i];
//         str[i++] = '\0';
//     }
//     return (new);
// }