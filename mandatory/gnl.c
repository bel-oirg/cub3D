/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:26:45 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/26 11:08:01 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static void	buffer_copy(char *res, char *storage, int j, int *i)
{
	int	h;

	h = j + 1;
	*i = 0;
	while (*i <= j || h < BUFFER_SIZE)
	{
		if (*i <= j)
		{
			res[*i] = storage[*i];
			storage[*i] = '\0';
		}
		if (h < BUFFER_SIZE)
		{
			if (storage[h] == '\0')
				h = BUFFER_SIZE;
			else
			{
				storage[*i] = storage[h];
				storage[h] = '\0';
			}
			h++;
		}
		(*i)++;
	}
	res[j + 1] = '\0';
}

static int	rsfast(char *storage, char **line, int j, int state)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	if (line[0])
	{
		while (line[0][i])
			i++;
		res = (char *)my_malloc(sizeof(char) * (j + i + 2),1);
		if (!res)
			return (-1);
		i = -1;
		while (line[0][++i])
			res[i] = line[0][i];
	}
	else
		res = (char *)my_malloc(sizeof(char) * (j + 2),1);
	if (!res)
		return (-1);
	buffer_copy(res + i, storage, j, &i);
	line[0] = res;
	return (state);
}

static int	check_state(int fd, char *storage, char **line, int state)
{
	int	i;

	if (state == 1 || state == 4)
	{
		i = read(fd, storage, BUFFER_SIZE);
		if (i == 0)
			return (state - 1);
		if (i == -1)
			return (-1);
		return (2);
	}
	i = 0;
	if (state == 2)
	{
		while (i < BUFFER_SIZE && storage[i] != '\0')
		{
			if (storage[i] == '\n')
				return (rsfast(storage, line, i, 3));
			i++;
		}
		if (i > 0)
			return (rsfast(storage, line, i - 1, 4));
	}
	return (-1);
}

char	*gnl(int fd)
{
	static char	storage[BUFFER_SIZE];
	char		*line;
	int			state;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	state = 1;
	if (storage[0] != '\0')
		state = 2;
	line = NULL;
	while (state > 0)
	{
		if (!line && storage[0] == '\0' && state == 1)
			state = check_state(fd, storage, &line, state);
		else if (state == 2)
			state = check_state(fd, storage, &line, state);
		else if (line && state == 3)
			return (line);
		else if (state == 4)
			state = check_state(fd, storage, &line, state);
		else if (state == -1)
			return (NULL);
	}
	return (line);
}