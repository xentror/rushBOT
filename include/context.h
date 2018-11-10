#ifndef CONTEXT_H
#define CONTEXT_H

#include "map.h"

struct vector2
{
    float x;
    float y;
};

struct tank
{
    struct vector2 *position;
    struct vector2 *direction;
    int health;
    float speed;
};

enum bulletType
{
    NORMAL = 0,
    HEAVY,
    LIGHT,
    ENORMOUS
};

struct bullet
{
    struct vector2 *direction;
    int damage;
    int speed;
    enum bulletType type;
};

struct GameContext
{
    struct map *map;
    struct tank **enemies;
    struct tank *player1;
    struct tank *player2;
    int isPlaying;
    struct bullet **bullets;
};

void gameInit(struct GameContext *game, char *arg);

#endif /* !CONTEXT_H */
