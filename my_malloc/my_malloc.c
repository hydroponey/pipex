#include "my_malloc.h"

void *my_malloc(size_t size __attribute__((unused)))
{
    //srand(0);

    //if (rand() % 2)
    //    return (malloc(size));
    errno = 12;
    return (0);
}