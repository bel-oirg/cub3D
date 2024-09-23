/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 00:54:24 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/20 01:29:43 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int line_len(char *line)
{
    int i; // index and return value
    int j; // cas of char 
    int k; // cas of spaces

    i = 0;
    j = -1;
    k = 0;
    while (line[i] && line[i] != '\n')
    {
        if(line[i] != ' ' && line[i] != '\t')
            j = i;
        else if (line[i] == ' ' || line[i] == '\t')
            k++;
        i++;
    }
    if (j == -1)
        return(0);
    k = k - (i - j -1);
    i = (j - k) + (k * 4) + 1;
    line[j + 1] = '\0';
    return (i);
}

int tab_spaces(char *dst, char *line)
{
    int i;

    i = 0;
    while (*line)
    {
        if (*line == '\t')
        {
            *dst++ = ' ';
            *dst++ = ' ';
            *dst++ = ' ';
            *dst++ = ' ';
            i +=3;
        }
        else
            *dst++ = *line;
        line++;
        i++;
    }
    *dst = '\0';
    return (i);
}

char *read_map(char *line, int *x)
{
    int i;
    char *dst;

    i = line_len(line);
    if (i == 0)
        return (NULL);
    dst = malloc(sizeof(char) * i + 1);
    if (!dst)
        return (NULL);
    i = tab_spaces(dst,line);
    *x = i;
    return (dst);
}


int get_len(char *line)
{
    int i;
    int spaces;
    int len;

    i = 0;
    spaces = 0;
    len = 0;
    while (line[i] && line[i] != '\n')
    {
        if (line[i] == ' ' || line[i] == '\t')
        {
            if (line[i] == '\t')
                spaces += 3;
            spaces++;
        }
        else
        {
            len = len + spaces;
            spaces = 0;
            len++;
        }
        i++;
    }
    return (len);
}

int set_len(t_tmp *list)
{
    t_node *current;

    current = list->map_head;
    while (current)
    {
        current->x = get_len(current->line);
        if (current->x == 0)
            return (1);
        if (current->x > list->max_x)
            list->max_x = current->x;
        current = current->next;
    }
    return (0);
}

void free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

char **create_2d(int x, int y)
{
    char **tab;
    int i;
    int j;

    i = 0;
    j = 0;
    tab = malloc(sizeof(char *) * (y + 1));
    while (i < y)
    {
        tab[i] = malloc(sizeof(char) * (x + 1));
        if (!tab[i])
            return (free_tab(tab),NULL);
        while (j < x)
        {
            tab[i][j] = ' ';
            j++;
        }
        tab[i][j] = '\0';
        i++;
    }
    tab[i] = NULL;
    return (tab);
}

char **cpy_2d(t_tmp *list, char **tab)
{
    t_node *current;
    int i;

    i = 0;
    current = list->map_head;
    while (current)
    {
        while(*current->line && i < current->x)
        {
            *tab[i] = *current->line;
            tab[i]++;
            current->line++;
        }
    }
    return (tab);
}

char *read_elements(t_tmp *list, int fd) 
{
    char *line;
    int elements;
    
    line = gln(fd);
    elements = 0;
    while (line != NULL && elements < 6)
    {
        if (line[0] != '\n')
        {
			list->elems[elements] = ft_split(line);
            elements++;
        }
        free(line);
        line = gln(fd);
    }
    while (line != NULL && line[0] == '\n')
    {
        free(line);
        line = gln(fd);
    }
    return line;
}