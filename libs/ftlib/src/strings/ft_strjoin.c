/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:04:12 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/05/02 19:45:28 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftlib.h"

char *ft_strjoin(char *s1, char *s2) 
{
    size_t newlen;
    char *new;

    newlen = ft_strlen(s1) + ft_strlen(s2);
    new = (char *)gc_malloc(sizeof(char) * (newlen + 1));
    if (!new)
        return NULL;
    if (s1 != NULL) 
    {
        ft_strcpy(new, s1);
        gc_free(s1);
    }
    else
        new[0] = '\0';
    ft_strcat(new, s2);
    return new;
}