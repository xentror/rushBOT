#include <math.h>
#include <stdlib.h>

#include "context.h"
#include "update.h"

static enum floor_type get_floor(struct map *M, float x, float y)
{
    x = x < 0.0 ? 0.0 : x;
    x = x > M->width ? M->width - 0.01: x;
    y = y < 0.0 ? 0.0 : y;
    y = y > M->height ? M->height - 0.01 : y;
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
    angle = angle * (180 / M_PI);

    float x = B->position->x - floor(B->position->x);
    float y = B->position->y - floor(B->position->y);

    if (x > 0.5)
        x = 1 - x;
    if (y > 0.5)
        y = 1 - y;

    if (angle <= 0 && angle >= -90)
    {
        if (x < y)
            B->direction->y *= -1;
        else
            B->direction->x *= -1;
    }

    if (angle >= 0 && angle <= 90)
    {
        // hit by the left
        if (x < y)
            B->direction->y *= -1;
        else
            B->direction->x *= -1;
    }

    if (angle >= 90 && angle <= 180)
    {
        if (x < y)
            B->direction->y *= -1;
        else
            B->direction->x *= -1;
    }

    if (angle <= -90 && angle >= -180)
    {
        if (x < y)
            B->direction->y *= -1;
        else
            B->direction->x *= -1;
    }
    B->position->x += B->direction->x * B->speed * 10;
    B->position->y -= B->direction->y * B->speed * 10;
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

            for (int j = 0; j < GC->nb_enemies; j++)
                touch_tank(GC->enemies[j], GC->bullets[i]);
        }
        else
        {
            if (GC->bullets[i]->nb_rebounds > 2)
            {
                GC->bullets[i]->to_destroy = 1;
            }
            else
            {
                rebound_bullet(GC->bullets[i]);
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
    if (in_the_lava(GC->map, GC->player1->position))
        GC->player1->health--;
    if (in_the_lava(GC->map, GC->player2->position))
        GC->player2->health--;
    update_bullets_position(GC);
    update_AI_position(GC);
}
