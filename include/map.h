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
