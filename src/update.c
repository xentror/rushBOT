#include "update.h"
#include "context.h"

static void update_AI_behaviour(struct GameContext *GC)
{
    for (int i = 0; i < GC->nb_enemies; i++)
    {
        GC->enemies[i]->since_i_shot += 1;
        if (GC->enemies[i]->since_i_shot > 100)
        {
            GC->enemies[i]->since_i_shot = 0;
            shot(GC, GC->enemies[i]);
        }
    }

    for (int i = 0; i < GC->nb_bullets; i++)
    {
        struct bullet *B = GC->bullets[i];
        B->position->x += B->direction->x * B->speed;
        B->position->y += B->direction->y * B->speed;
    }
}

void update(struct GameContext *GC)
{
    update_input(GC);
    update_position(GC);
    update_AI_behaviour(GC);
}
