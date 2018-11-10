#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "render.h"
#include "map.h"


SDL_Window *window_init(struct map *map)
{
    SDL_Window *window;

    int W = map->width * TEXTURE_W / 4;
    int H = map->height * TEXTURE_H / 4;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("TANK BATTLE !!!!",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            W,
            H,
            SDL_WINDOW_OPENGL);
    
    if (window == NULL) 
    {
        printf("could not create window\n");
        return NULL;
    }
    return window;
}

int render_map(struct map *map, SDL_Window *window)
{
    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1, 0);

    int w, h;
    SDL_Texture *block = IMG_LoadTexture(renderer, "./textures/block.jpg");
    SDL_Texture *dirt = IMG_LoadTexture(renderer, "./textures/dirt.jpg");
    SDL_Texture *lava = IMG_LoadTexture(renderer, "./textures/lava.png");
    SDL_QueryTexture(dirt, NULL, NULL, &w, &h);
    SDL_Rect textr;
    textr.w = w / 4;
    textr.h = h / 4;

    SDL_RenderClear(renderer);
    int a = 0;
    int b = 0;
    for (size_t i = 0; i < map->height; i++)
    {
        a = 0;
        for (size_t j = 0; j < map->width; j++)
        {
            textr.x = a;
            textr.y = b;
            if (map->table[i][j]->type == DIRT)
                SDL_RenderCopy(renderer, dirt, NULL, &textr);
            if (map->table[i][j]->type == LAVA)
                SDL_RenderCopy(renderer, lava, NULL, &textr);
            if (map->table[i][j]->type == BLOCK)
                SDL_RenderCopy(renderer, block, NULL, &textr);
            a += w / 4;
        } 
        b += h / 4;
    }
    SDL_RenderPresent(renderer);
    return 0;
}
