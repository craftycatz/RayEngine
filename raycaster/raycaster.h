#pragma once
#include <SDL2/SDL.h>
#include "../player/player.h"
#include "../map/map.h"
#include "../utils/utils.h"

#ifndef RAYCASTER_H
#define RAYCASTER_H

void draw_rays_2D(Player *player, SDL_Renderer *renderer, Map map);

#endif