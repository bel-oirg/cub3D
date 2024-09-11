/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftlib.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:03:56 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/09/07 09:49:26 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLIB_H
#define FTLIB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <wctype.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 10000
// typedef enum config_state{
//     FRESH = -1,
//     BEGIN,
//     FID,
//     ID,
//     SPACING,
//     DATA,
//     ERROR,
//     END,
//     VALIDE,
// }cstate;

// typedef enum map_state{
//     element,
// }mstate;

// typedef struct s_vector{
// 	int x;
// 	int y;
// }t_vector;
// typedef struct s_texture{
// 	char *path;
// 	char *direction;
// }t_texture;
// typedef struct s_color{
//     int *rgb;
// 	char id;
// }t_color;

// typedef struct s_map{
// 	t_vector player_pos;
// 	char **map;
//     void **bitmap;
// 	int width;
// 	int height;
// 	char player_dir;
// }t_map;

// typedef struct s_parse{
//     t_map *map;
//     t_texture **textures;
// 	t_color **colors;
//     void *data;
//     char *check_list;
//     int elem_index;
//     int cstate;
// }t_parse;


typedef struct s_gcnode{
    void *address;
    struct s_gcnode *next;
}t_gcnode;

typedef struct s_gclist{
    t_gcnode *head;
    t_gcnode *tail;
    int node_used;
    int malloc_call;
    int free_call;
    size_t data_size;
}t_gclist;


t_gclist *get_gclist();
void set_gclist();
void gc_add(t_gcnode *node);
void gc_remove(void *address);
void *gc_malloc(size_t size);
void gc_free(void *address);
void gc_clear();

size_t ft_strlen(char *str);
char* ft_strcat(char* dst, const char* src);
char* ft_strcpy(char* dst, const char* src);
int ft_strlcpy(char *res, char *line, int len);
char	*ft_strchr(char *s, int c);
char *ft_strdup(char *str);
char *ft_strjoin(char *s1, char *s2);
int ft_strcmp(char *s1, char *s2);
int ft_get_id_index(char *line, char *check_list);
char **ft_split(char *line);
char	**ft_split2(char const *s, char c);
char	*gln(int fd);
#endif