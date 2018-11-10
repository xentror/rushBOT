#include "update.h"
#include "context.h"

void go_forward(struct tank *T)
{
    T = T;
}

void go_back(struct tank *T)
{
    T = T;
}

void rotate_left(struct tank *T)
{
    T = T;
}

void rotate_right(struct tank *T)
{
    T = T;
}

void update(struct GameContext *GC, enum event event)
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
            break;
        case QUIT:
            break;
        default:
            break;
    }
}
