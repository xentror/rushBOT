#include "context.h"
#include "render.h"

static void print_play1(SDL_Renderer *renderer, int w, int h,
    SDL_Texture *texture)
{
    SDL_Rect start;
    start.x = 3*w/5;
    start.y = h/2;
    start.w = w/7;
    start.h = h/7;
    SDL_RenderCopy(renderer, texture, NULL, &start);
}

static void print_play2(SDL_Renderer *renderer, int w, int h,
    SDL_Texture *texture)
{
    SDL_Rect start2;
    start2.x = 3*w/5 + w/5;
    start2.y = h/2;
    start2.w = w/7;
    start2.h = h/7;
    SDL_RenderCopy(renderer, texture, NULL, &start2);
}

static void print_quit(SDL_Renderer *renderer, int w, int h,
    SDL_Texture *texture)
{
    SDL_Rect quit;
    quit.x = 2*w/3;
    quit.y = 3*h/4;
    quit.w = w/10;
    quit.h = h/20;
    SDL_RenderCopy(renderer, texture, NULL, &quit);
}

static int wait_to_click(int w, int h)
{
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
            mouse_x < 3*w/5 + w/5 + w/7 &&
            mouse_y > h/2 && mouse_y < h/2 + h/7)
                return 2;
            if(event.type == SDL_MOUSEBUTTONDOWN && mouse_x > 2*w/3 &&
            mouse_x < 2*w/3 + w/10 && mouse_y > 3*h/4
            && mouse_y < 3*h/4 + h/20)
                return 0;
        }
    }
}

int menu(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    SDL_Texture *img_texture =
    IMG_LoadTexture(renderer, "./textures/background_menu.jpg");
    SDL_RenderCopy(renderer, img_texture, NULL, NULL);
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);

    SDL_Texture *img_texture_start_1 =
        IMG_LoadTexture(renderer, "./textures/play_1.jpg");
    print_play1(renderer, w, h, img_texture_start_1);
    SDL_Texture *img_texture_start_2 =
        IMG_LoadTexture(renderer, "./textures/play_2.jpg");
    print_play2(renderer, w, h, img_texture_start_2);
    SDL_Texture *img_texture_quit =
        IMG_LoadTexture(renderer, "./textures/quit.jpg");
    print_quit(renderer, w, h, img_texture_quit);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(img_texture);
    SDL_DestroyTexture(img_texture_start_1);
    SDL_DestroyTexture(img_texture_start_2);
    SDL_DestroyTexture(img_texture_quit);
    return wait_to_click(w, h);
}
