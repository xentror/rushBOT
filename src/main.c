#include <stdlib.h>
#include <rand.h>
#include "map.h"
#include "context.h"

struct GameContext game;

struct vector2 *spawnTank(struct GameContext game)
{
    int h = game->map.height;
    int w = game->map.width;
    float pos_x = rand() % w;
    float pos_y = rand() % h;
    while (game->map->table[pos_y][pos_x].type)
    {
        pos_x = rand() % w;
        pos_y = rand() % h;
    }
    struct vector2 *new = malloc(sizeof(struct vector2));
    new->y = pos_y + 0.5;
    new->x = pos_x + 0.5;
    return new;
}

struct tank *initTank(struct GameContext game)
{
    struct tank *new = malloc(sizeof(struct tank));
    new->position = spawnTank(game);
    new->direction = malloc(sizeof(struct vector2));
    new->direction.x = 1;
    new->direction.y = 0;
    new->health = 100;
    new->speed = 0;
    return new;
}

void gameInit(struct GameContext game)
{
    game->map = create_map(argv[1]);
    game->player1 = initTank(game);
    game->player2 = initTank(game);
    struct tank **enemies = malloc(sizeof(struct tank*) * 2);
    for (size_t i = 0; i < 2; i++)
        enemies[i] = initTank(game);
    game->enemies = enemies;
    game->isPlaying = 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        errx(1, "Please enter path for map like: ./toto <path>");
    gameInit(game);
    while (game.isPlaying)
    {
        printf("tamerelapute\n");
    }
    return 0;
}
