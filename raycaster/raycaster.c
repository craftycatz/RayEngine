#include "raycaster.h"

void drawWall(SDL_Renderer *renderer, int x, int y, int w, int h) {
    COLOR_GREEN(renderer);
    SDL_Rect wall = {x, y, w, h};
    SDL_RenderFillRect(renderer, &wall);
}

void draw_rays_2D(Player *player, SDL_Renderer *renderer, Map map) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &(SDL_Rect) {526, 0, 480, 380});

    int rayCount, mx, my, mapPos, depth;
    float verticalX, verticalY, rayX, rayY, rayAngle, xOffset, yOffset, distanceV, distanceH;

    rayAngle = fixAngle(player->angle + 210); // ray set back 30 degrees

    for (rayCount = 0; rayCount < 60; rayCount++) {
        //---Vertical---
        depth = 0;
        distanceV = 100000;
        float Tan = tan(degToRad(rayAngle));
        if (cos(degToRad(rayAngle)) > 0.001) {
            rayX = (((int) player->x >> 6) << 6) + 64;
            rayY = (player->x - rayX) * Tan + player->y;
            xOffset = 64;
            yOffset = -xOffset * Tan;
        } // looking left
        else if (cos(degToRad(rayAngle)) < -0.001) {
            rayX = (((int) player->x >> 6) << 6) - 0.0001;
            rayY = (player->x - rayX) * Tan + player->y;
            xOffset = -64;
            yOffset = -xOffset * Tan;
        } // looking right
        else {
            rayX = player->x;
            rayY = player->y;
            depth = 8;
        } // looking up or down. no hit

        while (depth < 8) {
            mx = (int) (rayX) >> 6;
            my = (int) (rayY) >> 6;
            mapPos = my * map.mapX + mx;
            if (mapPos > 0 && mapPos < map.mapX * map.mapY && map.map[mapPos] == 1) {
                depth = 8;
                distanceV = cos(degToRad(rayAngle)) * (rayX - player->x) - sin(degToRad(rayAngle)) * (rayY - player->y);
            } // hit
            else {
                rayX += xOffset;
                rayY += yOffset;
                depth += 1;
            } // check next horizontal
        }
        verticalX = rayX;
        verticalY = rayY;

        //---Horizontal---
        depth = 0;
        distanceH = 100000;
        Tan = 1.0 / Tan;
        if (sin(degToRad(rayAngle)) > 0.001) {
            rayY = (((int) player->y >> 6) << 6) - 0.0001;
            rayX = (player->y - rayY) * Tan + player->x;
            yOffset = -64;
            xOffset = -yOffset * Tan;
        } // looking up
        else if (sin(degToRad(rayAngle)) < -0.001) {
            rayY = (((int) player->y >> 6) << 6) + 64;
            rayX = (player->y - rayY) * Tan + player->x;
            yOffset = 64;
            xOffset = -yOffset * Tan;
        } // looking down
        else {
            rayX = player->x;
            rayY = player->y;
            depth = 8;
        } // looking left or right. no hit

        while (depth < 8) {
            mx = (int) (rayX) >> 6;
            my = (int) (rayY) >> 6;
            mapPos = my * map.mapX + mx;
            if (mapPos > 0 && mapPos < map.mapX * map.mapY && map.map[mapPos] == 1) {
                depth = 8;
                distanceH = cos(degToRad(rayAngle)) * (rayX - player->x) - sin(degToRad(rayAngle)) * (rayY - player->y);
            } // hit
            else {
                rayX += xOffset;
                rayY += yOffset;
                depth += 1;
            } // check next horizontal
        }

        COLOR_GREEN(renderer)
        if (distanceV < distanceH) {
            rayX = verticalX;
            rayY = verticalY;
            distanceH = distanceV;
            COLOR_RED(renderer)
        }

        SDL_RenderDrawLine(renderer, player->x + 5, player->y + 5, rayX, rayY);

        int castAngle = fixAngle(player->angle - rayAngle);
        distanceH = distanceH * cos(degToRad(castAngle));
        int lineHeight = (map.mapScale * 320) / distanceH;
        if (lineHeight > 320) { lineHeight = 320; } // line height and limit
        int lineOff = 160 - (lineHeight >> 1); // line offset

        drawWall(renderer, 526 + rayCount * 8, lineOff, 8, lineHeight);

        rayAngle = fixAngle(rayAngle - 1);
    }
}

