#include "update.h"
#include "context.h"

#include <stdio.h>
static void update_AI_behaviour(struct GameContext *GC)
{
    for (int i = 0; i < GC->nb_enemies; i++)
    {
        if (!touch_the_wall(GC->map, GC->enemies[i]->position) &&
            !in_the_lava(GC->map, GC->enemies[i]->position))
        {
            printf("SINCE I SHOT:%d\n", GC->enemies[i]->since_i_shot);
            GC->enemies[i]->since_i_shot += 1;
            if (GC->enemies[i]->since_i_shot > 100)
            {
              printf("SHOOOOT\n");
                GC->enemies[i]->since_i_shot = 0;
                GC->enemies[i]->is_shoting = 1;
                shot(GC, GC->enemies[i]);
            }
        }
        else
        {
            rotate(GC->enemies[i], M_PI);
            move(GC->enemies[i], GC, 1);
        }
    }
}

void update(struct GameContext *GC)
{
    update_input(GC);
    update_position(GC);
    update_AI_behaviour(GC);
}
