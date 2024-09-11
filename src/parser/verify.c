/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 00:54:29 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/03 02:24:25 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void check_first_last_line(char **map, int rows, int cols) {
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

void save_player_pos(t_data *data,int i, int j, char dir)
{
    data->map->player_pos.x = j;
    data->map->player_pos.y = i;
    data->map->player_dir = dir;
}

void verify_player(t_data *data,char **map, int rows, int cols)
{
    int i;
    int j;
    int player_count;
    char player;

    i = 0;
    player_count = 0;
    while (i < rows - 1)
    {
        j = 0;
        while (j < cols - 1)
        {
            player = map[i][j];
            if (player == 'N' || player == 'S' || player == 'W' || player == 'E')
            {
                player_count++;
                if (player_count > 1)
                {
                    printf("player duplicated\n");
                    exit(1);
                }
                else if (i == 0 || i == rows || j == 0 || j == cols || map[i][j-1] == ' ' || map[i - 1][j] == ' ' || map[i][j + 1] == ' ' || map[i + 1][j] == ' ')
                {
                    printf("player pos not valid\n");
                    exit(1);
                }
                save_player_pos(data,i,j,map[i][j]);
            }
            j++;
        }
        i++;
    }
    if (player_count == 0)
    {
        printf("No player position found\n");
        exit(1);
    }
}

void check_map(t_data *data,char **map, int rows, int cols)
{
    check_first_last_line(map, rows, cols);
    verify_zeros(map, rows, cols);
    verify_player(data,map, rows, cols);
}
