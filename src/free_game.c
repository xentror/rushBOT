#include <stdlib.h>

#include "map.h"
#include "context.h"

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
    free(GC->player2);
}

void free_game(struct GameContext *GC)
{
    free_tanks(GC);
    free_bullets(GC);
    free_players(GC);
    free_map(GC->map);
}
