/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 00:54:24 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/26 11:05:34 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

int line_len(char *line)
{
	int i;
	int j;
	int k;

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



char *read_map(char *line, int *x)
{
	int i;
	char *dst;

	i = line_len(line);
	if (i == 0)
		return (NULL);
	dst = my_malloc(sizeof(char) * i + 1,1);
	if (!dst)
		return (NULL);
	i = tab_spaces(dst,line);
	*x = i;
	return (dst);
}


char *read_elements(t_tmp *list, int fd) 
{
	char *line;
	int elements;
	
	line = gnl(fd);
	elements = 0;
	while (line != NULL && elements < 6)
	{
		if (line[0] != '\n')
		{
			list->elems[elements] = ft_split(line);
			elements++;
		}
		line = gnl(fd);
	}
	while (line != NULL && line[0] == '\n')
		line = gnl(fd);
	return line;
}


void file_check(t_mlx *mlx, char *file, char *ext)
{
	int len;
	int i;
	char *file_name;
	char read_check[10];
	
	len = ft_strlen(file);
	i = open(file, O_RDONLY);
	if (i == -1 || len < 5)
		exit(before_exit(mlx,1));
	if (read(i, read_check, 10) <= 0)
		exit(before_exit(mlx,1));
	close(i);
	i = 0;
	while(i < len)
	{
		if (file[i] == '/')
			file_name = file + i + 1;
		i++;
	}
	if (file_name[0] == '.')
		exit(before_exit(mlx,1));
	len -= 4;
	if (ft_strcmp(file + len,ext) != 0)
		exit(before_exit(mlx,1));
}

void read_file(t_mlx *mlx, int fd)
{
	char *line;

	line = read_elements(mlx->tmp,fd);
	while (line != NULL && line[0] != '\n')
	{
		add_node(mlx->tmp,line);
		mlx->tmp->y++;
		line = gnl(fd);
		if (!mlx->tmp->map_tail->line && line)
			exit(before_exit(mlx,1));
	}
	while (line != NULL && line[0] == '\n')
		line = gnl(fd);
	if (line != NULL)
		exit(before_exit(mlx,1));
}

