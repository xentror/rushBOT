#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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

void rebound_bullet(struct bullet *B)
{
    double angle = atan2(B->direction->x, B->direction->y);

    // hit by the left
    if (B->position->x - floor(B->position->x) < 0.5
        && angle <= M_PI / 2 && angle >= -M_PI / 2)
    {


    }

    // hit by the right
    if (B->position->x - floor(B->position->x) >= 0.5
        && ((angle >= M_PI / 2 && angle <= M_PI) ||
        (angle >= -M_PI && angle <= -M_PI / 2)))
    {


    }

    // hit by the top
    if (B->position->y - floor(B->position->y) < 0.5
        && angle <= 0 && angle >= -M_PI)
    {


    }

    // hit by the bottom
    if (B->position->y - floor(B->position->y) < 0.5
        && angle <= 0 && angle >= -M_PI)
    {


    }
}

static void update_bullets_position(struct GameContext *GC)
{
    for (int i = 0; i < GC->nb_bullets; i++)
    {
        printf("bullets n°%d: (%f, %f)\n", i, GC->bullets[i]->position->x,
                GC->bullets[i]->position->y);
        printf("direction (%f, %f)\n", GC->bullets[i]->direction->x,
                GC->bullets[i]->direction->y);
        if (!touch_the_wall(GC->map, GC->bullets[i]->position))
        {
            printf("update pos \n");
            GC->bullets[i]->position->x += GC->bullets[i]->direction->x *
                GC->bullets[i]->speed;
            GC->bullets[i]->position->y -= GC->bullets[i]->direction->y *
                GC->bullets[i]->speed;
        }
        else
        {
            if (GC->bullets[i]->nb_rebounds > 3)
            {
                printf("destroy bullet \n");
                destroy_bullet(GC, i);
            }
            else
            {
                printf("rebondis \n");
                //rebound_bullet(GC->bullets[i]);
                GC->bullets[i]->nb_rebounds += 1;
            }
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
            GC->enemies[i]->position->x += GC->enemies[i]->direction->x * 0.01;
            GC->enemies[i]->position->y += GC->enemies[i]->direction->y * 0.01;
        }
    }
}

void update_position(struct GameContext *GC)
{
    printf("player2: (%f, %f)\n", GC->player2->position->x, GC->player2->position->y);
    printf("direction (%f, %f)\n", GC->player2->direction->x, GC->player2->direction->y);
    update_bullets_position(GC);
    update_AI_position(GC);
}
