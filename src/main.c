#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "update.h"
#include "context.h"
#include "render.h"


struct GameContext game;

int main(int argc, char *argv[])
{
    if (argc != 2)
        errx(1, "Please enter path for map like: ./toto <path>");
    gameInit(&game, argv[1]);
    SDL_Window *window = window_init(game.map);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED);
    render_map(game.map, renderer);
    render_tanks(&game, renderer);
    SDL_RenderPresent(renderer);

    game.player1->position->x = 1;
    game.player1->position->y = 1;

    while (game.isPlaying)
    {
        get_input(&game);
        update(&game);
        render_map(game.map, renderer);
        render_tanks(&game, renderer);
        SDL_RenderPresent(renderer);

        render_bullets(&game, renderer);
        SDL_RenderPresent(renderer);
    }

    free_game(&game);
    SDL_Delay(3000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
