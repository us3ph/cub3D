#include "cub3D.h"

int main(int argc, char **argv)
{
    t_game game;

    if(argc != 2)
        return err("Error\nnumber arguments not correct\n"), 1;


    if(check_map_extention(argv[1]))
        return err ("Error\nmap extention not correct\n"), 1;


    if(read_map(argv[1],&game))
        return err("Error\n"),err("unable to read map"), cleanup_game(&game), 1; // remove later the ruturn msg
    
    if(check_map_wall(&game))
        return err("Error\nmap wall not closed\n"), cleanup_game(&game), 1;

    if(check_map_chars(&game))
        return err("Error\nmap characters not correct\n"), cleanup_game(&game), 1;

    cleanup_game(&game);
    return(0);

}