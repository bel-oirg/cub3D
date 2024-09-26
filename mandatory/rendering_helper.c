/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:30:36 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/26 11:14:49 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0 || x >= S_W || y < 0 || y >= S_H)
		return ;
	mlx_put_pixel(mlx->img, x, y, color);
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

unsigned long	tohxa(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

double	offset_x(t_mlx *mlx, mlx_texture_t *texture)
{
	double	offset;

	if (mlx->ray->flag == 1)
		offset = (int)fmodf((mlx->ray->h_inter.x
					* (texture->width / TILE_SIZE)), texture->width);
	else
		offset = (int)fmodf((mlx->ray->v_inter.y
					* (texture->width / TILE_SIZE)), texture->width);
	return (offset);
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}
