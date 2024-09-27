/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:25:47 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/27 02:26:15 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

void f(void)
{
	system("leaks cub3d");
}

int main(int ac, char **av)
{
	t_mlx *mlx;

	mlx = create_mlx_struct();
	if (ac != 2)
		return (1);
	parse(mlx,av[1]);
	start_the_game(mlx);
	// atexit(f);
	return (0);
}