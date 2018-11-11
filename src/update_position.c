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

int touch_the_wall(struct map *M, struct vector2 *position)
{
    return get_floor(M, position->x, position->y) == BLOCK;
}

int in_the_lava(struct map *M, struct vector2 *position)
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
    free(tmp);
    GC->nb_bullets -= 1;
    GC->bullets = realloc(GC->bullets, sizeof(struct bullet *) *
            GC->nb_bullets);
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

static void touch_tank(struct tank *tank, struct bullet *bullet)
{
    struct vector2 *pos = bullet->position;
    if (tank->t_id != bullet->t_id)
    {
        if (pos->y >= tank->hbox->v1->y && pos->y <= tank->hbox->v2->y)
        {
            if (pos->x >= tank->hbox->v1->x && pos->x <= tank->hbox->v4->x)
            {
                tank->health -= bullet->damage;
                bullet->to_destroy = 1;
            }
        }
    }
}

static void update_bullets_position(struct GameContext *GC)
{
    for (int i = 0; i < GC->nb_bullets; i++)
    {
        if (!touch_the_wall(GC->map, GC->bullets[i]->position))
        {
            GC->bullets[i]->position->x += GC->bullets[i]->direction->x *
                GC->bullets[i]->speed;
            GC->bullets[i]->position->y -= GC->bullets[i]->direction->y *
                GC->bullets[i]->speed;
            touch_tank(GC->player1, GC->bullets[i]);
            touch_tank(GC->player2, GC->bullets[i]);
            /*printf("Player1 health: %d\n", GC->player1->health);
              printf("    v1.x=%f v1.y=%f | v2.x=%f v2.y=%f\n",
              GC->player1->hbox->v1->x, GC->player1->hbox->v1->y,
              GC->player1->hbox->v2->x, GC->player1->hbox->v2->y);
              printf("    v3.x=%f v3.y=%f | v4.x=%f v4.y=%f\n",
              GC->player1->hbox->v3->x, GC->player1->hbox->v3->y,
              GC->player1->hbox->v4->x, GC->player1->hbox->v4->y);
              printf("Player2 health: %d\n", GC->player2->health);
              printf("    v1.x=%f v1.y=%f | v2.x=%f v2.y=%f\n",
              GC->player2->hbox->v1->x, GC->player2->hbox->v1->y,
              GC->player2->hbox->v2->x, GC->player2->hbox->v2->y);
              printf("    v3.x=%f v3.y=%f | v4.x=%f v4.y=%f\n",
              GC->player2->hbox->v3->x, GC->player2->hbox->v3->y,
              GC->player2->hbox->v4->x, GC->player2->hbox->v4->y);*/


            for (int j = 0; j < GC->nb_enemies; j++)
                touch_tank(GC->enemies[j], GC->bullets[i]);
        }
        else
        {
            if (GC->bullets[i]->nb_rebounds >= 0)
                GC->bullets[i]->to_destroy = 1;
            else
            {
                //rebound_bullet(GC->bullets[i]);
                GC->bullets[i]->nb_rebounds += 1;
            }
        }
    }
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
    update_bullets_position(GC);
    update_AI_position(GC);
}
