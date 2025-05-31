#include "cub3D.h"

int	check_map_extention(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i >= 1)
	{
		i--;
		if (str[i] == 'b' && str[i - 1] == 'u' && str[i - 2] == 'c')
			return (0);
		return (1);
	}
	return (0);
}



int	check_row_walls(char *row)  // func to check first and last row 
{
	int	j;
	int	row_len;

	if (!row)
		return (1);
	row_len = ft_strlen(row);
	if (row_len == 0)
		return (1);
	j = 0;
	while (j < row_len)
	{
		if (row[j] == ' ' || row[j] == '\n')
		{
			j++;
			continue;
		}
		if (row[j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	check_middle_row_walls(char *row)  // check middle rows
{
	int	j;
	int	row_len;

	if (!row)
		return (1);
	row_len = ft_strlen(row);
	if (row_len == 0)
		return (1);
	j = 0;
	while (j < row_len && (row[j] == ' ' || row[j] == '\n'))
		j++;
	if (j >= row_len || row[j] != '1')
		return (1);
	j = row_len - 1;
	while (j >= 0 && (row[j] == ' ' || row[j] == '\n'))
		j--;
	if (j < 0 || row[j] != '1')
		return (1);
	return (0);
}

int	check_map_wall(t_game *game)
{
	int	i;
	int	map_height;

	if (!game || !game->map || !game->map[0])
		return (1);
	map_height = get_map_height(game->map);
	if (map_height < 3)
		return (1);
	if (check_row_walls(game->map[0]))
		return (1);
	i = 1;
	while (i < map_height - 1)
	{
		if (check_middle_row_walls(game->map[i]))
			return (1);
		i++;
	}
	if (check_row_walls(game->map[map_height - 1]))
		return (1);
	return (0);
}

int is_valid_char(char c)
{
    return(c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == '\n');
}

int validate_map_char(t_game *game)
{
    int i;
    int j;
    int row_len;

    i = 0;
    while(game->map[i])
    {
        j = 0;
        row_len = ft_strlen(game->map[i]);
        while(j < row_len)
        {
            if(!is_valid_char(game->map[i][j]))
			{
				printf("here3\n");
                return(1);
			}
            j++;
        }
        i++;
    }
    return(0);
}

int is_space_valid(char **map, int i, int j, int map_height)
{
    int row_len;
    int prev_row_len;
    int next_row_len;

    row_len = ft_strlen(map[i]);
    // check horizontal neighbors
    if (j > 0 && map[i][j - 1] == ' ')
        return (0);
    if(j + 1 < row_len && map[i][j + 1] == ' ')
		return(0);
    // check vertical neighbors
	if(i > 0)
	{
		prev_row_len = ft_strlen(map[i - 1]);
		if (j >= prev_row_len || (map[i - 1][j] == ' '))
			return (0);
	}
	if(i + 1 < map_height && map[i + 1])
	{
		next_row_len = ft_strlen(map[i + 1]);
		if (j >= next_row_len || (map[i + 1][j] == ' '))
			return (0);
	}	
    return (1); // aways return 1 if valid space
}

int validate_spaces(t_game *game)
{
    int i;
    int j;
    int row_len;
    // int map_height;
    
    game->map_height = get_map_height(game->map);
    i = 0;
    while (game->map[i])
    {
        j = 0;
        row_len = ft_strlen(game->map[i]);
        while (j < row_len)
        {
            if (game->map[i][j] == '0' || game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W' )
            {
                if (!is_space_valid(game->map, i, j, game->map_height))
                    return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

// void print_map(char **map)
// {
//     int i = 0;
//     while (map[i])
//     {
//         printf("Row %d (len=%zu): '%s'\n", i, ft_strlen(map[i]), map[i]);
//         i++;
//     }
//     printf("Total rows: %d\n", i);
// }


void get_player_position(t_game *game)
{
	int i;
	int j;
	int row_len;

	i = 0;
	while(i < game->map_height)
	{
		j = 0;
		row_len = ft_strlen(game->map[i]);
		while(j < row_len)
		{
			if(game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player_pos.height = i;
				game->player_pos.width = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

int check_map_chars(t_game *game)
{
    int player_count;
    if (!game->map || !game->map[0])
        return (1);
    if (validate_map_char(game))
        return (1);
    if (validate_spaces(game))
	{
    	return (1);
	}
	player_count = count_player(game->map);
    if (player_count != 1)
	{
    	return(1);
	}
	get_player_position(game);
    return (0);
}


