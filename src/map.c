#include <stdlib.h>
#include <stdio.h>
#include "map.h"

static struct block *create_block(char c)
{
    struct block *my_block = malloc(sizeof(struct block));

    switch (c)
    {
        case 'd':
            my_block->type = DIRT;
            break;
        case 'l':
            my_block->type = LAVA;
            break;
        case 'b':
            my_block->type = BLOCK;
            break;
        default:
            my_block->type = DIRT;
    }

    return my_block;
}

static void fill_map(struct map *my_map, FILE *file)
{
    char c;
    size_t i = 0;
    size_t j = 0;

    while (fread(&c, 1, sizeof(char), file) > 0)
    {
        if (c == '\n')
        {
            my_map->width = j;
            j = 0;
            i++;
            my_map->table = realloc(my_map->table, sizeof(struct block **) * (i + 1));
            my_map->table[i] = malloc(sizeof(struct block *));
        }
        else
        {
            my_map->table[i] = realloc(my_map->table[i], sizeof(struct block *) * (j + 1));
            my_map->table[i][j] = create_block(c);
            j++;
        }
    }
    my_map->height = i;
}

struct map *create_map(char *path)
{
    FILE *file = fopen(path, "r");
    if(!file)
        return NULL;
    struct map *my_map = malloc(sizeof(struct map));

    my_map->table = malloc(sizeof(struct block **));
    fill_map(my_map, file);
    return my_map;
}

void free_map(struct map *my_map)
{
    for (size_t i = 0; i < my_map->height; i++)
    {
        for (size_t j = 0; j < my_map->width; j++)
            free(my_map->table[i][j]);
        free(my_map->table[i]);
    }
    free(my_map->table);
    free(my_map);
}
