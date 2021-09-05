/*
 * TreeMapIterator.r
 *
 *  Created on: 9 de jan de 2019
 *      Author: lua
 */

#ifndef COMPONENTS_OO_BASE_MAP_TREE_MAP_ITERATOR_R_
#define COMPONENTS_OO_BASE_MAP_TREE_MAP_ITERATOR_R_

#include <ooc.r>
#include <vector_iterator.h>

typedef struct TreeMapIterator_r{
    Object_r       _;           /* TreeMapIterator: Object */
    TreeMapNode_r* first_node;  /* A pointer to the element with minimal key of the map */
    TreeMapNode_r* last_node;   /* A pointer to the element with maximal key of the map */
    TreeMapNode_r* curr_node;   /* The current element the iterator is pointing to */
}TreeMapIterator_r;


#endif /* COMPONENTS_OO_BASE_MAP_TREE_MAP_ITERATOR_R_ */
