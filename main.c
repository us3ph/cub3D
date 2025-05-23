#include "cub3D.h"

int main(int argc, char **argv)
{
    t_game game;
    
    if(argc != 2)
        return(1);
    if(check_map_extention(argv[1]))
        return err ("Error\n"),err("map extention not correct"), 1;
    if(read_map(argv[1],&game))
        return err("Error\n"),err("unable to read map"), cleanup_game(&game), 1;
    if(check_map_elem(&game))
        return err("Error\n"), err("invalid map config"), cleanup_game(&game), 1;
    if(check_map_wall(&game))
        return err("Error\n"), err("map wall not closed"), cleanup_game(&game), 1;
    if(check_map_chars(game.map))
        return err("Error\n"), err("map characters not correct"), cleanup_game(&game), 1;
    cleanup_game(&game);
    return(0);

}