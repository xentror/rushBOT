#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "context.h"
#include "update.h"

static void go(struct tank *tank, int w, int h, int neg)
{
    tank->position->x = tank->position->x + neg * (0.02 * tank->direction->x);
    tank->position->y = tank->position->y - neg * (0.02 * tank->direction->y);
    float x = tank->position->x;
    float y = tank->position->y;
    if (x > w)
        tank->position->x = 0.0;
    else if (x < 0.0)
        tank->position->x = w;
    if (y > h)
        tank->position->y = 0.0;
    else if (y < 0.0)
        tank->position->y = h;
}

static void normalize(struct vector2 *vect)
{
    double deno = sqrt(pow(vect->x, 2) + pow(vect->y, 2));
    vect->x = vect->x / deno;
    vect->y = vect->y / deno;
}

static void rotate(struct tank *tank, int neg)
{
    normalize(tank->direction);
    float x = tank->direction->x;
    float y = tank->direction->y;
    double angle = neg * 1.0 * (M_PI / 180.0);
    tank->direction->x = x * cos(angle) - y * sin(angle);
    tank->direction->y = x * sin(angle) + y * cos(angle);
    normalize(tank->direction);
}

static struct bullet *create_bullet(struct tank *tank)
{
    struct bullet *B = malloc(sizeof(struct bullet));
    B->position = malloc(sizeof(struct vector2));
    B->direction = malloc(sizeof(struct vector2));
    B->position->x = tank->position->x;
    B->position->y = tank->position->y;
    B->direction->x = tank->direction->x;
    B->direction->y = tank->direction->y;
    B->damage = 10;
    B->speed = 0.05;
    B->type = ENORMOUS;
    B->nb_rebounds = 0;
    B->to_destroy = 0;

    return B;
}

void shot(struct GameContext *GC, struct tank *tank)
{
    if (tank->is_shoting)
    {
        printf("shot !\n");
        GC->bullets = realloc(GC->bullets, sizeof(struct bullet *)
                * GC->nb_bullets + 1);
        GC->bullets[GC->nb_bullets] = create_bullet(tank);
        GC->nb_bullets += 1;
        tank->is_shoting = 0;
    }
}

void update_input(struct GameContext *GC)
{
    struct tank *p1 = GC->player1;
    struct tank *p2 = GC->player2;
    int h = GC->map->width;
    int w = GC->map->height;
    shot(GC, p1);
    shot(GC, p2);
    switch(p1->event)
    {
        case LEFT:
            rotate(p1, 1);
            break;
        case RIGHT:
            rotate(p1, -1);
            break;
        case FORWARD:
            go(p1, w, h, 1);
            break;
        case BACK:
            go(p1, w, h, -1);
            break;
        case NOTHING:
        default:
            break;
    }
    switch(p2->event)
    {
        case LEFT:
            rotate(p2, 1);
            break;
        case RIGHT:
            rotate(p2, -1);
            break;
        case FORWARD:
            go(p2, w, h, 1);
            break;
        case BACK:
            go(p2, w, h, -1);
            break;
        case NOTHING:
        default:
            break;
    }
}
