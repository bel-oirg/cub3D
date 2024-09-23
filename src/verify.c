/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 00:54:29 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/18 12:33:01 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void check_first_last_line(char **map, int rows, int cols)
{
    int i;

    i = 0;
    while (i < cols) {
        if (map[0][i] != ' ' && map[0][i] != '1') {
            printf("Error in first line\n");
            exit(1);
        }
        if (map[rows-1][i] != ' ' && map[rows-1][i] != '1') {
            printf("Error in last line\n");
            exit(1);
        }
        i++;
    }
}

void verify_zeros(char **map, int rows, int cols) {
    int i;
    int j;

    i = 1;
    while (i < rows - 1) {
        j = 0;
        while (j < cols - 1) {
            if (map[i][j] == '0') {
                if (j == 0 || map[i-1][j] == ' ' || map[i+1][j] == ' ' || map[i][j-1] == ' ' || map[i][j+1] == ' ') {
                    printf("Error at position (%d, %d)\n", i, j);
					map[i][j] = 'X';
					print_2d_char_array(map);
                    exit(1);
                }
            }
            j++;
        }
        i++;
    }
}

void save_player_pos(t_data *data,int i, int j,int *player_count)
{
    data->p_x = j;
    data->p_y = i;
    if (*player_count > 1)
    {
        printf("player duplicated\n");
        exit(1);
    }
}

int err(char *str)
{
    while(*str)
        write(2,str++,1);
    return (1);
}


int verify_player(t_data *data,char **map, int rows, int cols)
{
    int i;
    int j;
    int player_count;

    i = 0;
    player_count = 0;
    while (i < rows - 1)
    {
        j = 0;
        while (j < cols - 1)
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
            {
                player_count++;
                if (player_count > 1 || i == 0 || i == rows || j == 0 || j == cols || 
                map[i][j-1] == ' ' || map[i - 1][j] == ' ' || map[i][j + 1] == ' ' || map[i + 1][j] == ' ')
                    exit(err("Error\n"));
                save_player_pos(data,i,j,&player_count);
            }
            j++;
        }
        i++;
    }
    return (player_count);        
}

void check_map(t_data *data,char **map, int rows, int cols)
{
    check_first_last_line(map, rows, cols);
    verify_zeros(map, rows, cols);
    if (!verify_player(data,map, rows, cols))
        exit(err("Error\n"));
}
