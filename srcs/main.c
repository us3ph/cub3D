/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:57:25 by ytabia            #+#    #+#             */
/*   Updated: 2025/07/01 19:33:59 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv)
{
    t_game game;

    //my parsing and validation
    if (parsing(argc, argv, &game))
        return (1);
    // continue your part...

    cleanup_game(&game); // dont forget to clean the map and config in the end
}