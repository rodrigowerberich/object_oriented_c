#ifndef OO_CONFIG_MALLOC_H__
#define OO_CONFIG_MALLOC_H__

#include <stdlib.h>
#include <stdint.h>

/* Allocate SIZE bytes of memory.  */
void*    ooc_malloc (size_t __size);
/* Allocate NMEMB elements of SIZE bytes each, all initialized to 0.  */
void*    ooc_calloc (size_t __nmemb, size_t __size);

void*    ooc_realloc (void*__ptr, size_t __size);
void     ooc_free (void* __ptr);

#endif //OO_CONFIG_MALLOC_H__