#include "player.h"
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "../utils/utils.h"

Player *player_create(float x, float y, float angle) {
    Player *p = malloc(sizeof(Player));
    p->x = x;
    p->y = y;
    p->dir_x = cos(degToRad(angle));
    p->dir_y = sin(degToRad(angle));
    p->angle = angle;
    p->FOV = 60;
    p->SPEED = 5;
    return p;
}

void move_player(Player *player) {
    const Uint8 ROT_SPEED = 5;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LSHIFT]) {
        player->SPEED *= 2;
    } else {
        player->SPEED *= 1;
    }
    if (state[SDL_SCANCODE_W]) {
        player->x += player->dir_x * player->SPEED;
        player->y += player->dir_y * player->SPEED;
    }
    if (state[SDL_SCANCODE_S]) {
        player->x -= player->dir_x * player->SPEED;
        player->y -= player->dir_y * player->SPEED;
    }
    if (state[SDL_SCANCODE_A]) {
        double old_dir_x = player->dir_x;
        player->dir_x = player->dir_x * cos(degToRad(ROT_SPEED)) - player->dir_y * sin(degToRad(ROT_SPEED));
        player->dir_y = old_dir_x * sin(degToRad(ROT_SPEED)) + player->dir_y * cos(degToRad(ROT_SPEED));
        player->angle -= ROT_SPEED;
        if (player->angle < 0) {
            player->angle += 360;
        }
    }
    if (state[SDL_SCANCODE_D]) {
        double old_dir_x = player->dir_x;
        player->dir_x = player->dir_x * cos(degToRad(-ROT_SPEED)) - player->dir_y * sin(degToRad(-ROT_SPEED));
        player->dir_y = old_dir_x * sin(degToRad(-ROT_SPEED)) + player->dir_y * cos(degToRad(-ROT_SPEED));
        player->angle +=ROT_SPEED;
        if (player->angle >= 360) {
            player->angle -= 360;
        }
    }
}




void draw_player(Player *player, SDL_Renderer *renderer) {
    COLOR_BLUE(renderer);
    SDL_Rect player_rect = {player->x, player->y, 10, 10};
    SDL_RenderFillRect(renderer, &player_rect);
    SDL_RenderDrawLine(renderer, player->x + 5, player->y + 5, player->x + 5 + player->dir_x * 50, player->y + 5 + player->dir_y * 50);
}


void player_destroy(Player *p) {
    free(p);
}



