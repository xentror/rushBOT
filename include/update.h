#ifndef UPDATE_H
#define UPDATE_H

#include "context.h"

#define M_PI 3.14159265358979323846

void update(struct GameContext *GC);
void update_input(struct GameContext *GC);
void update_position(struct GameContext *GC);
void shot(struct GameContext *GC, struct tank *T);
int touch_the_wall(struct map *M, struct vector2 *position);
int in_the_lava(struct map *M, struct vector2 *position);
void move(struct tank *tank, struct GameContext *GC, int neg);
void rotate(struct tank *tank, int neg);

#endif /* !UPDATE_H */
