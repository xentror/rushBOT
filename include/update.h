#ifndef UPDATE_H
#define UPDATE_H

#include "context.h"

#define M_PI 3.14159265358979323846

void update(struct GameContext *GC);
void update_input(struct GameContext *GC);
void update_position(struct GameContext *GC);
void shot(struct GameContext *GC, struct tank *T);

#endif /* !UPDATE_H */
