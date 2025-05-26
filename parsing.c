#include "cub3D.h"

int pars_textures( char *line, int *j, t_config *config, const char *id)
{
    ft_strncpy(config->ids[*j].id, id, 2);
    config->ids[*j].id[2] = '\0';
    while(*line == ' ' || *line == '\t')
        line++;
    config->ids[*j].path = ft_strdup(line);
    if(j)
        (*j)++;
    return(0);
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

// Helper function to trim spaces/tabs from start and end
// char *ft_strtrim_spaces(char *str)
// {
//     int start = 0;
//     int end = ft_strlen(str) - 1;

//     while (str[start] && (str[start] == ' ' || str[start] == '\t'))
//         start++;
//     while (end >= start && (str[end] == ' ' || str[end] == '\t'))
//         end--;

//     return ft_substr(str, start, end - start + 1);
// }

// int pars_rgb(char *line, int *rgb)
// {
//     int i;
//     char **split;
//     char *trimmed;

//     printf("Parsing RGB from line: '%s'\n", line);

//     if (count_comma(line) != 2)
//         return (1);

//     split = ft_split(line, ',');
//     if (!split)
//         return (1);

//     i = 0;
//     while (split[i])
//     {
//         trimmed = ft_strtrim_spaces(split[i]);
//         if (!trimmed)
//             return (free_split(split), 1);

//         if (ft_isdigit_str(trimmed))
//         {
//             free(trimmed);
//             return (free_split(split), 1);
//         }

//         rgb[i] = ft_atoi(trimmed);
//         free(trimmed);

//         if (rgb[i] < 0 || rgb[i] > 255)
//             return (free_split(split), 1);

//         printf("rgb[%d] = %d\n", i, rgb[i]);  // print inside the loop for each component

//         i++;
//     }

//     free_split(split);
//     return (0);
// }

