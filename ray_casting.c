/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:03:44 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/11 06:27:36 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub.h"

void ray_casting(t_data raw)
{
	double	h_inter;
	int		beta;
	int		ray;

	ray = -1;
	beta = 90 - (FOV / 2);
	//TODO change the beta with the parsed angle

	while (++ray < WIDTH)
	{

		beta += FOV / WIDTH; 
		//TODO is rad or angle
	}
}

void direct_h(int alpha, double *y_step, int *y)
{
	if (alpha > 0 && alpha <= M_PI)
	{
		*y += SQUARE;
		return ;
	}
	*y_step *= -1;
}

int	hit_wall(t_data raw, int x, int y)
{
	if (x >= WIDTH || y >= HEIGHT)
		return (1);
	if (raw.map->map && raw.map->map[y][x] == 1)
		return (1);
	return (0);
}

double	intersected(t_data *raw, int alpha)
{
	double	x_step;
	double	y_step;
	double	dist;
	int		x;
	int		y;

	y_step = SQUARE;
	x_step = y_step / tan(alpha);
	y = floor((float)raw->map->player_pos.y / SQUARE) * SQUARE;
	direct_h(alpha, &y_step, &y);
	x = raw->map->player_pos.x + (y - raw->map->player_pos.y) / tan(alpha);
	while(!hit_wall(*raw, x, y))
	{
		x += x_step;
		y += y_step;
	}
	return(sqrt(pow(x, 2) + pow(y, 2)));
}

/*
1- find the angle for the first ray
angle = pos - FOV/2
begin by the full left and cast all throught the right

2- loop for each ray
expand the FOV to fill the WIDTH
angle += FOV / WIDTH

3- get the Horizotal intersection
we plan to draw a line from the play --> position of the direction

--> check the position of the player
--> we should find the first intersection (horizontaly)
	dy = (floor(py) / TILL) * TILL
	dx = px + X

	tan(alpha) = Y / X
	X = Y / tan(alpha)
	Y = py - y_inter

	--> X = (y_inter - py) / tan(alpha)
	------------------------------------
	dx = px + (y_inter - py) / tan(alpha)
	dy = (floor(py) / TILL) * TILL
	------------------------------------
(consider how the player is facing)

when we check for the wall hit, we will convert the pixel coords
to map coords which will cause a loss of float val
-> to ensure we re inside a map grid we will add one pixel

if we hit a wall we will calc the distance from the player -> wall
VITAGHORSS

hit_dist = sqrt(dx^2 + dy^2)
*/