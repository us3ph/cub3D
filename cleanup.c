#include "cub3D.h"

void cleanup_game(t_game *game)
{
    if(!game || !game->config)
        return;
    if(game->hmap)
    {
        free_map(game->hmap);
        free_config(game);
        game->hmap = NULL;
        game->config = NULL;
    }

}

void free_map(char **map)
{
    int i;

    if(!map)
        return;
    i = 0;
    while(map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

void free_config(t_game *game)
{
    int i;
    int num_ids;

    i = 0;
    num_ids = 0;
    while(i < 4)
    {
        if(game->config->ids[i].id[0] != '\0')
            num_ids++;
        i++;
    }
    i = 0;
    while(i < num_ids && game->config->ids[i].path != NULL)
    {
        free(game->config->ids[i].path);
        i++;
    }
    free(game->config);
}

void free_split(char **split)
{
    int i;

    i = 0;
    while(split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

void	err(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int get_map_height(char **map)
{
    int height;

    height = 0;
    while(map[height])
        height++;
    return(height);
}