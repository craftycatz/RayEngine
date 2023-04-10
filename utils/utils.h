#pragma once
#ifndef UTILS_H
#define UTILS_H
#include<errno.h>
#include <SDL2/SDL.h>

#define COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255);
#define COLOR_BLACK(x) SDL_SetRenderDrawColor(x, 0, 0, 0, 255);
#define COLOR_RED(x) SDL_SetRenderDrawColor(x, 255, 0, 0, 255);
#define COLOR_GREEN(x) SDL_SetRenderDrawColor(x, 0, 255, 0, 255);
#define COLOR_BLUE(x) SDL_SetRenderDrawColor(x, 0, 0, 255, 255);

#define return_defer(value) do { result = (value); goto defer; } while (0)

int fixAngle(int a);

float degToRad(int a);

#endif
