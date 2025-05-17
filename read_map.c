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
	j = 0;
	while (j < raw_len)
	{
		if (map[0][j] != '1')
			return (1);
		j++;
	}
	i = 1;
	while (map[i])
	{
		raw_len = ft_strlen(map[i]);
		if (map[i][0] != '1' || map[i][ raw_len - 1] != '1')
			return (1);
		i++;
	}
	j = 0;
	raw_len = ft_strlen(map[i - 1]);
	while (j < raw_len)
	{
		if (map[i - 1][j] != '1')
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
int check_map_chars(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 32 && map[i][j + 1] == '0' && map[i][j - 1] == '0')
				map[i][j] = '0';
            if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N'
                && map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W')
            {
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}