#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "context.h"
#include "render.h"

struct GameContext game;

int main(int argc, char *argv[])
{
    if (argc != 2)
        errx(1, "Please enter path for map like: ./toto <path>");
    gameInit(&game, argv[1]);
    SDL_Window *window = window_init(game.map);
    render_map(game.map, window);
    /*while (game.isPlaying)
    {
        printf("tamerelapute\n");
    }*/
    SDL_Delay(30000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
