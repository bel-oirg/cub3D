/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:19:04 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/21 21:59:48 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0 || x >= S_W || y < 0 || y >= S_H)
		return ;
	mlx_put_pixel(mlx->img, x, y, color);
}

float	nor_angle(float angle)	// normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI); //TODO CHANGE THIS IN CASE WE HAVE 78PI
	return (angle);
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
{
	int		i;
	// int		c;

	i = b_pix;
	while (i < S_H)
		my_mlx_pixel_put(mlx, ray, i++, FLOOR_COL); 
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, CEIL_COL);
}


mlx_texture_t	*get_texture_dir(t_mlx *mlx, int flag)	
{
	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl);
	if (flag == 0)
	{
		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
			return (mlx->dt->txtr->EA);
			// return (WEST_COL);
		else
			return (mlx->dt->txtr->WE);
			// return (EAST_COL); 
	}
	else
	{
		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
			return (mlx->dt->txtr->SO);
			// return (SOUTH_COL);
		else
			return (mlx->dt->txtr->NO);
			// return (NORTH_COL);
	}
}


/*
void	draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int color;

	color = get_color(mlx, mlx->ray->flag);
	while (t_pix < b_pix)
		my_mlx_pixel_put(mlx, ray, t_pix++, color);
}
*/


/*
	this function will be used to get
	the offset of a texture mapping
	
	flag: 1 is horizontal
	flag: 0 is virtucal
*/
double offset_x(t_mlx *mlx ,mlx_texture_t *texture)
{
	double	offset;

	if (mlx->ray->flag == 1)
		offset = (int)fmodf((mlx->ray->h_inter.x * (texture->width / TILE_SIZE)),texture->width);
	else
		offset = (int)fmodf((mlx->ray->v_inter.y * (texture->width / TILE_SIZE)),texture->width);
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

void draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix, double wall_h)
{
	t_dvector offset;
	mlx_texture_t *texture;
	uint32_t *pixles;
	double factor;
	int pixel;

	texture = get_texture_dir(mlx, mlx->ray->flag);
	pixles = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	offset.x = offset_x(mlx,texture);
	offset.y = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
	if (offset.y < 0)
		offset.y = 0;
	while (t_pix < b_pix)
	{
		pixel = ((int)offset.y * texture->width) + (int)offset.x;
		if (pixel < (int)(texture->width * texture->height) && pixel > 0)
			my_mlx_pixel_put(mlx,ray,t_pix,reverse_bytes(pixles[pixel]));
		offset.y += factor;
		t_pix++;
	}
}

void	render_wall(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle)); // fix the fisheye
    /*
        cos(beta) = CorDis/Longdis ---> CorDis = Cos(beta) * Longdis
        https://permadi.com/1996/05/ray-casting-tutorial-8/
    */
    
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->ply->fov_rd / 2)); // THALES
    /*
                                Actual Slice Height
    Projected Slice Height= --------------------- * Distance to Projection Plane
                            Distance to the Slice
                            
    https://www.permadi.com/tutorial/raycast/rayc9.html
    */
	b_pix = (S_H / 2) + (wall_h / 2);
	t_pix = (S_H / 2) - (wall_h / 2);
	if (b_pix > S_H) //floor
		b_pix = S_H;
	if (t_pix < 0) //ceiling
		t_pix = 0;
	// draw_wall(mlx, ray, t_pix, b_pix); // draw the wall (this is your old one)
	draw_wall(mlx, ray, t_pix, b_pix, wall_h); // i add wall_h because i need in textures 
	draw_floor_ceiling(mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
}