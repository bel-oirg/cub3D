#include "cub.h"

void	game_loop(void *ml)	// game loop
{
	t_mlx	*mlx;

	mlx = ml;	// cast to the mlx structure
	mlx_delete_image(mlx->mlx_p, mlx->img);	// delete the image
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);	// create new image
	hook(mlx, 0, 0); // hook the player
	cast_rays(mlx);	// cast the rays
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0); // put the image to the window
}

void init_the_player(t_mlx mlx)	// init the player structure
{
	mlx.ply->plyr_x = mlx.dt->p_x * TILE_SIZE + TILE_SIZE / 2; // player x position in pixels in the center of the tile
	mlx.ply->plyr_y = mlx.dt->p_y * TILE_SIZE + TILE_SIZE / 2; // player y position in pixels in the center of the tile
	mlx.ply->fov_rd = (FOV * M_PI) / 180; // field of view in radians
	mlx.ply->angle = M_PI; // player angle
	//the rest of the variables are initialized to zero by calloc
}

void	start_the_game(t_data *dt)	// start the game
{
	t_mlx	mlx;

	mlx.dt = dt;	// init the mlx structure
	mlx.ply = calloc(1, sizeof(t_player));	// init the player structure i'm using calloc to initialize the variables to zero
	mlx.ray = calloc(1, sizeof(t_ray));	// init the ray structure
	mlx.mlx_p = mlx_init(S_W, S_H, "Cub3D", 0);	// init the mlx pointer
	init_the_player(mlx);	// init the player structure
	mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx);	// game loop
	mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);	// key press and release
	mlx_loop(mlx.mlx_p);	// mlx loop
}

t_data *init_argumet()	// init the data structure
{
	t_data *dt = calloc(1, sizeof(t_data)); // init the data structure
	dt->map2d = calloc(10, sizeof(char *)); // init the map
	dt->map2d[0] = strdup("1111111111111111111111111"); //fill the map
	dt->map2d[1] = strdup("1000000000000000000100001");
	dt->map2d[2] = strdup("1001000000000P00000000001");
	dt->map2d[3] = strdup("1001000000000000001000001");
	dt->map2d[4] = strdup("1001000000000000001000001");
	dt->map2d[5] = strdup("1001000000100000001000001");
	dt->map2d[6] = strdup("1001000000000000001000001");
	dt->map2d[7] = strdup("1001000000001000001000001");
	dt->map2d[8] = strdup("1111111111111111111111111");
	dt->map2d[9] = NULL;
	dt->p_y = 3; // player y position in the map
	dt->p_x = 14; // player x position in the map
	dt->w_map = 25; // map width
	dt->h_map = 9; // map height
	return (dt); // return the data structure
}

void	ft_exit(t_mlx *mlx) 		// exit the game
{
	int	i = 0;
	while (mlx->dt->map2d[i])
		free(mlx->dt->map2d[i++]); // free the map line by line
	free(mlx->dt->map2d); // free the map
	free(mlx->dt); // free the data structure
	free(mlx->ply); // free the player structure
	free(mlx->ray); // free the ray structure
	mlx_delete_image(mlx->mlx_p, mlx->img); // delete the image
	mlx_close_window(mlx->mlx_p); // close the window
	mlx_terminate(mlx->mlx_p); // terminate the mlx pointer
	printf("Game closed\n"); // print the message
	exit(0); // exit the game
}

int main()	// main function
{
	t_data	*data;

	data = init_argumet();	// init the data structure
	start_the_game(data);	// start the game
	return 0;
}