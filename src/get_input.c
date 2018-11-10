#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "context.h"
#include "update.h"

void get_input(struct GameContext *GC)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    SDL_Keycode key = event.key.keysym.sym;
    if (event.type == SDL_KEYDOWN)
    {
        switch (key)
        {
            case SDLK_UP: GC->player1->event = FORWARD; return;
            case SDLK_DOWN: GC->player1->event = BACK; return;
            case SDLK_LEFT: GC->player1->event = LEFT; return;
            case SDLK_RIGHT: GC->player1->event = RIGHT; return;
            case SDLK_KP_0: GC->player1->is_shoting = 1; return;
            case SDLK_w: GC->player2->event = FORWARD; return;
            case SDLK_s: GC->player2->event = BACK; return;
            case SDLK_a: GC->player2->event = LEFT; return;
            case SDLK_d: GC->player2->event = RIGHT; return;
            case SDLK_SPACE: GC->player2->is_shoting = 1; return;
            case SDLK_ESCAPE: GC->isPlaying = 0;return;
            default: return;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        switch (key)
        {
            case SDLK_UP: GC->player1->event = NOTHING; return;
            case SDLK_DOWN: GC->player1->event = NOTHING; return;
            case SDLK_LEFT: GC->player1->event = NOTHING; return;
            case SDLK_RIGHT: GC->player1->event = NOTHING; return;
            case SDLK_KP_0: GC->player1->is_shoting = 0; return;
            case SDLK_w: GC->player2->event = NOTHING; return;
            case SDLK_s: GC->player2->event = NOTHING; return;
            case SDLK_a: GC->player2->event = NOTHING; return;
            case SDLK_d: GC->player2->event = NOTHING; return;
            case SDLK_SPACE: GC->player2->is_shoting = 0; return;
            case SDLK_ESCAPE: GC->isPlaying = 0;return;
            default: return;
        }

    }
    else
        return;
}
