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
	if (!buff)
		return (1);
	return ((process_map_data(buff, game)), free(buff), 0);
}
int	check_map_wall(char **map)
{
	int	i;
	int	j;
	int	raw_len;

	i = 0;
	if (!map || !map[0])
		return (1);
	raw_len = ft_strlen(map[0]);
	if (raw_len == 0)
		return (1);
	j = 0;
	while (j < raw_len)
	{
        if(map[0][j] == 32)
            j++;
		else if(map[0][j] != '1')
			return (1);
		j++;
	}
	i = 1;
    j = 0;
	while (map[i + 1] != NULL)
	{
		raw_len = ft_strlen(map[i]);
        if(map[i][j] == 32)
        {
            j++;
            continue;
        }
		else if (raw_len == 0 || map[i][0] != '1' || map[i][raw_len - 1] != '1')
			return (1);
		i++;
	}
	j = 0;
	raw_len = ft_strlen(map[i]);  // map[i] is the last row after the loop
	if (raw_len == 0)
		return (1);
	while (j < raw_len)
	{
        if(map[i][j] == 32)
            j++;
		else if (map[i][j] != '1')  // Check map[i], not map[i-1]
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
            return(map[i - 1][i] == '0' && map[i + 1][j] == '0');
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
        while(i < row_len)
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
int check_map_chars(char **map)
{
    int player_count;

    if(!map || !map[0])
        return(1);
    convert_space_to_zero(map);
    if(validate_map_char(map))
        return(1);
    player_count = count_player(map);
    if(player_count != 1)
        return(1);
    return (0);
}