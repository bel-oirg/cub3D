/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:40:05 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/20 22:12:26 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"


// void get_flag(char *extention, int *flag)
// {
//     if (ft_strcmp(extention,".png") == 0)
//         *flag = 0;
//     else if (ft_strcmp(extention,".xpm") == 0)
//         *flag = 1;
//     else
//         *flag = -1;
// }
/*
    this function will check if the file has the right extention
    and return true if it does, false otherwise. 
    Rules for the file name:
    1. The file must have the extention .cub
    2. The file must be at least 5 characters long
    3. The file must not be hidden (start with a dot)
    Note: the minimum length of the file name is 5 characters
    cas of name is without path : o.cub
	hidden can be one . or more so .cub ..cub ...cub
	hidden can be "/.cub" "" 
*/
int file_check(char *file, char *ext)
{
    int len;
    int i;
    char *file_name;
	char read_check[10];
	
    len = ft_strlen(file);
	i = open(file, O_RDONLY);
    if (i == -1 || len < 5)
        return (1);
	if (read(i, read_check, 10) <= 0)
		return (1);
    close(i);
    i = 0;
    while(i < len)
    {
        if (file[i] == '/')
            file_name = file + i + 1;
        i++;
    }
    if (file_name[0] == '.')
        return (1);
	len -= 4;
    if (ft_strcmp(file + len,ext) != 0)
        return (1);
    // get_flag(file + len,flag)
    return (0);
}

int read_file(t_tmp *tmp, int fd)
{
    char *line;
    
    line = read_elements(tmp, fd);
    while (line != NULL && line[0] != '\n')
    {
		add_node(tmp,line);
        tmp->y++;
        line = gln(fd);
        if (!tmp->map_tail->line && line)
            return (free(line),1);
    }
    while (line != NULL && line[0] == '\n')
    {
        free(line);
        line = gln(fd);
    }
    if (line != NULL)
        return(free(line), 1);
    return (0);
}

int elem_validation(t_data *data, t_tmp *tmp)
{
	int i;
	int id;
	char *check_list;

	i = 0;
	id = -1;
	check_list = ft_strdup("NSWEFCOOEA");
	while (i < 6 && tmp->elems[i] != NULL)
	{
		id = id_check(tmp->elems[i][0]);
		if (id < 0 || id > 5)
			return (1);
		if (tmp->elems[i][0][0] != check_list[id])
			return (1);
		if (check_data(data,id,tmp->elems[i][1]))
			return (1);
		if (tmp->elems[i][2] != NULL)
			return (1);
		check_list[id] = '-';
		i++;
	}
	return (0);
}

void print_2d_char_array(char **array)
{

    if (array == NULL) {
        printf("Array is NULL\n");
        return;
    }
    for (int i = 0; array[i] != NULL; i++)
    {
        for (int j = 0; array[i][j] != '\0'; j++)
            printf("%c", array[i][j]);
        printf("\n");
    }
}

int get_max(t_tmp *list)
{
    t_node *current;
    int max;

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

char *ft_memset(char *str, int c, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        str[i] = c;
        i++;
    }
    str[i] = '\0';
    return (str);
}

void create_2d_map(t_data *data, t_tmp *list)
{
    int x; 

    x = get_max(list);
    data->w_map = x;
    data->h_map = list->y;
    data->map2d = malloc(sizeof(char *) * (list->y + 1));
    if (!data->map2d)
        return;
    while(list->y >= 0)
    {
        data->map2d[list->y] = malloc(sizeof(char) * (x + 1));
        ft_memset(data->map2d[list->y],' ',x);
        if (!data->map2d[list->y])
            return;
        list->y--;
    }
    data->map2d[data->h_map] = NULL;
    list->y = data->h_map;
}


int cpy_map(t_data *data, t_tmp *list)
{
    t_node *current;
    char *line;
    int i;
    int j;

    i = 0; 
    current = list->map_head;
    while (current)
    {
		j = 0;
        line = current->line;
        while (*line)
        {
            if (*line != '0' && *line != '1' && *line != ' ' &&
            *line != '\n' && *line != '\t' && *line != 'E' &&
            *line != 'S' && *line != 'W' && *line != 'N')
                    return(1);
            if (*line == '\t')
                j = j + 3;
            else
                data->map2d[i][j] = *line;
            j++;
            line++;
        }
        i++;
        current = current->next;
    }
    return (0);
}


/* 
    this function will check if the file is valid
    1. check if the file has the right extention
    2. check if the file is readable
    3. check if the file is not empty(skip it)
*/
int parse(t_tmp *tmp,t_data *data, char *file)
{
	int fd;

	if (file_check(file,".cub"))
		return (1);
	fd = open(file,O_RDONLY);
	if (fd < 0)
		return (1);
    if (read_file(tmp, fd))
        return (close(fd),1);
	if (elem_validation(data, tmp))
    {
        printf("Error\n");
        return (close(fd),free_list(tmp),1);
    }
    create_2d_map(data,tmp);
	if (cpy_map(data,tmp))
        return (1);
    // print_2d_char_array(data->map2d);
    check_map(data,data->map2d,data->h_map,data->w_map);
    free_list(tmp);
    return (close(fd),0);
}