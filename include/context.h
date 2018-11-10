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
    int since_i_shot;
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
    struct vector2 *position;
    struct vector2 *direction;
    int damage;
    int speed;
    enum bulletType type;
};

struct GameContext
{
    struct map *map;
    struct tank **enemies;
    int nb_enemies;
    struct tank *player1;
    struct tank *player2;
    int isPlaying;
    struct bullet **bullets;
    int nb_bullets;
};

void gameInit(struct GameContext *game, char *arg);
void free_game(struct GameContext *GC);

#endif /* !CONTEXT_H */
