#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "context.h"
#include "update.h"

static int checkVector2(struct vector2 *vect, float move_x, float move_y,
        struct GameContext *GC)
{
    float new_x = vect->x + move_x;
    int tmp_x = new_x;
    float new_y = vect->y - move_y;
    int tmp_y = new_y;
    if (GC->map->table[tmp_y][tmp_x]->type == BLOCK)
        return 0;
    vect->x = new_x;
    vect->y = new_y;
    return 1;
}

void move(struct tank *tank, struct GameContext *GC, int neg)
{
    int h = GC->map->height;
    int w = GC->map->width;
    float move_x = neg * (0.02 * tank->direction->x);
    float move_y = neg * (0.02 * tank->direction->y);
    if (!checkVector2(tank->hbox->v1, move_x, move_y, GC) ||
        !checkVector2(tank->hbox->v2, move_x, move_y, GC) ||
        !checkVector2(tank->hbox->v3, move_x, move_y, GC) ||
        !checkVector2(tank->hbox->v4, move_x, move_y, GC))
        return;
    tank->position->x = tank->position->x + move_x;
    tank->position->y = tank->position->y - move_y;

    float x = tank->position->x;
    float y = tank->position->y;
<<<<<<< HEAD
    if (x > w)
        tank->position->x = 0.0;
    else if (x < 0.0)
        tank->position->x = w;
    if (y > h)
        tank->position->y = 0.0;
    else if (y < 0.0)
        tank->position->y = h;
=======
    int tmp_x = x;
    int tmp_y = y;
    if (GC->map->table[tmp_y][tmp_x]->type == LAVA)
        tank->health--;
    if (x >= w - 0.02)
        tank->position->x = 1.02;
    else if (x <= 0.02)
        tank->position->x = w - 1.02;
    if (y >= h - 0.02)
        tank->position->y = 1.02;
    else if (y < 0.0)
        tank->position->y = h - 1.02;
>>>>>>> [fix] bullet going out of range with segfault
}

static void normalize(struct vector2 *vect)
{
    double deno = sqrt(pow(vect->x, 2) + pow(vect->y, 2));
    vect->x = vect->x / deno;
    vect->y = vect->y / deno;
}

void rotate(struct tank *tank, int neg)
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
        GC->bullets[GC->nb_bullets++] = create_bullet(tank);
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
            rotate(p1, 1);
            break;
        case RIGHT:
            rotate(p1, -1);
            break;
        case FORWARD:
            move(p1, GC, 1);
            break;
        case BACK:
            move(p1, GC, -1);
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
            move(p2, GC, 1);
            break;
        case BACK:
            move(p2, GC, -1);
            break;
        case NOTHING:
        default:
            break;
    }
}
