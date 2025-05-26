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

int check_map_elem(t_game *game) // add game in param
{
    int i;
    int j;

    if(!game->hmap || !game->hmap[0])
        return(1);
    game->config = malloc(sizeof(t_config));
    if(!game->config)
        return(1);
    ft_memset(game->config, 0, sizeof(t_config));
    i = 0;
    j = 0;
    while(i < 6 && game->hmap[i][0] != '1')
    {
        if(game->hmap[i][0] == '\n')
        {
            i++;
            continue;
        }
        if(!ft_strncmp(game->hmap[i], "NO ", 3))
            pars_textures(game->hmap[i] + 3, &j, game->config, "NO"), j++;
        else if(!ft_strncmp(game->hmap[i], "SO ", 3))
            pars_textures(game->hmap[i] + 3, &j, game->config, "SO"), j++;
        else if(!ft_strncmp(game->hmap[i], "EA ", 3))
            pars_textures(game->hmap[i] + 3, &j, game->config, "EA"), j++;
        else if(!ft_strncmp(game->hmap[i], "WE ", 3))
            pars_textures(game->hmap[i] + 3, &j, game->config, "WE"), j++;
        else if(!ft_strncmp(game->hmap[i], "C ", 2))
        {
            if(pars_rgb(game->hmap[i] + 2, game->config->ceiling_rgb))
                return(1);
        }
        else if(!ft_strncmp(game->hmap[i], "F ", 2))
        {
            if(pars_rgb(game->hmap[i] + 2, game->config->floor_rgb))
                return(1);
        }
        else
            return(1);
        i++;
    }
    i = 0;
    if(check_config_dup(game))
        return(1);
    return(0);
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

int check_config_dup(t_game *game)
{
    int i;
    int j;
    int count;

    i = 0;
    count = count_lines_bfr_map(game->hmap);
    while(i < count && game->hmap[i][0] != '\0')
    {
        if(game->hmap[i][0] == '\n')
        {
            i++;
            continue;
        }
        j = i + 1;
        while(j < count && game->hmap[j][0] != '\0')
        {
            if(game->hmap[j][0] == '\n')
            {
                j++;
                continue;
            }
            if(!ft_strcmp(game->hmap[i], game->hmap[j]))
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