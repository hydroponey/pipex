#ifndef MY_MALLOC
#define MY_MALLOC

#include <stdlib.h>
#include <errno.h>

#define malloc(x) my_malloc(x)

void *my_malloc(size_t size);

#endif