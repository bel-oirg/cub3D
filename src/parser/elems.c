/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 00:54:32 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/07 11:23:41 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

// int ft_iispace(char c)
// {
// 	return ((c >= 9 && c <= 13) || c == 32);
// }

// int ft_isdigit(char c)
// {
// 	return (c >= '0' && c <= '9');
// }

int id_check(char *id)
{
    char *elems;
	int i;

	i = 0;
	elems = "NSWEFCOOEA";
	if (!id)
		exit(printf("6-Error\n"));
	while (i < 6)
	{
		if (id[0] == elems[i])
			break;
		i++;
	}
	if (i == 6)
		return (-1);
	if (i < 4 && (id[1] != elems[i + 6] || id[2] != '\0'))
		return (-1);
	if ((i == 4 || i == 5) && id[1] != '\0')
		return (-1);
	return (i);
}

int validate_conditions(int len, int commaCount, int *commaPos, long long int res)
{
	long long int save;

	save = 0;
	// printf("%lld\n",res);
	if (res < 0)
		exit(printf("7-Error\n"));
    if (len <= 0)
		return 0;
    if (commaCount != 2)
		return 0;
    if (!(commaPos[0] > 0 && commaPos[0] < 4 && commaPos[1] > commaPos[0] + 1 && commaPos[1] < 8))
		return 0;
	len = 0;
	while (len < 3)
	{
		save = res % 1000;
		if (save > 255)
			return 0;
		res /= 1000;
		len++;
	}
    return 1;
}

// void setbit(short int flag, int bit)
// {
		
// }

int validate_rgb(char *str)
{
	int i;
	int index;

	(1) && (i = 1 ,index = 0);
	while (str[i] && str[i] != ',')
	{
		if (((str[i] >= '0' && str[i] <= '9')))
			index++;
		i++;
	}
	if (index == i) 
		return (1);
	return (0);
}



int validate_rgb_form(char *str, long long int *res)
{
    int i;
	int commaCount;
	int commaPos[2];
	
	printf("%s\n",str);
	// printf("++++");
	(1) && (commaPos[0] = -1, commaPos[1] = -1, i = 0, commaCount = 0);
	if (!str)
		exit(printf("Error\n"));
    while (str[i] != '\0')
	{
        if (!((str[i] >= '0' && str[i] <= '9') || str[i] == ','))
			return 1;
        if (str[i] == ',')
		{
			if (validate_rgb(str + i))
				exit(printf("Error\n"));
            if (commaCount < 2) 
				commaPos[commaCount] = i;
            commaCount++;
        }
		if (str[i] >= '0' && str[i] <= '9')
			*res = *res * 10 + (str[i] - '0');
        i++;
    }
	*res = *res * validate_conditions(i, commaCount, commaPos,*res);
    return (*res);
}

int check_arg(char **args, int *rgb)
{
	int i;
	int j;

	i = 0;
	while (args[i] != NULL && i < 3)
	{
		j = 0;
		rgb[i] = 0;
		while (args[i][j])
		{
			if (!(args[i][j] >= '0' && args[i][j] <= '9'))
				return (0);
			rgb[i] = rgb[i] * 10 + (args[i][j] - '0');
			if (!(rgb[i] >= 0 && rgb[i] <= 255))
				return (0);
			j++;
		}
		i++;
	}
	if (i != 3 || args[3] != NULL)
		return (0);
	return (1);
}

int check_color(t_data *data, char *line, int id)
{
	char **rgb;
	int rgb2[3];
	
	(void )data;
	(void )id;
	rgb = ft_split2(line,',');
	if (!check_arg(rgb, rgb2))
		return (0);
	data->config->rgb[id][0] = rgb2[0];
	data->config->rgb[id][1] = rgb2[1];
	data->config->rgb[id][2] = rgb2[2];
	return (1);
}

int check_data(t_data *data, int id, char *line)
{
	if (id < 4)
	{
		if (!line)
			exit(printf("Error\n"));
		if (file_check(line,".xpm"))
			exit(printf("Error\n"));
		data->config->path[id] = line;
	}
	else
	{
		if (!line)
			exit(printf("Error\n"));
		if (!check_color(data,line,id - 4))
			(printf("Error\n"),exit(1));
	}
	return (0);
}