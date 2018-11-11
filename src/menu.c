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


    SDL_Texture *img_texture_start_1 = IMG_LoadTexture(renderer, "./textures/play_1.jpg");
    SDL_Rect start;
    start.x = 3*w/5;
    start.y = h/2;
    start.w = w/7;
    start.h = h/7;
    SDL_RenderCopy(renderer, img_texture_start_1, NULL, &start);

    SDL_Texture *img_texture_start_2 = IMG_LoadTexture(renderer, "./textures/play_2.jpg");
    SDL_Rect start2;
    start2.x = 3*w/5 + w/5;
    start2.y = h/2;
    start2.w = w/7;
    start2.h = h/7;
    SDL_RenderCopy(renderer, img_texture_start_2, NULL, &start2);


    SDL_Texture *img_texture_quit = IMG_LoadTexture(renderer, "./textures/quit.jpg");
    SDL_Rect quit;
    quit.x = 2*w/3;
    quit.y = 3*h/4;
    quit.w = w/10;
    quit.h = h/20;
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
            if(event.type == SDL_MOUSEBUTTONDOWN && mouse_x > 3*w/5 &&
              mouse_x < 3*w/5 + w/7 && mouse_y > h/2 && mouse_y < h/2 + h/7)
                return 1;
            if(event.type == SDL_MOUSEBUTTONDOWN && mouse_x > 3*w/5 +w/5 &&
              mouse_x < 3*w/5 + w/5 + w/7 && mouse_y > h/2 && mouse_y < h/2 + h/7)
                return 2;
            if(event.type == SDL_MOUSEBUTTONDOWN && mouse_x > 2*w/3 &&
              mouse_x < 2*w/3 + w/10 && mouse_y > 3*h/4 && mouse_y < 3*h/4 + h/20)
                return 0;
        }
    }
}
