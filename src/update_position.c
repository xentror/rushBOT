#include <math.h>
#include <stdlib.h>

#include "context.h"
#include "update.h"

static enum floor_type get_floor(struct map *M, float x, float y)
{
    size_t nx = floor(x);
    size_t ny = floor(y);
    return M->table[nx][ny]->type;
}

static int touch_the_wall(struct map *M, struct vector2 *position)
{
    return get_floor(M, position->x, position->y) == BLOCK;
}

static int in_the_lava(struct map *M, struct vector2 *position)
{
    return get_floor(M, position->x, position->y) == LAVA;
}

void destroy_bullet(struct GameContext *GC, int i)
{
    for (int j = i; j < GC->nb_bullets - 1; j++)
        GC->bullets[i] = GC->bullets[i + 1];
    free(GC->bullets[GC->nb_bullets - 1]);
    GC->nb_bullets -= 1;
    GC->bullets = realloc(GC->bullets, sizeof(struct bullet *) * GC->nb_bullets);
}

static void update_bullets_position(struct GameContext *GC)
{
    for (int i = 0; i < GC->nb_bullets; i++)
    {
        if (!touch_the_wall(GC->map, GC->bullets[i]->position))
        {
            GC->bullets[i]->position->x += GC->bullets[i]->direction->x;
            GC->bullets[i]->position->y += GC->bullets[i]->direction->y;
        }
        else
        {
            if (GC->bullets[i]->nb_rebounds > 3)
                destroy_bullet(GC, i);
            GC->bullets[i]->nb_rebounds += 1;
        }
    }
}

static void update_AI_position(struct GameContext *GC)
{
    for (int i = 0; i < GC->nb_enemies; i++)
    {
        if (!touch_the_wall(GC->map, GC->enemies[i]->position) &&
            !in_the_lava(GC->map, GC->enemies[i]->position))
        {
            GC->enemies[i]->position->x += GC->enemies[i]->direction->x;
            GC->enemies[i]->position->y += GC->enemies[i]->direction->y;
        }
    }
}

void update_position(struct GameContext *GC)
{
    update_bullets_position(GC);
    update_AI_position(GC);
}
