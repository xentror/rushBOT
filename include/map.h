enum floor_type
{
    DIRT = 0;
    LAVA = 1;
    BLOCK = 2;
};

struct map
{
    struct block ***table;
    size_t width;
    size_t height;
};

struct block
{
    enum floor_type type;
};

struct map *create_map(char *path);
void free_map(struct map *my_map);
