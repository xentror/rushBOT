#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "map.h"
#define TEXTURE_W 128
#define TEXTURE_H 128

SDL_Window *window_init(struct map *map);
SDL_Renderer *render_map(struct map *map, SDL_Window *window);
void render_tanks(struct GameContext *GC, SDL_Renderer *renderer);
void render_bullets(struct GameContext *GC, SDL_Renderer *renderer);

#endif /* !RENDER_H */
