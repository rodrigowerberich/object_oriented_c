/*
 * tree_map_helper_functions.h
 *
 *  Created on: 9 de jan de 2019
 *      Author: lua
 */

#ifndef COMPONENTS_OO_BASE_MAP_TREE_MAP_HELPER_FUNCTIONS_H_
#define COMPONENTS_OO_BASE_MAP_TREE_MAP_HELPER_FUNCTIONS_H_

// Returns the smallest element of the tree
TreeMapNode_r* tree_map_minimun(TreeMapNode_r* node);
// Returns the biggest element of the tree
TreeMapNode_r* tree_map_maximum(TreeMapNode_r* node);
// Compares the key of two nodes without deleting any of them
static inline int tree_map_compare_keys(TreeMapNode_r* node1, TreeMapNode_r* node2){
    return TreeMapNode_compareKey(node1, Clonable_safeClone(node2->key, node2->key_size));
}
// Compares the value of two nodes without deleting any of them
static inline int tree_map_compare_values(TreeMapNode_r* node1, TreeMapNode_r* node2){
    return TreeMapNode_compareValue(node1, Clonable_safeClone(node2->value, node2->value_size));
}

#endif /* COMPONENTS_OO_BASE_MAP_TREE_MAP_HELPER_FUNCTIONS_H_ */
