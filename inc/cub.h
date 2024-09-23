#ifndef CUB_H
#define CUB_H

#include "MLX42.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFFER_SIZE 10000
# define SP_FRAMES 75
# define S_W 1400 // screen width
# define S_H 900 // screen height
# define TILE_SIZE 30 // tile size
# define FOV 60 // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 4	// player speed
# define FLOOR_COL 0x99AAFF99
# define CEIL_COL 0xFF111111
# define WEST_COL 0xFFFFF222
# define EAST_COL 0xFF333333
# define SOUTH_COL 0xF4123123
# define NORTH_COL 0xFF555555

typedef struct s_ivector{
	int x;
	int y;
}t_ivector;

typedef struct s_dvector{
	double x;
	double y;
}t_dvector;

typedef struct s_texture
{
	mlx_texture_t *NO;
	mlx_texture_t *SO;
	mlx_texture_t *WE;
	mlx_texture_t *EA;
}t_texture;

typedef struct s_player //the player structure
{
	int		plyr_x; // player x position in pixels
	int		plyr_y; // player y position in pixels
	double	angle;	// player angle
	float	fov_rd;	// field of view in radians
	int		rot;	// rotation flag
	int		l_r;	// left right flag
	int		u_d;	// up down flag
}	t_player;

typedef struct s_ray	//the ray structure
{
	double	ray_ngl;	// ray angle
	double	distance;	// distance to the wall
	int		flag;		// flag for the wall
	t_dvector h_inter;
	t_dvector v_inter;
}	t_ray;

typedef struct s_config{
	char **path;
	int **rgb;
}t_config;

typedef struct s_node
{
    char	*line;
	int		x;
    struct	s_node *next;
}t_node;

typedef struct s_tmp{
	char ***elems;
	t_node *map_head;
	t_node *map_tail;
	int y;
	int max_x;
}t_tmp;

typedef struct s_data	//the data structure
{
	t_config	*config;
	t_texture	*txtr;
	char		**map2d;	// the map
	int			p_x;		// player x position in the map
	int			p_y;		// player y position in the map
	int			w_map;		// map width
	int			h_map;		// map height
}	t_data;

typedef struct s_sp
{
	mlx_texture_t	*txt[SP_FRAMES];
    int			frame;
    int			is_sp;
}	t_sp;

typedef struct s_mlx	//the mlx structure
{
	mlx_image_t		*img;	// the image
	t_sp			*sprite;
	mlx_t			*mlx_p;	// the mlx pointer
	t_ray			*ray;	// the ray structure
	t_data			*dt;	// the data structure
	t_player		*ply;	// the player structure
	t_tmp			*tmp; // this struct is just temp sturct for parsing
}	t_mlx;

// t_data *create_data();
void add_node(t_tmp *list, char *line);
// t_tmp *parse_list(void);
void free_list(t_tmp *list);
int file_check(char *file, char *ext);
int parse(t_tmp *tmp,t_data *data, char *file);
int id_check(char *id);
int check_data(t_data *data, int id, char *line);
char *read_elements(t_tmp *list, int fd);
char *read_map(char *line, int *x);
void check_map(t_data *data,char **map, int rows, int cols);
void print_2d_char_array(char **array);
int check_color(t_data *data, char *line, int id);
char	**ft_split2(char const *s, char c);
char **ft_split(char *line);
char	*gln(int fd);

//LIBFT
char* ft_strcpy(char* dst, const char* src);
int ft_strlcpy(char *res, char *line, int len);
size_t ft_strlen(char *str);
char *ft_strdup(char *str);
char* ft_strcat(char* dst, const char* src);
char *ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
int ft_strcmp(char *s1, char *s2);

//sprite
void	sprited(t_mlx *raw);
void	render_sp(t_mlx *raw);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

//mini_map
void mini_map(t_mlx *raw);


void ft_exit(t_tmp *parse);
void free_tmp(t_tmp *tmp);
t_mlx *create_mlx_struct(void);
void before_exit(t_mlx *mlx, int error_flag);
void mlx_key(mlx_key_data_t keydata, void *ml);
void	start_the_game(t_mlx *mlx);
void init_the_player(t_mlx *mlx);
void	game_loop(void *ml);
void	hook(t_mlx *mlx, double move_x, double move_y);
void	cast_rays(t_mlx *mlx);
void	start_the_game(t_mlx *mlx);
float	nor_angle(float angle);
void	render_wall(t_mlx *mlx, int ray);

#endif