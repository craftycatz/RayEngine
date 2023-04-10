#pragma once
#include<SDL2/SDL.h>
#ifndef MAP_MAP_H
#define MAP_MAP_H

typedef struct
{
    int mapScale;
    int mapX;
    int mapY;
    int* map;
} Map;

void draw_map_2D(
        SDL_Renderer *renderer,
        Map map
);

void printMapArray(Map map);

Map read_map_file(char *filename);

#endif
