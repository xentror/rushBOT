#include "context.h"
#include "render.h"

int menu(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);

    SDL_Texture *img_texture = IMG_LoadTexture(renderer, "./textures/background_menu.jpg");
    SDL_RenderCopy(renderer, img_texture, NULL, NULL);

    int w;
    int h;

    SDL_GetRendererOutputSize(renderer, &w, &h);


    SDL_Texture *img_texture_start = IMG_LoadTexture(renderer, "./textures/start_game.jpg");
    SDL_Rect start;
    start.x = 2*w/3;
    start.y = h/2;
    start.w = w/5;
    start.h = h/10;
    SDL_RenderCopy(renderer, img_texture_start, NULL, &start);


    SDL_Texture *img_texture_quit = IMG_LoadTexture(renderer, "./textures/quit.jpg");
    SDL_Rect quit;
    quit.x = 2*w/3;
    quit.y = 2*h/3;
    quit.w = w/5;
    quit.h = h/10;
    SDL_RenderCopy(renderer, img_texture_quit, NULL, &quit);

    SDL_RenderPresent(renderer);

    while(1)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            int mouse_x;
            int mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            if(event.type == SDL_MOUSEBUTTONDOWN && mouse_x > 2*w/3 &&
              mouse_x < 2*w/3 + w/5 && mouse_y > h/2 && mouse_y < h/2 + h/10)
                return 1;
            if(event.type == SDL_MOUSEBUTTONDOWN && mouse_x > 2*w/3 &&
              mouse_x < 2*w/3 + w/5 && mouse_y > 2*h/3 && mouse_y < 2*h/3 + h/10)
                return 0;
        }
    }
}
