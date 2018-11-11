#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

#include "context.h"
#include "render.h"
#include "map.h"


SDL_Window *window_init(void)
{
    SDL_Window *window;

    int W = WIDTH_WINDOW * TEXTURE_W / SCALE;
    int H = HEIGHT_WINDOW * TEXTURE_H / SCALE;
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
    SDL_Texture *block = IMG_LoadTexture(renderer,
            "./textures/wood_block.jpg");
    SDL_Texture *dirt = IMG_LoadTexture(renderer, "./textures/dirt.jpg");
    SDL_Texture *lava = IMG_LoadTexture(renderer, "./textures/lava.png");
    SDL_QueryTexture(dirt, NULL, NULL, &w, &h);
    SDL_Rect textr;
    textr.w = w / SCALE;
    textr.h = h / SCALE;

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
            a += w / SCALE;
        }
        b += h / SCALE;
    }
    SDL_DestroyTexture(block);
    SDL_DestroyTexture(dirt);
    SDL_DestroyTexture(lava);
}

void render_tanks(struct GameContext *GC, SDL_Renderer *renderer)
{
    int w, h;
    SDL_Texture *tank_g_texture = IMG_LoadTexture(renderer,
            "./textures/tank-g.png");
    SDL_Texture *tank_r_texture = IMG_LoadTexture(renderer,
            "./textures/tank-r.png");
    SDL_Texture *tank_b_texture = IMG_LoadTexture(renderer,
            "./textures/tank-b.png");
    SDL_QueryTexture(tank_r_texture, NULL, NULL, &w, &h);
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Rect textr;
    textr.w = w / SCALE;
    textr.h = h / SCALE;

    double angle = atan2(GC->player1->direction->x, GC->player1->direction->y);
    angle = angle * (180 / M_PI1);
    textr.x = GC->player1->position->x * w / SCALE;
    textr.y = GC->player1->position->y * h / SCALE;
    SDL_RenderCopyEx(renderer, tank_b_texture, NULL, &textr, angle, NULL, flip);

    angle = atan2(GC->player2->direction->x, GC->player2->direction->y);
    angle = angle * (180 / M_PI1);
    textr.x = GC->player2->position->x * w / SCALE;
    textr.y = GC->player2->position->y * h / SCALE;
    SDL_RenderCopyEx(renderer, tank_g_texture, NULL, &textr, angle, NULL, flip);

    for (int i = 0; i < GC->nb_enemies; i++)
    {
        angle = atan2(GC->enemies[i]->direction->x,
                GC->enemies[i]->direction->y);
        angle = angle * (180 / M_PI1);
        textr.x = GC->enemies[i]->position->x * w / SCALE;
        textr.y = GC->enemies[i]->position->y * h / SCALE;
        SDL_RenderCopyEx(renderer, tank_r_texture, NULL, &textr, angle,
                NULL, flip);
    }
    SDL_DestroyTexture(tank_g_texture);
    SDL_DestroyTexture(tank_b_texture);
    SDL_DestroyTexture(tank_r_texture);
}

void render_bullets(struct GameContext *GC, SDL_Renderer *renderer)
{
    SDL_Texture *bullet_texture = IMG_LoadTexture(renderer,
            "./textures/bullet1.png");
    int w, h;
    SDL_QueryTexture(bullet_texture, NULL, NULL, &w, &h);
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Rect textr;
    textr.w = w / SCALE;
    textr.h = h / SCALE;
    double angle;
    for (int i = 0; i < GC->nb_bullets; i++)
    {
        angle = atan2(GC->bullets[i]->direction->x,
                GC->bullets[i]->direction->y);
        angle = angle * (180 / M_PI1);
        textr.x = (GC->bullets[i]->position->x  + 0) * w / SCALE;
        textr.y = (GC->bullets[i]->position->y + 0) * h / SCALE;
        SDL_RenderCopyEx(renderer, bullet_texture, NULL, &textr, angle,
                NULL, flip);
    }
    SDL_DestroyTexture(bullet_texture);
}
