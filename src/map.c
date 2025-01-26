#include <stdlib.h>
#include <stdio.h>

#include "map.h"
#include "perlin_noise.h"

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

char map_noise_to_char(float noise) {
  if (noise < 0.7)
    return 'g';
  else if (noise >= 0.7 && noise <= 0.85)
    return 'l';
  else
    return 'b';
}

struct map *generate_map(void) {
  struct map *my_map = malloc(sizeof(struct map));

  int height = 28, width = 28;
  my_map->height = height;
  my_map-> width = width;

  // Allocation of the matrix of blocks
  my_map->table = malloc(sizeof(struct block*) * height);
  for (int i = 0; i < height; i++) {
    my_map->table[i] = malloc(sizeof(struct block*) * width);

    for (int j = 0; j < width; j++) {
      float noise = perlin2d(i, j, 0.4, 1);
      char c = map_noise_to_char(noise);

      // Force the limit of the map to be a bloc
      if (i == 0 || j == 0 || j + 1 == width || i + 1 == height)
        c = 'b';

      my_map->table[i][j] = create_block(c);
    }
  }

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
