#include "cub3D.h"

int main(int argc, char **argv)
{
    t_game game;
    if(argc != 2)
        return(1);
    if(check_map_extention(argv[1]))
        return err ("Error\n"),err("map extention not correct"), 1;
    if(read_map(argv[1],&game))
        return err("Error\n"),err("unable to read map"), 1;
    if(check_map_wall(game.map))
        return err("Error\n"), err("map wall not closed"), 1;
    if(check_map_chars(game.map))
        return err("Error\n"), err("map characters not correct"), 1;
    return(0);
        
}