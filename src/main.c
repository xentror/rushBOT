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
    render_map(game.map, window);
    while (game.isPlaying)
    {
        enum event event = get_input();
        update(&game, event);

        render_map(game.map, window);
        render_tanks(game, window);
        render_bullets(game, windows);
        
        printf("running tamerelapute\n");
    }
    free_game();
    SDL_Delay(30000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
