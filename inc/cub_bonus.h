#ifndef CUB_H
#define CUB_H

#include "MLX42.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>



# define SP_FRAMES 75
# define MINI_SIZE   14
# define CUB_MAP     8
# define DOOR "./sprite_png/door.png"

# define BUFFER_SIZE 10000
# define S_W 1900
# define S_H 1000
# define TILE_SIZE 32
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4
#define FLOOR_COL 0x99AAFF99
#define CEIL_COL 0xFF111111
#define WEST_COL 0xFFFFF222
#define EAST_COL 0xFF333333
#define SOUTH_COL 0xF4123123
#define NORTH_COL 0xFF555555


typedef struct s_gdata
{
	void			*data;
	struct s_gdata	*next;
}	t_gdata;

void	*my_malloc(size_t size, int mode);


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
	mlx_texture_t *door;
}t_texture;

typedef struct s_player
{
	int		plyr_x;
	int		plyr_y;
	double	angle;
	float	fov_rd;
	int		rot;
	int		l_r;
	int		u_d;
}	t_player;

typedef struct s_ray
{
	double	ray_ngl;
	double	distance;
	int		flag;
	t_dvector h_inter;
	t_dvector v_inter;
}	t_ray;

typedef struct s_config{
	char **path;
	int **rgb;
}t_config;

typedef struct s_node
{
	char *line;
	int x;
	struct s_node *next;
}t_node;

typedef struct s_tmp{
	char ***elems;
	t_node *map_head;
	t_node *map_tail;
	int y;
	int max_x;
}t_tmp;

typedef struct s_data
{
	t_config *config;
	t_texture *txtr;
	int		**rgb;
	char	**map2d;
	int		p_x;
	int		p_y;
	int		w_map;
	int		h_map;
}	t_data;

typedef struct s_mouse{
	int mouse_hidden;
}t_mouse;

typedef struct s_sp
{
	mlx_texture_t	*txt[SP_FRAMES];
	int			frame;
	int			is_sp;
}	t_sp;

typedef struct s_mlx
{
	mlx_image_t		*img;
	t_sp			*sprite;
	mlx_t			*mlx_p;
	t_ray			*ray;
	t_data			*dt;
	t_player		*ply;
	t_tmp			*tmp;
	int mouse_hidden;
	int wall_ty;
}	t_mlx;


//rendering_helper
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
float	nor_angle(float angle);
unsigned long	tohxa(int r, int g, int b);
double	offset_x(t_mlx *mlx, mlx_texture_t *texture);
int	reverse_bytes(int c);

//libft
char	**ft_split2(char const *s, char c);
char	**ft_split(char *line);
char	*ft_strcpy(char* dst, const char* src);
int		ft_strlcpy(char *res, char *line, int len);
size_t	ft_strlen(char *str);
char	*ft_strdup(char *str);
char*	ft_strcat(char* dst, const char* src);
int		ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);
char	*ft_strjoin(char *s1, char *s2);


char	*gnl(int fd);
void	add_node(t_tmp *list, char *line);
void	file_check(t_mlx *mlx, char *file, char *ext);
void	parse(t_mlx *mlx, char *file_name);
int		id_check(char *id);
void	check_data(t_mlx *mlx, int id, char *line);
char	*read_elements(t_tmp *list, int fd);
char	*read_map(char *line, int *x);
void	check_data(t_mlx *mlx, int id, char *line);
void	print_2d_char_array(char **array);
void	check_color(t_mlx *mlx, char *line, int id);

t_mlx	*create_mlx_struct(void);
void	check_map(t_mlx *mlx);
int		before_exit(t_mlx *mlx, int error);
void	mlx_key(mlx_key_data_t keydata, void *ml);
void	start_the_game(t_mlx *mlx);
void	init_the_player(t_mlx *mlx);
void	game_loop(void *ml);
void	hook(t_mlx *mlx, double move_x, double move_y);
void	cast_rays(t_mlx *mlx);
void	start_the_game(t_mlx *mlx);
void	render_wall(t_mlx *mlx, int ray);
int		valid_char(char c);
void	print_2d_char_array(char **array);
char	*ft_memset(char *str, int c, int n);
int		get_max(t_tmp *list);
void 	read_file(t_mlx *mlx, int fd);
void 	add_node(t_tmp *list, char *line);
int 	tab_spaces(char *dst, char *line);
int		wall_hit(float x, float y, t_mlx *mlx);
float 	v_y_inter(t_player *ply, float x_inter, float rad, float *y_step);
float 	v_x_inter(int plyr_x, float rad, float *x_step, int *pxl);
float	h_y_inter(int plyr_y, float *y_step, float rad, int *pxl);
float	h_x_inter(t_player *ply, float *x_step, float y_inter, float rad);
void 	render_sp(t_mlx *raw);
void 	mini_map(t_mlx *raw);
void	sprited(t_mlx *raw);

#endif