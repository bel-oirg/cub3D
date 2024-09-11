/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 07:57:08 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/11 10:38:20 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "libs/mlx/include/MLX42/MLX42.h"

#define WIDTH 960
#define HEIGHT 960
#define M_WIDTH 24
#define M_HEIGHT 24

static mlx_image_t* image;
static mlx_image_t* image2;

int TILL = WIDTH / M_WIDTH;
int worldMap[M_WIDTH][M_HEIGHT] =
{   {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
    {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
    {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
    {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
    {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
    {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
    {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
    {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
    {4,1,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
    {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
    {4,1,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
    {6,0,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
    {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {6,0,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
    {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
    {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
    {4,1,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
    {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
    {4,1,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
    {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
    {4,1,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
    {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
    {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3} };

void ft_hook(void* param)
{
	mlx_t* mlx = param;
    int X;
    int Y;

    X = image2->instances[0].x;
    Y = image2->instances[0].y;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
    int speed = TILL/4;
    
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
    {
        int YY = floor((Y-speed)/(float)TILL);
        if (!worldMap[YY][X/TILL] && !worldMap[YY+1][X/TILL])
		    image2->instances[0].y -= speed;
    }

	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
    {
        int YY = floor((Y+speed)/(float)TILL);

        if (!worldMap[YY][X/TILL] && !worldMap[YY+1][X/TILL])
		    image2->instances[0].y += speed;


    }
	
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
    {
        int XX = floor((X-speed)/(float)TILL);

        if (!worldMap[Y/TILL][XX] && !worldMap[Y/TILL][XX+1])
		    image2->instances[0].x -= speed;
    }
	
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
    {
        int XX = floor((X+speed)/(float)TILL);

        if (!worldMap[Y/TILL][XX] && !worldMap[Y/TILL][XX+1])
		    image2->instances[0].x += speed;
    }
}

void map(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
            if (worldMap[y/TILL][i/TILL])
            {
			    uint32_t color = 0x0F000FF;
			    mlx_put_pixel(image, i, y, color);
            }
		}
	}
}

void player(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image2->width; ++i)
	{
		for (uint32_t y = 0; y < image2->height; ++y)
		{
            uint32_t color = 0x0FFFFFF;
            mlx_put_pixel(image2, i, y, color);
		}
	}
}

int main()
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    if (!(image2 = mlx_new_image(mlx, TILL, TILL)))
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
    if (mlx_image_to_window(mlx, image2, 4*TILL, 2*TILL) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, map, mlx);
	mlx_loop_hook(mlx, player, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}