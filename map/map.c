#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

#include "map.h"
#include "../utils/utils.h"

int parse_map_file(const char* filename, Map *map)
{
    FILE* file = fopen(filename, "r");
    int result;
    if (!file) return_defer(errno);

    char line[1024];
    int mapPos = 0;

    map->mapX = 0;
    map->mapY = 0;
    map->mapScale = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "x: ", 3) == 0)
        {
            if((!atoi(line + 3)) != 0){
                fprintf(stderr, "Error: Invalid map data.\n");
            }
            map->mapX = atoi(line + 3);
        }
        else if (strncmp(line, "y: ", 3) == 0)
        {
            if((!atoi(line + 3)) != 0){
                fprintf(stderr, "Error: Invalid map data.\n");
            }
            map->mapY = atoi(line + 3);
            map->map = malloc(sizeof(int) * map->mapX * map->mapY);
        }
        else if (strncmp(line, "s: ", 3) == 0)
        {
            if((!atoi(line + 3)) != 0){
                fprintf(stderr, "Error: Invalid map data.\n");
                return_defer(errno);
            }
            map->mapScale = atoi(line + 3);
        }
        else {
            int i = 0;
            int maxI = (int) map->mapX - 1;
            char *p = line;
            if (line[0] == '[') {
                p = line + 1;
            }
            while ((i <= maxI && *p != ']') && *p != '\0') {
                if (*p == '0' || *p == '1') {
                    if (i >= map->mapX * map->mapY) {
                        fprintf(stderr, "Error: Too many map squares in file.\n");
                        return_defer(errno);
                    }
                    map->map[mapPos] = *p - '0';
                    i++;
                    mapPos++;
                }
                p++;
            }
        }
    }

    if (map->mapX <= 0 || map->mapY <= 0 || map->mapScale <= 0 || !map->map)
    {
        fprintf(stderr, "Error: Invalid map data.\n");
        return_defer(errno);
    }

    return_defer(0);

    defer:
        if (file) fclose(file);
        return result;

}



Map read_map_file(char *filename)
{
    Map map;

    if (parse_map_file(filename, &map) != 0) {
        fprintf(stderr, "Failed to parse map file: %s\n", filename);
        exit(1);
    }

    // check if map is valid
    if (map.mapX <= 0 || map.mapY <= 0 || map.mapScale <= 0) {
        fprintf(stderr, "Error: invalid map dimensions.\n");
        exit(1);
    }


    return map;
}

void draw_map_2D(SDL_Renderer *renderer, Map map){
    int x, y, xOff, yOff;
    for(y=0; y<map.mapY; y++){
        for(x=0; x<map.mapX; x++){
            if(map.map[y*map.mapX + x] == 1){
                COLOR_BLACK(renderer);
            }
            else{
                COLOR_WHITE(renderer);
            }
            xOff = x * map.mapScale;
            yOff = y * map.mapScale;
            SDL_Rect rect = {xOff, yOff, map.mapScale - 1, map.mapScale - 1};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
