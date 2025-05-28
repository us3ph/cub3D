#include "cub3D.h"

// int pars_textures( char *line, int *j, t_config *config, const char *id)
// {
//     ft_strncpy(config->ids[*j].id, id, 2);
//     config->ids[*j].id[2] = '\0';
//     while(*line == ' ' || *line == '\t')
//         line++;
//     config->ids[*j].path = ft_strdup(line);
//     if(j)
//         (*j)++;
//     return(0);
// }

//function to get the correct index for texture type
int get_texture_index(const char *id)
{
    if (ft_strcmp(id, "NO") == 0) return 0;
    if (ft_strcmp(id, "SO") == 0) return 1;
    if (ft_strcmp(id, "WE") == 0) return 2;
    if (ft_strcmp(id, "EA") == 0) return 3;
    return -1;
}

// Fixed pars_textures function
int pars_textures(char *line, t_config *config, const char *id)
{
    int index;

    index = get_texture_index(id);
    if (index == -1)
        return 1;
    
    //check if this texture type already exists
    if (config->ids[index].id[0] != '\0')
    {
        err("Error\nDuplicate texture identifier found\n");
        exit(1);
    }
    
    ft_strncpy(config->ids[index].id, id, 2);
    config->ids[index].id[2] = '\0';
    while(*line == ' ' || *line == '\t')
        line++;
    config->ids[index].path = ft_strdup(line);
    if (!config->ids[index].path)
        return 1;
    return 0;
}

int pars_rgb(char *line , int *rgb)
{
    int i;
    // int j;
    char **split;

    i = 0;
    if(count_comma(line) != 2)
        return(1);
    split = ft_split(line, ',');
    if(!split)
        return(1);
    while(split[i])
    {
        if(ft_isdigit_str(split[i]))
            return(free_split(split), 1);
        i++;
    }
    i = 0;
    while(i < 3)
    {
        if (split[i] == NULL)
        {
            return(free_split(split), 1);
        }
        rgb[i] = ft_atoi(split[i]);
        if(rgb[i] < 0 || rgb[i] > 255)
            return(1);
        i++;
    }
    free_split(split);
    return(0);
}

