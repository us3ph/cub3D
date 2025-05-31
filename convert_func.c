#include "cub3D.h"

// void convert_space_to_zero(t_game *game)
// {
//     int i;
//     int j;
//     int row_len;
//     int map_height;

//     map_height = get_map_height(game->map);
//     i = 0;
//     while(game->map[i])
//     {
//         j = 0;
//         row_len = ft_strlen(game->map[i]);
//         while(j < row_len)
//         {
//             if(game->map[i][j] == ' ')
//             {
//                 if(horizonal(game->map[i], j, row_len))
//                     game->map[i][j] = '0';
//                 else if(vertical(game->map, i, j, map_height))
//                     game->map[i][j] = '0';
//             }
//             j++;
//         }
//         i++;
//     }
// }

// int vertical(char **map, int i, int j, int map_height)
// {
//     int prev_len;
//     int next_len;
//     if(i > 0 && i < map_height - 1)
//     {
//         prev_len = ft_strlen(map[i - 1]);
//         next_len = ft_strlen(map[i + 1]);
//         if(j < prev_len && j < next_len)
//             return(map[i - 1][j] == '1' && map[i + 1][j] == '1');
//     }
//     return(0);
// }

// int horizonal(char *row, int j, int row_len)
// {
//     if(j > 0 && j < row_len - 1)
//         return(row[j - 1] == '1' && row[j + 1] == '1');
//     return(0);
// }

int is_valid_char(char c)
{
    return(c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == '\n');
}