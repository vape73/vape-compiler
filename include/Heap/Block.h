#include <cstdlib>

struct Block
{
    void *data;
    size_t size;
    bool used;
};