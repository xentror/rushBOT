#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "update.h"
#include "context.h"
#include "render.h"


struct GameContext game;

int main(int argc, char *argv[])
{
    if (argc != 1)
        errx(1, "Please enter path for map like: ./main");

    SDL_Window *window = window_init();
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED);

    int res;
    while(res = menu(renderer))
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

      free_game(&game);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
