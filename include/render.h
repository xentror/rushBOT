#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "map.h"
#define TEXTURE_W 128
#define TEXTURE_H 128
#define M_PI1 3.1415926535
#define SCALE 4
#define WIDTH_WINDOW 28
#define HEIGHT_WINDOW 28

SDL_Window *window_init(void);
void render_map(struct map *map, SDL_Renderer *renderer);
void render_tanks(struct GameContext *GC, SDL_Renderer *renderer);
void render_bullets(struct GameContext *GC, SDL_Renderer *renderer);

#endif /* !RENDER_H */
