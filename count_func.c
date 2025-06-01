#include "cub3D.h"

int count_player(char **map)
{
    int i;
    int j;
    int count_player;

    i = 0;
    count_player = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
                count_player++;
            j++;
        }
        i++;
    }
    return (count_player);
}

int count_comma(char *str)
{
    int i;
    int comma;

    comma = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == ',')
            comma++;
        i++;
    }
    return (comma);
}
