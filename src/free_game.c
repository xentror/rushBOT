#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "map.h"
#include "context.h"
#include "update.h"

extern SDL_Texture *full_heart_texture;
extern SDL_Texture *empty_heart_texture;
extern SDL_Texture *player_1_texture;
extern SDL_Texture *player_2_texture;

static void free_tanks(struct GameContext *GC)
{

    for (int i = 0; i < GC->nb_enemies; i++)
    {
        free(GC->enemies[i]->position);
        free(GC->enemies[i]->direction);
        free(GC->enemies[i]);
    }
    free(GC->enemies);
}

static void free_bullets(struct GameContext *GC)
{
    if (!GC)
        return;
    for (int i = 0; i < GC->nb_bullets; i++)
    {
        free(GC->bullets[i]->position);
        free(GC->bullets[i]->direction);
        free(GC->bullets[i]);
    }
    free(GC->bullets);
}

static void free_players(struct GameContext *GC)
{
    free(GC->player1->position);
    free(GC->player1->direction);
    free(GC->player1);
    free(GC->player2->position);
    free(GC->player2->direction);
    free(GC->player2);
}

void free_game(struct GameContext *GC)
{
    GC->nb_bullets = 0;
    GC->nb_enemies = 0;

    free_tanks(GC);
    free_bullets(NULL);
    free_players(GC);
    free_map(GC->map);
}
