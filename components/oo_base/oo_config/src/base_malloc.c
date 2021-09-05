#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#include <ooc/malloc.h>
#include <ooc/malloc_analysis.h>
#include <ooc/assert.h>

// #define OOC_MALLOC_BAREBACK
#define OOC_MALLOC_WITHOUT_LIST // Better to use whitout list for now, there may be a problem in it

struct linked_list{
    struct linked_list_node* root;
};


struct linked_list_node{
    void* pointer;
    struct linked_list_node* next;
};

#if !defined(OOC_MALLOC_WITHOUT_LIST)
static void add_node(struct linked_list* list, void* new_pointer){
    if(!list->root){
        list->root = malloc(sizeof(struct linked_list_node));
        verify_pointer(list->root);
        list->root->pointer = new_pointer;
        list->root->next = NULL;
        return;
    }
    struct linked_list_node* current = list->root;
    while(current->next){
        current = current->next;
    }
    current->next = malloc(sizeof(struct linked_list_node));

    current->next->pointer = new_pointer;
    current->next->next = NULL;
}
#endif

#if !defined(OOC_MALLOC_WITHOUT_LIST)
static bool inside_list(struct linked_list* list, void* pointer){
    struct linked_list_node* current = list->root;
    while(current){
        if(current->pointer == pointer){
            return true;
        }
        current = current->next;
    }
    return false;    
}
#endif

#if !defined(OOC_MALLOC_WITHOUT_LIST)
static void swap_node(struct linked_list* list, void* old_pointer, void* new_pointer){
    struct linked_list_node* current = list->root;
    while(current){
        if(current->pointer == old_pointer){
            current->pointer = new_pointer;
            return;
        }
        current = current->next;
    }
}
#endif

#if !defined(OOC_MALLOC_WITHOUT_LIST)
static bool remove_node(struct linked_list* list, void* pointer){
    struct linked_list_node* current = list->root;
    struct linked_list_node* temp_node = NULL;
    
    if(!current){
        return false;
    }

    while(current->pointer != pointer && current->next){
        temp_node = current;
        current = current->next;
    }
    if(current->pointer == pointer){
        if(current == list->root){
            temp_node = list->root;
            list->root = current->next;
            free(temp_node);
            return true;
        }else{
            temp_node->next = current->next;
            free(current);
            return true;
        }
    }
    return false;
}
#endif


#if !defined(OOC_MALLOC_WITHOUT_LIST)
static void print_list(struct linked_list* list){
    struct linked_list_node* current = list->root;    
    while(current){
        printf("Block: %p,", current->pointer);
        current = current->next;
    }
    printf("\n");
}
#endif

#define MAX_OCCUPIED_MEMORY 10240
static uint32_t g_occupied_memory = 0;
#if !defined(OOC_MALLOC_WITHOUT_LIST)
static struct linked_list g_memory_map = {
    .root = NULL
};
#endif


/* Allocate SIZE bytes of memory.  */
void* ooc_malloc (size_t __size){
#if !defined(OOC_MALLOC_BAREBACK)
    size_t size_to_allocate = sizeof(size_t)+__size;
    g_occupied_memory += size_to_allocate;
    void* block_of_data = malloc(size_to_allocate);
    *(size_t*)(block_of_data) = __size;
    void* shifted_pointer = block_of_data+sizeof(size_t);
#if !defined(OOC_MALLOC_WITHOUT_LIST)
    add_node(&g_memory_map, shifted_pointer);
#endif
    return shifted_pointer;
#else
    return malloc(__size);
#endif
}
/* Allocate NMEMB elements of SIZE bytes each, all initialized to 0.  */
void* ooc_calloc (size_t __nmemb, size_t __size){
#if !defined(OOC_MALLOC_BAREBACK)
    size_t total_size = __size*__nmemb;
    size_t size_to_allocate = sizeof(size_t)+total_size;
    g_occupied_memory += size_to_allocate;
    void* block_of_data = malloc(size_to_allocate);
    *(size_t*)(block_of_data) = total_size;
    void* shifted_pointer = block_of_data+sizeof(size_t);
    memset(shifted_pointer, 0, total_size);
#if !defined(OOC_MALLOC_WITHOUT_LIST)    
    add_node(&g_memory_map, shifted_pointer);
#endif
    return shifted_pointer;
#else
    return calloc(__nmemb, __size);
#endif
}
void* ooc_realloc (void*__ptr, size_t __new_size){
#if !defined(OOC_MALLOC_BAREBACK)
#if !defined(OOC_MALLOC_WITHOUT_LIST)
    if(inside_list(&g_memory_map, __ptr)){
#endif
        void* init_of_block = __ptr-sizeof(size_t);
        size_t old_size = *(size_t*)(init_of_block);
        void* new_ptr = ooc_malloc(__new_size);
        // We must copy the mininum size of the two
        size_t size_to_copy = (__new_size < old_size)? __new_size: old_size; 
        memcpy(new_ptr, __ptr, size_to_copy);
        ooc_free(__ptr);
        __ptr = NULL;
        return new_ptr; 
#if !defined(OOC_MALLOC_WITHOUT_LIST)
    }
#endif
    return __ptr;
#else
    return realloc(__ptr, __new_size);
#endif
}

void ooc_free (void* __ptr){
#if !defined(OOC_MALLOC_BAREBACK)
#if !defined(OOC_MALLOC_WITHOUT_LIST)
    if(remove_node(&g_memory_map, __ptr)){
#endif
        void* init_of_block = __ptr-sizeof(size_t);
        size_t size_of_block = *(size_t*)(init_of_block);
        free(init_of_block);
        g_occupied_memory-= size_of_block+sizeof(size_t);
#if !defined(OOC_MALLOC_WITHOUT_LIST)
    }else{
        printf("Block not allocated by this function\n");
    }
#endif
#else
    free(__ptr);
#endif
}

uint32_t ooc_allocated_memory(){
#if !defined(OOC_MALLOC_BAREBACK)
    return g_occupied_memory;
#else
    return 0;
#endif
}
uint32_t ooc_remaining_memory(){
#if !defined(OOC_MALLOC_BAREBACK)
    return MAX_OCCUPIED_MEMORY-g_occupied_memory;
#else
    return 0;
#endif
}
void ooc_see_allocated_memory(){
#if !defined(OOC_MALLOC_WITHOUT_LIST)    
    printf("Memory map: begin --------------\n");
    print_list(&g_memory_map);
    printf("Memory map:   end --------------\n");
#endif
}
