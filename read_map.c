#include "cub3D.h"

void process_map_data(char *buff, t_game *game)
{
    game->map = ft_split(buff, '\n');
}

int read_map(char *file, t_game *game)
{
    char *buff;
    char *line;
    char *tmp;
    int fd;

    buff = NULL;
    fd = open(file, O_RDONLY);
    if(fd < 0)
        return(-1);
    while(1)
    {
        line = get_next_line(fd);
        if(!line)
            break;
        if(*line == '\n')
            return(free(line), free(buff), 1);
        tmp = buff;
        buff = ft_strjoin(buff, line);
        free(tmp);
        free(line);
    }
    if(!buff)
        return(1);
    return (process_map_data(buff,game)), 0;
}

int check_wall(char **map)
{
    int i;
    int j;

    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[0][j])
        {
            if(map[i][j] != '1')
                return(1);
            j++;
        }
        i++;
        while(map[i][j])
        {
            if(map[i][0] != '1' || ft_strlen(map[i]) != '1')
                return(1);
            i++;            
        }
    }
    return(0);
}

int check_map_extention(char *str)
{
    int i;

    i = ft_strlen(str); 
    if(i >= 1)
    {
        i--;
        if(str[i] == 'b' && str[i - 1] == 'u' && str[i - 2] == 'c')
            return(0);
        return(1);
    }
    return(0);
}
