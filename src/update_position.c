#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "context.h"
#include "update.h"

static enum floor_type get_floor(struct map *M, float x, float y)
{
    size_t nx = floor(x + 0.5);
    size_t ny = floor(y + 0.5);
    return M->table[ny][nx]->type;
}

static int touch_the_wall(struct map *M, struct vector2 *position)
{
    return get_floor(M, position->x, position->y) == BLOCK;
}

static int in_the_lava(struct map *M, struct vector2 *position)
{
    return get_floor(M, position->x, position->y) == LAVA;
}

static void rebound_bullet(struct bullet *B)
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

static void destroy_bullet(struct GameContext *GC, int i)
{
    struct bullet *tmp = GC->bullets[i];
    for (int j = i; j < GC->nb_bullets - 1; j++)
        GC->bullets[j] = GC->bullets[j + 1];
    free(tmp->direction);
    free(tmp->position);
    printf("addess tmp %p\n",(void*)tmp);
    free(tmp);
    GC->nb_bullets -= 1;
    GC->bullets = realloc(GC->bullets, sizeof(struct bullet *) *
            GC->nb_bullets);
    printf("---------------------------------------------------free %d\n", i);
}

static void free_destroyed_bullets(struct GameContext *GC)
{
    int i = 0;
    while (i < GC->nb_bullets)
    {
        if (GC->bullets[i]->to_destroy)
            destroy_bullet(GC, i);
        else
            i++;
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
            if (GC->bullets[i]->nb_rebounds >= 0)
            {
                printf("destroy bullet \n");
                GC->bullets[i]->to_destroy = 1;
            }
            else
            {
                printf("rebondis \n");
                //rebound_bullet(GC->bullets[i]);
                GC->bullets[i]->nb_rebounds += 1;
            }
        }
    }
    for (int i = 0; i < GC->nb_bullets; i++)
        printf("n°%d: todestroy:%d\n", i, GC->bullets[i]->to_destroy);
    free_destroyed_bullets(GC);
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
    printf("player1: (%f, %f)\n", GC->player1->position->x, GC->player1->position->y);
    printf("direction (%f, %f)\n", GC->player1->direction->x, GC->player1->direction->y);
    struct hitbox *hb = GC->player1->hbox;
    printf("Hitbox:\n");
    printf("v1 x=%f y=%f | v2 x=%f y=%f\nv3 x=%f y=%f | v4 x=%f y=%f\n", 
            hb->v1->x, hb->v1->y, hb->v2->x, hb->v2->y, hb->v3->x, hb->v3->y,
            hb->v4->x, hb->v4->y);
    update_bullets_position(GC);
    update_AI_position(GC);
}
