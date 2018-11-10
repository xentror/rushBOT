#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "update.h"
#include "context.h"
#include "render.h"
#include "get_input.h"

struct GameContext game;

int main(int argc, char *argv[])
{
    if (argc != 2)
        errx(1, "Please enter path for map like: ./toto <path>");
    SDL_Event event;
    gameInit(&game, argv[1]);
    SDL_Window *window = window_init(game.map);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED);
    render_map(game.map, renderer);
    render_tanks(&game, renderer);
    SDL_RenderPresent(renderer);

    int quit = 0;
    while (!quit)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_LEFT:  game.player2->position->x -= 0.1; break;
                    case SDLK_RIGHT: game.player2->position->x += 0.1; break;
                    case SDLK_UP:    game.player2->position->y -= 0.1; break;
                    case SDLK_DOWN:  game.player2->position->y += 0.1; break;
                    case SDLK_p:  quit = 1; break;
                }
                break;
        }
        render_map(game.map, renderer);
        render_tanks(&game, renderer);
        SDL_RenderPresent(renderer);

        render_bullets(&game, renderer);
        SDL_RenderPresent(renderer);
    }

    free_game(&game);
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
