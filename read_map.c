#include "cub3D.h"

int is_texture_line(char *line)
{
	return(!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "WE ", 3));
}
int is_rgb_line(char *line)
{
	return(!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2));
}
const char *get_texture_id(const char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0) return "NO";
	if (ft_strncmp(line, "SO", 2) == 0) return "SO";
	if (ft_strncmp(line, "WE", 2) == 0) return "WE";
	if (ft_strncmp(line, "EA", 2) == 0) return "EA";
	return NULL;
}
int	read_map(char *file, t_game *game)
{
	const char	*id;
	char	*line;
	char	*s;
	int		fd;
	int 	i;

	i = 0;
	game->map_start_line = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	game->config = malloc(sizeof(t_config));
	if (!game->config)
		return(1);
	ft_memset(game->config, 0, sizeof(t_config));
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break;
		line = ft_strtrim(s, "\n");
		free(s);
		if(line[0] == '\0') // empty line, ignore and continue
		{
			free(line);
			game->map_start_line++;
			continue;
		}
		if(is_texture_line(line))
		{
			id = get_texture_id(line);
			if(id)
				pars_textures(line + 2, &i, game->config, id);
		}
		else if (!ft_strncmp(line, "F ", 2))
		{
			if (pars_rgb(line + 2, game->config->floor_rgb))
				return (free(line), close(fd), 1);
		}
		else if (!ft_strncmp(line, "C ", 2))
		{
			if (pars_rgb(line + 2, game->config->ceiling_rgb))
				return (free(line), close(fd), 1);
		}
		else
		{
			free(line);
			break;
		}
		free(line);
		game->map_start_line++;
	}
	if (!s)
		return (1);
	if(store_and_validat_map(file, game))
	{
		printf("map not valid");
		exit(1);
	}
	return (0);
}
int preprocess_map_file(char *file, t_game *game)
{
	char *line ;
	int fd;
	int i;
	int map_lines;

	 i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	while(i < game->map_start_line)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	map_lines = 0;
	while(1)
	{
		line = get_next_line(fd);
		if(!line)
			break;
		map_lines++;
		free(line);
	}
	game->map_lines = map_lines;
	close(fd);
	return(0);

}
int store_and_validat_map(char *file, t_game *game)
{
	char *skip;
	char **map = NULL;
	char *line;
	int fd;
	int i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	printf("game->map_start_line%d\n", game->map_start_line);
	while(i < game->map_start_line)
	{
		skip = get_next_line(fd);
		free(skip);
		i++;
	}
	map = malloc(sizeof(char *) * (game->map_lines + 1));
	if(!map)
		return(close(fd),1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if(line[0] == '\n')
			return(free(line), close(fd),1);
		map[i] = line;
		// free(line);
		i++;
	}
	map[i] = NULL;
	game->map = map;
	i = 0;
	while(game->map[i])
	{
		printf("%s", game->map[i]);
		i++;
	}
	close(fd);
	return(0);
}

