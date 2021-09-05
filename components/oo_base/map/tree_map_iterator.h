/*
 * tree_map_iterator.h
 *
 *  Created on: 9 de jan de 2019
 *      Author: lua
 */

#ifndef COMPONENTS_OO_BASE_MAP_TREE_MAP_ITERATOR_H_
#define COMPONENTS_OO_BASE_MAP_TREE_MAP_ITERATOR_H_

#include <ooc.h>
#include <iterator.h>
#include <tree_map.r>

// Class implementation of the Iterator interface for the TreeMap class

/*------------------------------------------------*/
/*----------- ClassVar declaration ---------------*/
/*------------------------------------------------*/
CLASS_DECLARATION(TreeMapIterator);
/*------------------------------------------------*/
/*------------ Class constructors ----------------*/
/*------------------------------------------------*/
// Create a tree map iterator from a pointer to the tree root node
// You should't call this directly, you should alway use the Iterable_create method on the TreeMap
static inline o_TreeMapIterator TreeMapIterator(TreeMapNode_r* root_node){
    return ooc_new(TreeMapIteratorClass(), root_node);
}

#endif /* COMPONENTS_OO_BASE_MAP_TREE_MAP_ITERATOR_H_ */
