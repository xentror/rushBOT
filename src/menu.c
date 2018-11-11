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

    SDL_Surface *s = SDL_CreateRGBSurface(0, w/5, h/5, 200, 0, 10, 50, 0);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, s);



    SDL_Rect start;
    start.x = w/2;
    start.y = h/2;
    start.w = w/5;
    start.h = h/5;
    SDL_RenderCopy(renderer, texture, NULL, &start);

    SDL_Rect quit;
    quit.x = w/2;
    quit.y = 2*h/3;
    quit.w = w/5;
    quit.h = h/5;
    SDL_RenderCopy(renderer, texture, NULL, &quit);

    SDL_RenderPresent(renderer);

    while(1)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            int mouse_x;
            int mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            if(event.type == SDL_MOUSEBUTTONDOWN && mouse_x > w/2 &&
              mouse_x < w/2 + w/5 && mouse_y > h/2 && mouse_y < h/2 + h/5)
                return 1;
            if(event.type == SDL_MOUSEBUTTONDOWN && mouse_x > w/2 &&
              mouse_x < w/2 + w/5 && mouse_y > 2*h/3 && mouse_y < 2*h/3 + h/h)
                return 0;
        }
    }
}
