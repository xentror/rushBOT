#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "context.h"
#include "update.h"

static void go_forward(struct tank *tank)
{
    tank->position->x += 0.02 * tank->direction->x;
    tank->position->y -= 0.02 * tank->direction->y;
}

static void go_back(struct tank *tank)
{
    tank->position->x -= 0.02 * tank->direction->x;
    tank->position->y += 0.02 * tank->direction->y;
}

static void normalize(struct vector2 *vect)
{
    double deno = sqrt(pow(vect->x, 2) + pow(vect->y, 2));
    vect->x = vect->x / deno;
    vect->y = vect->y / deno;
}

static void rotate_left(struct tank *tank)
{
    normalize(tank->direction);
    float x = tank->direction->x;
    float y = tank->direction->y;
    double angle = 1.0 * (M_PI / 180.0);
    tank->direction->x = x * cos(angle) - y * sin(angle);
    tank->direction->y = x * sin(angle) + y * cos(angle);
    normalize(tank->direction);
}

static void rotate_right(struct tank *tank)
{
    normalize(tank->direction);
    float x = tank->direction->x;
    float y = tank->direction->y;
    double angle = -1.0 * (M_PI / 180.0);
    tank->direction->x = x * cos(angle) - y * sin(angle);
    tank->direction->y = x * sin(angle) + y * cos(angle);
}

static struct bullet *create_bullet(struct tank *tank)
{
    struct bullet *B = malloc(sizeof(struct bullet));
    B->position = malloc(sizeof(struct vector2));
    B->direction = malloc(sizeof(struct vector2));
    B->position->x = tank->position->x + tank->direction->x / 2;
    B->position->y = tank->position->y + tank->direction->y / 2;
    B->direction->x = tank->direction->x;
    B->direction->y = tank->direction->y;
    B->damage = 10;
    B->speed = 3;
    B->type = ENORMOUS;
    B->nb_rebounds = 0;

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
        tank->is_shoting = 0;
    }
}

void update_input(struct GameContext *GC)
{
    struct tank *p1 = GC->player1;
    struct tank *p2 = GC->player2;
    shot(GC, p1);
    shot(GC, p2);
    switch(p1->event)
    {
        case LEFT:
            rotate_left(p1);
            break;
        case RIGHT:
            rotate_right(p1);
            break;
        case FORWARD:
            go_forward(p1);
            break;
        case BACK:
            go_back(p1);
            break;
        case NOTHING:
        default:
            break;
    }
    switch(p2->event)
    {
        case LEFT:
            rotate_left(p2);
            break;
        case RIGHT:
            rotate_right(p2);
            break;
        case FORWARD:
            go_forward(p2);
            break;
        case BACK:
            go_back(p2);
            break;
        case NOTHING:
        default:
            break;

    }
}
