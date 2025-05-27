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

int	check_map_wall(t_game *game)
{
	int	i;
	int	j;
	int	raw_len;
    int map_height;

	i = 0;
	if(!game || !game->map[0])
	    return(1);
	raw_len = get_row_len(game);
	if (raw_len == 0)
		return (1);
	j = 0;
	while (j < raw_len) // check first row
	{
        if(game->map[0][j] == ' ')
        {
            j++;
            continue;
        }
		if(game->map[0][j] != '1')
			return (1);
		j++;
	}
	map_height = get_map_height(&game->map[i]);
    i = 1;
	while (i < map_height -1)   // check midel rows
	{
		raw_len = ft_strlen(game->map[i]);
        if(raw_len == 0)
            return(1);
        j = 0;
        while(j < raw_len && game->map[i][j] == ' ')  // check left wall
            j++;
        if(j >= raw_len || game->map[i][j] != '1')
            return(1);
        j = raw_len -1;
        while(j >= 0 && game->map[i][j] == ' ') // check right wall
            j--;
        if(j < 0 || game->map[i][j] != '1')
            return(1);
        i++;
	}
    i = map_height -1;
	raw_len = ft_strlen(game->map[i]);  // check last row
	if (raw_len == 0)
        return (1);
	j = 0;
	while (j < raw_len)
	{
        if(game->map[i][j] == ' ')
        {
            j++;
            continue;
        }
		if (game->map[i][j] != '1')
			return (1);
		j++;
	}
	return (0);
}


int validate_map_char(char **map)
{
    int i;
    int j;
    int row_len;

    i = 0;
    while(map[i])
    {
        j = 0;
        row_len = ft_strlen(map[i]);
        while(j < row_len)
        {
            if(!is_valid_char(map[i][j]))
                return(1);
            j++;
        }
        i++;
    }
    return(0);
}


int check_map_chars(char **map)
{
    int player_count;

    if(!map || !map[0])
        return(1);
    if(validate_map_char(map))
        return(1);
    convert_space_to_zero(map);
    player_count = count_player(map);
    if(player_count != 1)
        return(1);
    return (0);
}

int check_config_dup(t_config *config)
{
    int i;
    int j;
    
    i = 0;
    while(i < 4)
    {
        if(config->ids[i].id[0] != '\0')
        {
            j = i + 1;
            while(j < 4)
            {
                if(config->ids[j].id[0] != '\0' && 
                   ft_strcmp(config->ids[i].id, config->ids[j].id) == 0)
                {
                    err("Error\nduplicate texture identifier\n");
                    return(1);
                }
                j++;
            }
        }
        i++;
    }
    return(0);
}