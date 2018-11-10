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
    gameInit(&game, argv[1]);
    SDL_Window *window = window_init(game.map);
    SDL_Renderer *renderer = render_map(game.map, window);
    render_tanks(&game, renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    while (game.isPlaying)
    {
        enum event event = get_input();
        update(&game, event);

        render_bullets(&game, renderer);
        SDL_RenderPresent(renderer);
    }
    free_game(&game);
    return 0;
}
