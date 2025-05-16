#include "cub3D.h"

int main(int argc, char **argv)
{
    t_game game;
    if(argc != 2)
        return(1);
    if(check_map_extention(argv[1]))
        return (printf("map extention not correct")), 1;
    if(read_map(argv[1],&game))
        return (printf("unable to read map")), 1;
    if(check_wall(game.map))
        return(printf("map wall not closed")), 1;
    return(0);
        
}