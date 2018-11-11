#include "update.h"
#include "context.h"
#include <stdio.h>
static void update_AI_behaviour(struct GameContext *GC)
{
    for (int i = 0; i < GC->nb_enemies; i++)
    {
        GC->enemies[i]->since_i_shot += 1;
        if (GC->enemies[i]->since_i_shot > 300)
        {
            GC->enemies[i]->since_i_shot = 0;
            shot(GC, GC->enemies[i]);
        }
    }
}

void update(struct GameContext *GC)
{
    update_input(GC);
    update_position(GC);
    update_AI_behaviour(GC);
}
