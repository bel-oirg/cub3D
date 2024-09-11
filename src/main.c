/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:25:47 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/07 11:46:25 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

// void f(void)
// {
// 	system("leaks cub3d");
// }

int main(int ac, char **av)
{
	t_data *data;
	data = create_data();
	if (ac != 2)
		return (1);
	if (parse(data,av[1]))
		exit(printf("Main-Error\n"));
	mlx_screen(data);
	// atexit(f);
	
	return (0);
}