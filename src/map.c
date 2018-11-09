#include <stdio.h>
#include <stdlib.h>

struct map *create_map(char *path)
{
    FILE *file = fopen(path, "r");
    struct map *my_map = malloc(sizeof(struct map));

    my_map->table = malloc(sizeof(struct block **));
    char c;
    while (fread(&c, 1, sizeof(char), file) > 0)
    {
        printf("%c", c);
    }

    return my_map;
}

void free_map(struct map *my_map)
{
    for (int i = 0; i < my_map->height; i++)
    {
        for (int j = 0; j < my_map->width; j++)
            free(my_map->table[i][j]);
        free(my_map->table[i]);
    }
    free(my_map->table);
    free(my_map);
}

void print_map (struct map *my_map)
{
    for (int i = 0; i < my_map->height; i++)
    {
        for (int j = 0; j < my_map->width; j++)
            printf("%d", my_map->table[i][j]);
        printf("\n");
    }
}

int main(void)
{
    struct map *m = create_map("maps/map1");
    print_map(m);
    return 0;
}
