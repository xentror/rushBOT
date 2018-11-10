#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "map.h"
#include "context.h"

int nb_rnd = 0;

struct vector2 *spawnTank(struct GameContext game)
{
    int h = game.map->height;
    int w = game.map->width;
    srand(time(NULL) + nb_rnd++);
    int pos_x = rand() % w;
    int pos_y = rand() % h;
    while (game.map->table[pos_y][pos_x]->type != 0)
    {
        pos_x = rand() % w;
        pos_y = rand() % h;
    }
    printf("pos_x=%d pos_y=%d type pos %d\n", pos_x, pos_y, 
            game.map->table[pos_y][pos_x]->type);

    struct vector2 *new = malloc(sizeof(struct vector2));
    new->y = pos_y - 0.5;
    new->x = pos_x - 0.5;
    return new;
}

struct tank *initTank(struct GameContext game)
{
    struct tank *new = malloc(sizeof(struct tank));
    new->position = spawnTank(game);
    new->direction = malloc(sizeof(struct vector2));
    new->direction->x = 1;
    new->direction->y = 0;
    new->health = 100;
    new->speed = 0;
    new->event = NOTHING;
    new->is_shoting = 0;
    new->since_i_shot = 0;
    return new;
}

void gameInit(struct GameContext *game, char *arg)
{
    game->map = create_map(arg);
    game->player1 = initTank(*game);
    game->player2 = initTank(*game);
    struct tank **enemies = malloc(sizeof(struct tank*) * 2);
    for (size_t i = 0; i < 2; i++)
        enemies[i] = initTank(*game);
    game->nb_enemies = 2;
    game->enemies = enemies;
    game->isPlaying = 1;
}
