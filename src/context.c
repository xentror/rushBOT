#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "context.h"

int nb_rnd = 0;

static struct vector2 *spawnTank(struct GameContext game)
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
    struct vector2 *new = malloc(sizeof(struct vector2));
    new->y = pos_y;
    new->x = pos_x;
    return new;
}

static struct hitbox *initHitbox(struct vector2 *center)
{
    struct hitbox *hbox = malloc(sizeof(struct hitbox));
    hbox->v1 = malloc(sizeof(struct vector2));
    hbox->v1->x = center->x + 0.1;
    hbox->v1->y = center->y + 0.1;

    hbox->v2 = malloc(sizeof(struct vector2));
    hbox->v2->x = center->x + 0.1;
    hbox->v2->y = center->y + 0.9;

    hbox->v3 = malloc(sizeof(struct vector2));
    hbox->v3->x = center->x + 0.9;
    hbox->v3->y = center->y + 0.1;

    hbox->v4 = malloc(sizeof(struct vector2));
    hbox->v4->x = center->x + 0.9;
    hbox->v4->y = center->y + 0.1;

    return hbox;
}

static struct tank *initTank(struct GameContext game, int t_id)
{
    struct tank *new = malloc(sizeof(struct tank));
    new->position = spawnTank(game);
    new->hbox = initHitbox(new->position);
    new->direction = malloc(sizeof(struct vector2));
    new->direction->x = 1;
    new->direction->y = 0;
    new->health = 100;
    new->speed = 0.1;
    new->event = NOTHING;
    new->is_shoting = 0;
    new->since_i_shot = 0;
    new->t_id = t_id;
    return new;
}

void gameInit(struct GameContext *game, char *arg)
 {
    game->map = generate_map();
    game->player1 = initTank(*game, 0);
    game->player2 = initTank(*game, 1);
    struct tank **enemies = malloc(sizeof(struct tank*) * 2);
    for (size_t i = 0; i < 2; i++)
        enemies[i] = initTank(*game, 2 + i);
    game->nb_enemies = 2;
    game->enemies = enemies;
    game->isPlaying = 1;
    game->winner = -1;
}
