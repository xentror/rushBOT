#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

#include "context.h"
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

void render_map(struct map *map, SDL_Renderer *renderer)
{
    int w, h;
    SDL_Texture *block = IMG_LoadTexture(renderer, "./textures/wood_block.jpg");
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
    SDL_DestroyTexture(block);
    SDL_DestroyTexture(dirt);
    SDL_DestroyTexture(lava);
}

void render_tanks(struct GameContext *GC, SDL_Renderer *renderer)
{
    int w, h;
    SDL_Texture *tank_texture = IMG_LoadTexture(renderer,
            "./textures/tank.png");
    SDL_QueryTexture(tank_texture, NULL, NULL, &w, &h);
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Rect textr;
    textr.w = w / 2;
    textr.h = h / 2;

    double angle = atan2(GC->player1->direction->x, GC->player1->direction->y);
    angle = angle * (180 / M_PI1);
    textr.x = GC->player1->position->x * w / 4;
    textr.y = GC->player1->position->y * h / 4;
    SDL_RenderCopyEx(renderer, tank_texture, NULL, &textr, angle, NULL, flip);

    angle = atan2(GC->player1->direction->x, GC->player1->direction->y);
    angle = angle * (180 / M_PI1);
    textr.x = GC->player2->position->x * w / 4;
    textr.y = GC->player2->position->y * h / 4;
    SDL_RenderCopyEx(renderer, tank_texture, NULL, &textr, angle, NULL, flip);

    for (int i = 0; i < GC->nb_enemies; i++)
    {
        textr.x = GC->enemies[i]->position->x * w / 4;
        textr.y = GC->enemies[i]->position->y * h / 4;
        SDL_RenderCopy(renderer, tank_texture, NULL, &textr);
    }
    SDL_DestroyTexture(tank_texture);
}

void render_bullets(struct GameContext *GC, SDL_Renderer *renderer)
{
    SDL_Texture *bullet_texture = IMG_LoadTexture(renderer, "./textures/bullet.png");

    for (int i = 0; i < GC->nb_bullets; i++)
    {
        // render GC->bullets[i];
    }
}
