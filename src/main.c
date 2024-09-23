/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:25:47 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/20 21:06:51 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

// void f(void)
// {
// 	system("leaks cub3d");
// }

int main(int ac, char **av)
{
	t_mlx *mlx;

	mlx = create_mlx_struct();
	if (ac != 2)
		return (1);
	if (parse(mlx->tmp,mlx->dt,av[1]))
		return (before_exit(mlx,1), 1);
	start_the_game(mlx);
	// mlx_screen(data);
	// atexit(f);
	return (0);
}