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
# include <limits.h>
# include <unistd.h>


typedef struct s_ppos
{
    int height;
    int width;
} t_ppos;

typedef struct s_ids
{
    char id[3];
    char *path;
}   t_ids;

typedef struct s_config
{
    t_ids ids[4];
    int floor_rgb[3];
    int ceiling_rgb[3];
} t_config;

typedef struct s_game
{
    int row_index;
    int height;
    int width;
    char **map;
    char **hmap;
    t_ppos *player_pos;
    t_config *config;
}  t_game;

char	**ft_split(char const *s, char c);
int read_map(char *file, t_game *game);
int	check_map_extention(char *str);
// int check_map_wall(char **map);
void  process_map_data(char *buff, t_game *game);
void err(char *str);
int check_map_chars(char **map);
int get_map_height(char **map);
void free_map(char **map);
void cleanup_game(t_game *game);
int	check_map_wall(t_game *game);
int	ft_strncmp(const char *str1, const char *str2, size_t n);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strncpy(char *dest, const char *src, int n);
int check_map_elem(t_game *game);
int	ft_atoi(const char *str);
int check_config_dup(t_game *game);
int pars_textures( char *line, int *j, t_config *config, const char *id);
void	*ft_memset(void *str, int c, size_t n);


#endif