#include <stdio.h>

struct map *create_map(char *path)
{
    FILE *file = fopen(path, "r");
    struct map *my_map = malloc(sizeof(struct map));
    my_map->table = malloc(sizeof(struct block **));
    while (fread(buffer, 3, sizeof(char), file) > 0)
    {


    }
}

void free_map(struct map *my_map)
{
    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
            free(map->table[i][j]);
        free(map->table[i]);
    }
    free(map->table);
    free(map);
}

void print_map (struct map *my_map)
{
    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
            printf("%d", map->table[i][j]);
        printf("\n");
    }
}

int main(void)
{
    struct map *m = create_map("maps/map1");
    print_map();
    return 0;
}
