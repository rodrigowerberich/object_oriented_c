#ifndef OO_CONFIG_MALLOC_ANALYSIS_H__
#define OO_CONFIG_MALLOC_ANALYSIS_H__

#include <stdlib.h>
#include <stdint.h>
    
uint32_t ooc_allocated_memory();
uint32_t occ_remaining_memory();
void     ooc_see_allocated_memory();

#endif //OO_CONFIG_MALLOC_ANALYSIS_H__