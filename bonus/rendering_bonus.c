/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:19:04 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/29 09:49:38 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int				i;
	unsigned long	f;
	unsigned long	c;

	i = b_pix;
	c = tohxa(mlx->dt->rgb[0][0], mlx->dt->rgb[0][1], mlx->dt->rgb[0][2]);
	f = tohxa(mlx->dt->rgb[1][0], mlx->dt->rgb[1][1], mlx->dt->rgb[1][2]);
	while (i < S_H)
		my_mlx_pixel_put(mlx, ray, i++, c);
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, f);
}

mlx_texture_t	*get_texture_dir(t_mlx *mlx, int flag, int wall_ty)
{
	if (wall_ty == 2)
		return (mlx->dt->txtr->door);
	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl);
	if (flag == 0)
	{
		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
			return (mlx->dt->txtr->we);
		else
			return (mlx->dt->txtr->ea);
	}
	else
	{
		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
			return (mlx->dt->txtr->so);
		else
			return (mlx->dt->txtr->no);
	}
}

void	draw_wall(t_mlx *mlx, int ray, t_dvector pix, double wall_h)
{
	t_dvector		offset;
	mlx_texture_t	*texture;
	uint32_t		*pixles;
	double			factor;
	int				pixel;

	texture = get_texture_dir(mlx, mlx->ray->flag, mlx->wall_ty);
	pixles = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	offset.x = offset_x(mlx, texture);
	offset.y = (pix.y - (S_H / 2) + (wall_h / 2)) * factor;
	if (offset.y < 0)
		offset.y = 0;
	while (pix.y < pix.x)
	{
		pixel = ((int)offset.y * texture->width) + (int)offset.x;
		if (pixel < (int)(texture->width * texture->height) && pixel > 0)
			my_mlx_pixel_put(mlx, ray, pix.y, reverse_bytes(pixles[pixel]));
		offset.y += factor;
		pix.y++;
	}
}

void	render_wall(t_mlx *mlx, int ray)
{
	double		wall_h;
	t_dvector	pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle));
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2)
			/ tan(mlx->ply->fov_rd / 2));
	pix.x = (S_H / 2) + (wall_h / 2);
	pix.y = (S_H / 2) - (wall_h / 2);
	if (pix.x > S_H)
		pix.x = S_H;
	if (pix.y < 0)
		pix.y = 0;
	draw_wall(mlx, ray, pix, wall_h);
	draw_floor_ceiling(mlx, ray, pix.y, pix.x);
}
