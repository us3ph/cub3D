#include "cub3D.h"

int validate_textures(t_config *config)
{
	int i;

	i = 0;
	while(i < 4)
	{
		if (config->ids[i].id[0] == '\0') 
		{
			err("Error\nmissing or invalid texture\n");
			exit(1);
		}
		i++;
	}
    return 0;
}

int is_texture_line(char *line)
{
	return(!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "WE ", 3));
}

const char *get_texture_id(const char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0) return "NO";
	if (ft_strncmp(line, "SO", 2) == 0) return "SO";
	if (ft_strncmp(line, "WE", 2) == 0) return "WE";
	if (ft_strncmp(line, "EA", 2) == 0) return "EA";
	return NULL;
}

int handle_floor_color(char *line, t_config *config, int *floor_count)
{
    (*floor_count)++;
    if (*floor_count > 1)
    {
        err("Error\nduplicate identifier found\n");
        exit(1);
    }
    if (pars_rgb(line + 2, config->floor_rgb))
    {
        err("Error\ninvalid floor color format\n");
        exit(1);
    }
    return (0);
}

int handle_ceiling_color(char *line, t_config *config, int *ceiling_count)
{
    (*ceiling_count)++;
    if (*ceiling_count > 1)
    {
        err("Error\nduplicate identifier found\n");
        exit(1);
    }
    if (pars_rgb(line + 2, config->ceiling_rgb))
    {
        err("Error\ninvalid ceiling color format\n");
        exit (1);
    }   
    return (0);
}

int process_texture_line(char *line, t_game *game)
{
    const char *id;
    
    id = get_texture_id(line);
    if (id)
    {
        if (pars_textures(line + 2, game->config, id))
            return (1);
    }
    return (0);
}

int process_config_line(char *line, t_game *game, t_counters *counters) 
{
    if (is_texture_line(line))
        return (process_texture_line(line, game));
    else if (!ft_strncmp(line, "F ", 2))
        return (handle_floor_color(line, game->config, &counters->floor_count));
    else if (!ft_strncmp(line, "C ", 2))
        return (handle_ceiling_color(line, game->config, &counters->ceiling_count));
    else if (ft_isalpha(line[0]))  // Add this line
    {
        err("Error\nmissing or invalid texture\n");
        exit(1);
    }
    else
        return (2);
    return (0);
}

int init_game_config(t_game *game)
{
    game->config = malloc(sizeof(t_config));
    if (!game->config)
        return (1);
    ft_memset(game->config, 0, sizeof(t_config));
    return (0);
}

int process_line(int fd, t_game *game, t_counters *counters)
{
    char *line;
    char *s;
    int result;

    s = get_next_line(fd);
    if (!s)
        return (-1);
    line = ft_strtrim(s, "\n");
    free(s);
    if (line[0] == '\0')
    {
        free(line);
        game->map_start_line++;
        return (0);
    }
    result = process_config_line(line, game, counters);
    free(line);
    if (result == 1)
        return (1);
    if (result == 2)
        return (2);
    game->map_start_line++;
    return (0);
}

int read_config_section(int fd, t_game *game)
{
    t_counters counters;
    int result;

    counters.floor_count = 0;
    counters.ceiling_count = 0;
    while (1)
    {
        result = process_line(fd, game, &counters);
        if (result == -1)
            break;
        if (result == 1)
            return (close(fd), 1);
        if (result == 2)
            break;
    }
    if (result == -1)
        return (free(game->config), 1);
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
    char *line;
    char **map = NULL;
    int fd;
    int i;
    int map_index;
    int j;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (-1);
    // skip lines until map starts
    i = 0;
    while (i < game->map_start_line)
    {
        line = get_next_line(fd);
        if (!line)
            return (close(fd), -1);
        free(line);
        i++;
    }

    preprocess_map_file(file, game);
    
    map = malloc(sizeof(char *) * (game->map_lines + 1));
    if (!map)
        return (close(fd), 1);

    // init all pointers to NULL
    j = 0;
    while (j <= game->map_lines)
    {
        map[j] = NULL;
        j++;
    }

    map_index = 0;
    while (map_index < game->map_lines)
    {
        line = get_next_line(fd);
        if (!line)
            break;

        // check for empty line in middle of map
        if (line[0] == '\n')
        {
            free(line);
            if (map_index < game->map_lines)  // empty line in middle
            {
                // Free allocated memory using while loop
                j = 0;
                while (j < map_index)
                {
                    free(map[j]);
                    j++;
                }
                free(map);
                return (close(fd), 1);
            }
            continue; 
        }

        map[map_index] = line;
        map_index++;
    }

    map[map_index] = NULL;
    game->map = map;
    close(fd);
    return (0);
}

int read_map(char *file, t_game *game)
{
    int fd;

    game->map_start_line = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        err("Error\ncannot open map file\n");
        exit(1);
    }
    if (init_game_config(game))
        exit(1); 
    if (read_config_section(fd, game))
        return (1);
    if (validate_textures(game->config))
        cleanup_game(game), exit(1);
    if (store_and_validat_map(file, game))
    {
        err("Error\ninvalid map\n");
        exit(1);
    }
    return (0);
}