#ifndef UPDATE_H
#define UPDATE_H

#include "context.h"

enum event
{
    J1_LEFT = 0,
    J1_RIGHT,
    J1_FORWARD,
    J1_BACK,
    J1_SHOT,
    J2_LEFT,
    J2_RIGHT,
    J2_FORWARD,
    J2_BACK,
    J2_SHOT,
    NOTHING,
    QUIT
};

#define M_PI 3.14159265358979323846

void update(struct GameContext *GC, enum event event);
void update_input(struct GameContext *GC, enum event event);
void update_position(struct GameContext *GC);

#endif /* !UPDATE_H */
