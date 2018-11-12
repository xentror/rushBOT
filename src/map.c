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

    size_t width = 0;
    fread(&c, 1, sizeof(char), file);
    while(c != '\n')
    {
        fread(&c, 1, sizeof(char), file);
        width++;
    }

    size_t height = 1;
    while(fread(&c, 1, sizeof(char), file) > 0)
        height += (c == ('\n'));


    my_map->table = malloc(sizeof(struct block **) * height);
    for (size_t i = 0; i < height; i++)
        my_map->table[i] = malloc(sizeof(struct block *) * width);


    fseek(file, 0, SEEK_SET);

    size_t i = 0;
    size_t j = 0;
    while (fread(&c, 1, sizeof(char), file) > 0)
    {
        if (c == '\n')
        {
            j = 0;
            i++;
        }
        else
            my_map->table[i][j++] = create_block(c);
    }

    my_map->width = width;
    my_map->height = height;
}

struct map *create_map(char *path)
{
    FILE *file = fopen(path, "r");
    if(!file)
        return NULL;
    struct map *my_map = malloc(sizeof(struct map));

    fill_map(my_map, file);
    fclose(file);

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
