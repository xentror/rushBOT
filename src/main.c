#include <stdlib.h>
#include <err.h>
#include "update.h"
#include "context.h"
#include "render.h"


struct GameContext game;

int main(void)
{
    SDL_Window *window = window_init();
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED);

    int res;
    while((res = (menu(renderer))))
    {
        if (res == 1)
            gameInit(&game, "maps/mossoul");
        else
            gameInit(&game, "maps/shastri_nagar");

        while (game.isPlaying)
        {
            get_input(&game);
            update(&game);

            render_map(game.map, renderer);
            render_tanks(&game, renderer);
            render_bullets(&game, renderer);
            update_gui(renderer, &game);
            SDL_RenderPresent(renderer);
        }
        char *path = "./textures/player1.png";
        if (game.winner == 0)
            path = "./textures/player2.png";
        print_winner(renderer, path);
        SDL_Delay(2000);
        free_game(&game);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
