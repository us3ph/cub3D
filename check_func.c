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
	int	row_len;
	int	map_height;

	if (!game || !game->map || !game->map[0])
		return (1);
	
	map_height = get_map_height(game->map);
	if (map_height < 3)
			return (1);
	// check first row
    i = 0;
	row_len = ft_strlen(game->map[i]);
	if (row_len == 0)
			return (1);
	j = 0;
	while (j < row_len)
	{
		if (game->map[i][j] == ' ' || game->map[i][j] == '\n')
		{
			j++;
			continue;
		}
		if (game->map[i][j] != '1')
			return (1);
		j++;
	}
	// check middle rows
	i = 1;
	while (i < map_height - 1)
	{
		row_len = ft_strlen(game->map[i]);
		if (row_len == 0)
			return (1);
		j = 0;
		while (j < row_len && (game->map[i][j] == ' ' || game->map[i][j] == '\n'))
			j++;
		if (j >= row_len || game->map[i][j] != '1')
			return (1);
		j = row_len - 1;
		while (j >= 0 && (game->map[i][j] == ' ' || game->map[i][j] == '\n'))
			j--;
		if (j < 0 || game->map[i][j] != '1')
			return (1);
		i++;
	}
	// check last row
	i = map_height - 1;
	if (!game->map[i])
		return (1);
	row_len = ft_strlen(game->map[i]);
	if (row_len == 0)
		return (1);
	j = 0;
	while (j < row_len)
	{
		if (game->map[i][j] == ' ' || game->map[i][j] == '\n')
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


int check_map_chars(t_game *game)
{
    int player_count;

    if(!game->map || !game->map[0])
        return(1);
    if(validate_map_char(game))
        return(1);
    convert_space_to_zero(game);
    player_count = count_player(game->map);
    if(player_count != 1)
        return(1);
    return (0);
}
