#include "cub3D.h"

void	process_map_data(char *buff, t_game *game)
{
	game->map = ft_split(buff, '\n');
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
int	check_map_wall(char **map, char **hmap)
{
	int	i;
	int	j;
	int	raw_len;
    int map_height;

	i = 0;
	if (!map || !map[0])
		return (1);
    while(map[i])
    {
        if(map[i][0] == '1')
        {
            hmap = &map[i];
            break;
        }
        i++;
    }
    i = 0;
    // while(hmap[i]) // check map 1
    // {
    //     printf("%s\n", hmap[i]);
    //     i++;
    // }
	raw_len = ft_strlen(map[0]);
	if (raw_len == 0)
		return (1);
	j = 0;
	while (j < raw_len) // check first row
	{
        if(map[0][j] == ' ')
        {
            j++;
            continue;
        }
		if(map[0][j] != '1')
			return (1);
		j++;
	}
	map_height = get_map_height(&map[i]);
    i = 1;
	while (i < map_height -1)   // check midel rows
	{
		raw_len = ft_strlen(map[i]);
        if(raw_len == 0)
            return(1);
        j = 0;
        while(j < raw_len && map[i][j] == ' ')  // check left wall
            j++;
        if(j >= raw_len || map[i][j] != '1')
            return(1);
        j = raw_len -1;
        while(j >= 0 && map[i][j] == ' ') // check right wall
            j--;
        if(j < 0 || map[i][j] != '1')
            return(1);
        i++;
	}
    i = map_height -1;
	raw_len = ft_strlen(map[i]);  // check last row
	if (raw_len == 0)
        return (1);
	j = 0;
	while (j < raw_len)
	{
        if(map[i][j] == ' ')
        {
            j++;
            continue;
        }
		if (map[i][j] != '1')
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
int validate_map_elem(char **map)
{
    int i;
    int j;

    t_map_elem map_elem;
    // t_path path;
    i = 0;
    while(map[i])
    {
        if(map[i][0] == '\n')
        {
            i++;
            continue;
        }
        j = 0;
        if(map[i][j] == 'N' && map[i][j + 1] == 'O')
        {
            map_elem.path->identifier = "NO";
            j += 3;
            while(map[i][j])
                map_elem.path->path = &map[i][j++];
        }
        else if(map[i][j] == 'S' && map[i][j] == 'O')
        {
            map_elem.path->identifier = "SO";
            j += 3;
            while(map[i][j])
                map_elem.path->path = &map[i][j++];
        }
        else if(map[i][j] == 'E' && map[i][j + 1] == 'A')
        {
            map_elem.path->identifier = "EA";
            j += 3;
            while(map[i][j])
                map_elem.path->path = &map[i][j++];
        }
        else if(map[i][j] == 'W' && map[i][j] == 'E')
        {
            map_elem.path->identifier = "WE";
            j += 3;
            while(map[i][j])
                map_elem.path->path = &map[i][j++];
        }
        else if(map[i][j] == 'C')
        {
            map_elem.colors->identifier = "C";
            j += 2;
            while(map[i][j])
                map_elem.colors->RGB = &map[i][j++];
        }
        else if(map[i][j] == 'F')
        {
            map_elem.colors->identifier = "F";
            j += 2;
            while(map[i][j])
                map_elem.colors->RGB = &map[i][j++];
        }
        else
            return(1);
        i++;
    }
    return(0);
}
int check_map_chars(char **map)
{
    int player_count;
    t_map_colors map_colors;

    if(!map || !map[0])
        return(1);
    validate_map_elem(map);
    convert_space_to_zero(map);
    if(validate_map_char(map))
        return(1);
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
void cleanup_game(t_game *game)
{
    if(game->map)
    {
        free_map(game->map);
        game->map = NULL;
    }

}