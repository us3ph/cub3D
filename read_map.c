#include "cub3D.h"

void	process_map_data(char *buff, t_game *game)
{
    int i;

    i = 0;
	game->hmap = ft_split(buff, '\n');
    while(game->hmap[i])
    {
        if(game->hmap[i][0] == '1')
        {
            game->map = &game->hmap[i];
            break;
        }
        i++;
    }
}
int	read_map(char *file, t_game *game)
{
	char	*buff;
	char	*line;
	char	*tmp;
	int		fd;

	buff = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		// if(*line == '\n')
		//     return(free(line), free(buff), 1);
		tmp = buff;
		buff = ft_strjoin(buff, line);
		free(tmp);
		free(line);
	}
    close(fd);
	if (!buff)
		return (1);
	return ((process_map_data(buff, game)), free(buff), 0);
}
int	check_map_wall(t_game *game)
{
	int	i;
	int	j;
	int	raw_len;
    int map_height;

	i = 0;
	if (!game->map || !game->map[0])
		return (1);
	raw_len = ft_strlen(game->map[0]);
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
int is_valid_char(char c)
{
    return(c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int horizonal_zeros(char *row, int j, int row_len)
{
    if(j > 0 && j < row_len - 1)
        return(row[j - 1] == '0' && row[j + 1] == '0');
    return(0);
}

int vertical_zeros(char **map, int i, int j, int map_height)
{

    int prev_len;
    int next_len;
    if(i > 0 && i < map_height - 1)
    {
        prev_len = ft_strlen(map[i - 1]);
        next_len = ft_strlen(map[i + 1]);
        if(j < prev_len && j < next_len)
            return(map[i - 1][j] == '0' && map[i + 1][j] == '0');
    }
    return(0);
}
void convert_space_to_zero(char **map)
{
    int i;
    int j;
    int row_len;
    int map_height;

    map_height = get_map_height(map);
    i = 0;
    while(map[i])
    {
        j = 0;
        row_len = ft_strlen(map[i]);
        while(j < row_len)
        {
            if(map[i][j] == ' ')
            {
                if(horizonal_zeros(map[i], j, row_len))
                    map[i][j] = '0';
                else if(vertical_zeros(map, i, j, map_height))
                    map[i][j] = '0';
            }
            j++;
        }
        i++;
    }
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
int pars_textures( char *line, int *j, t_config *config, const char *id)
{
    while(*line == ' ' || *line == '\t')
        line++;
    ft_strncpy(config->ids[*j].id, id, 2);
    config->ids[*j].id[2] = '\0';
    config->ids[*j].path = ft_strdup(line);
    return(0);
}

int ft_isdigit(char *str)
{

    int i;

    i = 0;
    while(str[i])
    {
        while(str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] < 48 || str[i] > 57)
		    return (1);
        i++;
    }
    return(0);
}

int pars_rgb(char *line , int *rgb)
{
    int i;
    int j;
    char **split;

    i = 0;
    if(count_comma(line) != 2)
        return(1);
    split = ft_split(line, ',');
    if(!split)
        return(1);
    while(split[i])
    {
        if(ft_isdigit(split[i]))
            return(1);
        i++;
    }
    i = 0;
    while(i < 3)
    {
        if (split[i] == NULL)
        {
            return(1);
        }
        rgb[i] = ft_atoi(split[i]);
        if(rgb[i] < 0 || rgb[i] > 255)
            return(1);
        i++;
    }
    j = 0;
    while(split[j])
    {
        free(split[j]);
        j++;
    }
    free(split);
    return(0);
}

int check_map_elem(t_game *game) // add game in param
{
    int i;
    int j;

    game->config = malloc(sizeof(t_config));
    if(!game->config)
        return(1);
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
            pars_textures(game->hmap[i] + 3, &j, game->config, "NO");
        else if(!ft_strncmp(game->hmap[i], "SO ", 3))
            pars_textures(game->hmap[i] + 3, &j, game->config, "SO");
        else if(!ft_strncmp(game->hmap[i], "EA ", 3))
            pars_textures(game->hmap[i] + 3, &j, game->config, "EA");
        else if(!ft_strncmp(game->hmap[i], "WE ", 3))
            pars_textures(game->hmap[i] + 3, &j, game->config, "WE");
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
        j++;
    }
    if(check_config_dup(game))
        return(1);
    return(0);
}
int check_config_dup(t_game *game)
{
    int i;
    int j;

    i = 0;
    while(i < 6)
    {
        j = i + 1;
        while(j < 6)
        {
            if(game->hmap[i][0] == '\n')
            {
                i++;
                continue;
            }
            if(!ft_strncmp(game->config->ids[i].id, game->config->ids[j].id, 3))
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

    i = 0;
    while(game->config->ids[i].path != NULL)
    {
        free(game->config->ids[i].path);
        i++;
    }
    free(game->config);
}
void cleanup_game(t_game *game)
{
    if(!game || !game->config)
        return;
    if(game->hmap)
    {
        free_map(game->hmap);
        // free_config(game);
        game->hmap = NULL;
        game->config = NULL;
    }

}