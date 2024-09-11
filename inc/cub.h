#ifndef CUB_H
#define CUB_H

#include "../libs/ftlib/inc/ftlib.h"
#include "../libs/mlx/include/MLX42/MLX42.h"

#define WIDTH 1920
#define HEIGHT 1080
#define FOV 90
#define SQUARE 30
#include <math.h>

typedef struct s_config{
	char *path[4];
	int rgb[2][3];
}t_config;

typedef struct s_node
{
    char *line;
	int x;
    struct s_node *next;
}t_node;

typedef struct s_parse{
	char **elems[6];
    t_node *map_head;
    t_node *map_tail;
    int y;
	int max_x;
}t_parse;

typedef struct s_vector{
	int x;
	int y;
}t_vector;

typedef struct s_map{
	t_vector player_pos;
	char **map;
	int width;
	int height;
	char player_dir;
}t_map;

typedef struct s_data{
    t_config *config;
    t_map *map;
	mlx_t *mlx;
	mlx_image_t* image;
}t_data;

t_data *create_data();
void add_node(t_parse *list, char *line);
t_parse *parse_list(void);
void free_list(t_parse *list);
int file_check(char *file, char *ext);
int parse(t_data *data, char *file);
int id_check(char *id);
int check_data(t_data *data, int id, char *line);
char *read_elements(t_parse *list, int fd);
char *read_map(char *line, int *x);
void check_map(t_data *data,char **map, int rows, int cols);
void print_2d_char_array(char **array);
int32_t mlx_screen(t_data *data);
int check_color(t_data *data, char *line, int id);

#endif