#include <stdio.h>
#include <SDL2/SDL.h>
#include <libgen.h>

#include "player/player.h"
#include "map/map.h"
#include "raycaster/raycaster.h"
#include "json/json.h"
#include "datastructures/dynamicarry.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 512


int main(void) {



      // Initialize SDL
      if (SDL_Init(SDL_INIT_VIDEO) != 0) {
          fprintf(stderr, "SDL_Init Error: %s", SDL_GetError());
      }
  
      // Create a window
      SDL_Window *win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      if (win == NULL) {
          fprintf(stderr, "SDL_CreateWindow Error: %s", SDL_GetError());
      }
      // Create a renderer
      SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (renderer == NULL) {
         fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
     }
      //get the path of the executable
      char exe_path[1024];
      char map_path[1024];
      realpath(__FILE__, exe_path);
      char* dir_path = dirname(exe_path);
      sprintf(map_path, "%s/map.txt", dir_path);
      // Create a player
      Player *player = player_create(100, 100, 90);
      Map map = read_map_file(map_path);

      bool running = true;
      while (running) {
          SDL_Event event;
          while (SDL_PollEvent(&event)) {
              if (event.type == SDL_QUIT) {
                  running = false;
              }
              move_player(player);
          }
          // Clear the screen to grey
          SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
          SDL_RenderClear(renderer);
          // Draw the map
          draw_map_2D(renderer, map);
          // Draw the player in its new position
          draw_player(player, renderer);
          // Draw the rays
          draw_rays_2D(player, renderer, map);
          // Present the renderer
          SDL_RenderPresent(renderer);
      }
    // Clean up
    player_destroy(player);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
