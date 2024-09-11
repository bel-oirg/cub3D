/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:43:09 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/05/12 00:22:38 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftlib.h"

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