#include <math.h>
#include <stdlib.h>

#include "context.h"
#include "update.h"

static void go_forward(struct tank *T)
{
    T->position->x += T->direction->x;
    T->position->y += T->direction->y;
}

static void go_back(struct tank *T)
{
    T->position->x -= T->direction->x;
    T->position->y -= T->direction->y;
}

static void rotate_left(struct tank *T)
{
    double angle = atan2(T->direction->x, T->direction->y);
    angle += M_PI/16;
    T->direction->x = cos(angle);
    T->direction->y = sin(angle);
}

static void rotate_right(struct tank *T)
{
    double angle = atan2(T->direction->x, T->direction->y);
    angle -= M_PI/16;
    T->direction->x = cos(angle);
    T->direction->y = sin(angle);
}

static struct bullet *create_bullet(struct tank *T)
{
    struct bullet *B = malloc(sizeof(struct bullet));
    B->position->x = T->position->x + T->direction->x / 2;
    B->position->y = T->position->y + T->direction->y / 2;
    B->direction->x = T->direction->x;
    B->direction->y = T->direction->y;
    B->damage = 10;
    B->speed = 3;
    B->type = ENORMOUS;

    return B;
}

static void shot(struct GameContext *GC, struct tank *T)
{
    GC->nb_bullets += 1;
    GC->bullets = realloc(GC->bullets, sizeof(struct bullet *) * GC->nb_bullets);
    GC->bullets[GC->nb_bullets] = create_bullet(T);
}

void update_input(struct GameContext *GC, enum event event)
{
    struct tank *p1 = GC->player1;
    struct tank *p2 = GC->player2;

    switch(event)
    {
        case J1_LEFT:
            rotate_left(p1);
            break;
        case J1_RIGHT:
            rotate_right(p1);
            break;
        case J1_FORWARD:
            go_forward(p1);
            break;
        case J1_BACK:
            go_back(p1);
            break;
        case J1_SHOT:
            shot(GC, p1);
            break;
        case J2_LEFT:
            rotate_left(p2);
            break;
        case J2_RIGHT:
            rotate_right(p2);
            break;
        case J2_FORWARD:
            go_forward(p2);
            break;
        case J2_BACK:
            go_back(p2);
            break;
        case J2_SHOT:
            shot(GC, p2);
            break;
        case QUIT:
            break;
        default:
            break;
    }
}
