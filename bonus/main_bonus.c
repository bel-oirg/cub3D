/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:25:47 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/29 09:51:41 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

int	main(int ac, char **av)
{
	t_mlx	*mlx;

	if (ac != 2)
		return (printf("Error\n"), 1);
	mlx = create_mlx_struct();
	parse(mlx, av[1]);
	start_the_game(mlx);
	return (0);
}
