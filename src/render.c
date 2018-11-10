#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

int main(void)
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("TANK BATTLE !!!!",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1024,
            720,
            SDL_WINDOW_OPENGL);
    
    if (window == NULL) 
    {
        printf("could not create window\n");
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    //SDL_SetRenderDrawColor(renderer,159, 87, 43, 255);
    //SDL_RenderClear(renderer);
    //SDL_RenderPresent(renderer);

    int w, h;
    SDL_Texture *img = IMG_LoadTexture(renderer, "./textures/ground.png");
    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    SDL_Rect textr;
    textr.x = 0;
    textr.y = 0;
    textr.w = w / 2;
    textr.h = h / 2;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, img, NULL, &textr);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
