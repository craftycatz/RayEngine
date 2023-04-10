#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>

typedef struct
{
    float x;
    float y;
    double dir_x;
    double dir_y;
    float angle;
    Uint8 FOV;
    Uint16 SPEED;
} Player;


Player *player_create(
        float x,
        float y,
        float angle
);

void move_player(
        Player *player
);

void draw_player(
        Player *player,
        SDL_Renderer *renderer
);

void player_destroy(
        Player *p
);

#endif