#ifndef CUB3D_H
#define CUB3D_H

# include "get_next_line.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <mlx.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>


typedef struct s_ppos
{
    int height;
    int width;
} t_ppos;

typedef struct s_game
{
    int height;
    int width;
    char **map;
    char **hmap;
    t_ppos player_pos;
}  t_game;

typedef struct s_map_colors
{
    char *identifier;
    char *RGB;
} t_map_colors;

typedef struct s_path
{
    char *identifier;
    char *path;
} t_path;
typedef struct s_map_elem
{
    t_path *path;
    t_map_colors *colors;
} t_map_elem;

char	**ft_split(char const *s, char c);
int read_map(char *file, t_game *game);
// int check_map_wall(char **map);
void process_map_data(char *buff, t_game *game);
int check_map_extention(char *str);
void err(char *str);
int check_map_chars(char **map);
int get_map_height(char **map);
void free_map(char **map);
void cleanup_game(t_game *game);
int	check_map_wall(char **map, char **hmap);





#endif