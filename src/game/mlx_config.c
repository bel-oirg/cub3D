/* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   mlx_config.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/09/03 01:35:14 by aelmrabe          #+#    #+#             */
// /*   Updated: 2024/09/03 01:52:35 by aelmrabe         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../inc/cub.h"


int32_t mlx_screen(t_data *data)
{
	mlx_t* mlx;
    mlx_image_t *image;

    mlx = data->mlx;
	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}