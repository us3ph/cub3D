#include "cub3D.h"

int count_player(char **map)
{
    int i;
    int j;
    int count_player;

    i = 0;
    count_player = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
                count_player++;
            j++;
        }
        i++;
    }
    return(count_player);
}

int count_comma(char *str)
{
    int i;
    int comma;

    comma = 0;
    i = 0;
    while(str[i])
    {
        if(str[i] == ',')
            comma++;
        i++;
    }
    return(comma);
}

int count_lines_bfr_map(char **hmap)
{
    int i;

    i = 0;
    while(hmap[i] && hmap[i][0] != '1')
    {
        i++;
    }
    return(i);
}

int get_row_len(t_game *game)
{

    size_t j;
    int row_len;

    row_len = 0;
     j = 0;
    while (j < ft_strlen(game->map[0]))
    {
        if(game->map[0][j] == ' ')
        {
            j++;
            continue;
        }
        if(game->map[0][j] == '1' || game->map[0][j] == '0')
            row_len++;
        j++;
    }
    return(row_len);
}