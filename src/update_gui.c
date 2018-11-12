#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "context.h"

SDL_Texture *full_heart_texture;
SDL_Texture *empty_heart_texture;
SDL_Texture *player_1_texture;
SDL_Texture *player_2_texture;

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

void iter_full(int nb_heart, SDL_Renderer *renderer, float *w_cur)
{
    int w;
    int h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    for (int i = 0; i < nb_heart; i++)
    {
        if (!full_heart_texture)
            full_heart_texture = IMG_LoadTexture(renderer,
                    "./textures/full_heart.png");
        SDL_Rect full_heart;
        full_heart.x = *w_cur;
        full_heart.y = h/50;
        full_heart.w = w/30;
        full_heart.h = h/30;
        SDL_RenderCopy(renderer, full_heart_texture, NULL, &full_heart);
        *w_cur += w/25;
    }
}

void iter_empty(int nb_heart, SDL_Renderer *renderer, float *w_cur)
{
    int w;
    int h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    for (int i = 0; i < 5 - nb_heart; i++)
    {
        if(!empty_heart_texture)
            empty_heart_texture = IMG_LoadTexture(renderer,
                    "./textures/empty_heart.png");
        SDL_Rect empty_heart;
        empty_heart.x = *w_cur;
        empty_heart.y = h/50;
        empty_heart.w = w/30;
        empty_heart.h = h/30;
        SDL_RenderCopy(renderer, empty_heart_texture, NULL, &empty_heart);
        *w_cur += w/25;
    }
}

void print_heart(SDL_Renderer *renderer, struct tank *T,
        float width_pos, int player)
{
    int nb_heart = get_life(T);

    int w;
    int h;
    SDL_GetRendererOutputSize(renderer, &w, &h);

    float w_cur = width_pos * w;

    SDL_Rect player_logo;
    player_logo.x = w_cur;
    player_logo.y = h/50;
    player_logo.w = w/30;
    player_logo.h = h/30;
    w_cur += w/20;

    if (player == 1)
    {
        if (!player_1_texture)
            player_1_texture = IMG_LoadTexture(renderer,
                    "./textures/tank-b_logo.png");
        SDL_RenderCopy(renderer, player_1_texture, NULL, &player_logo);
    }
    else
    {
        if (!player_2_texture)
            player_2_texture = IMG_LoadTexture(renderer,
                    "./textures/tank-g_logo.png");
        SDL_RenderCopy(renderer, player_2_texture, NULL, &player_logo);
    }
    iter_full(nb_heart, renderer, &w_cur);
    iter_empty(nb_heart, renderer, &w_cur);
}

void update_gui(SDL_Renderer *renderer, struct GameContext *GC)
{
    print_heart(renderer, GC->player1, 0.05, 1);
    print_heart(renderer, GC->player2, 0.75, 2);
}
