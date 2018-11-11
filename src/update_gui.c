#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "context.h"

SDL_Texture *full_heart_texture;
SDL_Texture *empty_heart_texture;

int get_life(struct tank *T)
{
    if (T->health <= 0)
        return 0;
    else if (T->health <= 20)
        return 1;
    else if (T->health <= 40)
        return 2;
    else if (T->health <= 60)
        return 3;
    else if (T->health <= 80)
        return 4;
    else
        return 5;
}

void print_heart(SDL_Renderer *renderer, struct tank *T, float width_pos)
{
    int nb_heart = get_life(T);
    printf("nbheart:%d\n", nb_heart);
    int w;
    int h;
    SDL_GetRendererOutputSize(renderer, &w, &h);

    float w_cur = width_pos * w;
    for (int i = 0; i < nb_heart; i++)
    {
        printf("x:%f y:%d\n", w_cur, h/10);
        if(!full_heart_texture)
            full_heart_texture = IMG_LoadTexture(renderer, "./textures/full_heart.png");
        SDL_Rect full_heart;
        full_heart.x = w_cur;
        full_heart.y = h/50;
        full_heart.w = w/30;
        full_heart.h = h/30;
        SDL_RenderCopy(renderer, full_heart_texture, NULL, &full_heart);
        w_cur += w/25;
    }

    for (int i = 0; i < 5 - nb_heart; i++)
    {
        printf("x:%f y:%d\n", w_cur, h/10);
        if(!empty_heart_texture)
            empty_heart_texture = IMG_LoadTexture(renderer, "./textures/empty_heart.png");
        SDL_Rect empty_heart;
        empty_heart.x = w_cur;
        empty_heart.y = h/50;
        empty_heart.w = w/30;
        empty_heart.h = h/30;
        SDL_RenderCopy(renderer, empty_heart_texture, NULL, &empty_heart);
        w_cur += w/25;
    }
}

void update_gui(SDL_Renderer *renderer, struct GameContext *GC)
{
    print_heart(renderer, GC->player1, 0.1);
    print_heart(renderer, GC->player1, 0.8);
}
