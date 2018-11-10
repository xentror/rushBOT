#include <math.h>
#include <stdlib.h>

#include "context.h"
#include "update.h"

static void go_forward(struct tank *tank)
{
    tank->position->x += tank->direction->x;
    tank->position->y += tank->direction->y;
}

static void go_back(struct tank *tank)
{
    tank->position->x -= tank->direction->x;
    tank->position->y -= tank->direction->y;
}

static void rotate_left(struct tank *tank)
{
    double angle = atan2(tank->direction->x, tank->direction->y);
    angle += M_PI/16;
    tank->direction->x = cos(angle);
    tank->direction->y = sin(angle);
}

static void rotate_right(struct tank *tank)
{
    double angle = atan2(tank->direction->x, tank->direction->y);
    angle -= M_PI/16;
    tank->direction->x = cos(angle);
    tank->direction->y = sin(angle);
}

static struct bullet *create_bullet(struct tank *tank)
{
    struct bullet *B = malloc(sizeof(struct bullet));
    B->position->x = tank->position->x + tank->direction->x / 2;
    B->position->y = tank->position->y + tank->direction->y / 2;
    B->direction->x = tank->direction->x;
    B->direction->y = tank->direction->y;
    B->damage = 10;
    B->speed = 3;
    B->type = ENORMOUS;

    return B;
}

void shot(struct GameContext *GC, struct tank *tank)
{
    if (tank->is_shoting)
    {
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
