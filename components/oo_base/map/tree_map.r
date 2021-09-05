/*
 * tree_map.r
 *
 *  Created on: 9 de jan de 2019
 *      Author: lua
 */

#ifndef COMPONENTS_OO_BASE_MAP_TREE_MAP_R_
#define COMPONENTS_OO_BASE_MAP_TREE_MAP_R_

#include <ooc.r>
#include <tree_map.h>

typedef struct TreeMapNode_r{
    const Object_r        _;            /* TreeMapNode : Object */
    void*                 key;          /* The pointer to the key */
    void*                 value;        /* The pointer to the value */
    size_t                key_size;     /* The size of the object the key points to, used for cloning  */
    size_t                value_size;   /* The size of the object the value points to, used for cloning  */
    struct TreeMapNode_r* right;        /* Classic binary tree structure, points to the right child of this node */
    struct TreeMapNode_r* left;         /* Classic binary tree structure, points to the left child of this node */
    struct TreeMapNode_r* parent;       /* Classic binary tree structure, points to the parent of this node */

}TreeMapNode_r;

typedef struct TreeMapNodeClass_r{
    const Class_r _;
	/*----------------- Clonable ---------------------*/    
    CLASS_INTERFACE_METHOD(TreeMapNodeClass, M_CLONABLE_CLONE);
	/*----------------- Comparable -------------------*/
    CLASS_INTERFACE_METHOD(TreeMapNodeClass, M_COMPARABLE_COMPARE_TO);
}TreeMapNodeClass_r;
/*----------------- Clonable ---------------------*/    
SUPER_INTERFACE_METHOD(TreeMapNodeClass, M_CLONABLE_CLONE);
/*----------------- Comparable -------------------*/
SUPER_INTERFACE_METHOD(TreeMapNodeClass, M_COMPARABLE_COMPARE_TO);

typedef struct TreeMap_r{
    const Object_r _;           /* TreeMap : Object */
    TreeMapNode_r* root;        /* The root of the binary tree */
    size_t         node_count;  /* The number of elements inside the node */
    size_t         height;      /* The current height of the tree */
}TreeMap_r;

typedef struct TreeMapClass_r{
    const Class_r _;
    /*----------------- Clonable ---------------------*/
    CLASS_INTERFACE_METHOD(TreeMapClass, M_CLONABLE_CLONE);
    /*----------------- Iterable ---------------------*/
    CLASS_INTERFACE_METHOD(TreeMapClass, M_ITERABLE_CREATE);
    /*----------------- Collection -------------------*/
    CLASS_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_ADD);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_ADD_ALL);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_ADD_ALL_C_POINTER);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_CLEAR);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_CONTAINS);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_IS_EMPTY);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_REMOVE);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_REMOVE_ALL);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_RETAIN_ALL);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_SIZE);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_TO_ARRAY);
    /*--------------- Map interface ------------------*/
    CLASS_INTERFACE_METHOD(TreeMapClass, M_MAP_ADD);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_MAP_DELETE_BY_VALUE);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_MAP_DELETE_BY_KEY);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_MAP_GET);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_MAP_GET_VALUE);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_MAP_GET_VALUES);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_MAP_FIND_BY_VALUE);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_MAP_GET_KEY);
    CLASS_INTERFACE_METHOD(TreeMapClass, M_MAP_GET_KEYS);
}TreeMapClass_r;

/*----------------- Clonable ---------------------*/
SUPER_INTERFACE_METHOD(TreeMapClass, M_CLONABLE_CLONE);
/*----------------- Iterable ---------------------*/
SUPER_INTERFACE_METHOD(TreeMapClass, M_ITERABLE_CREATE);
/*----------------- Collection -------------------*/
SUPER_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_ADD);
SUPER_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_ADD_ALL);
SUPER_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_ADD_ALL_C_POINTER);
SUPER_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_CLEAR);
SUPER_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_CONTAINS);
SUPER_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_IS_EMPTY);
SUPER_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_REMOVE);
SUPER_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_REMOVE_ALL);
SUPER_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_RETAIN_ALL);
SUPER_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_SIZE);
SUPER_INTERFACE_METHOD(TreeMapClass, M_COLLECTION_TO_ARRAY);
/*--------------- Map interface ------------------*/
SUPER_INTERFACE_METHOD(TreeMapClass, M_MAP_ADD);
SUPER_INTERFACE_METHOD(TreeMapClass, M_MAP_DELETE_BY_VALUE);
SUPER_INTERFACE_METHOD(TreeMapClass, M_MAP_DELETE_BY_KEY);
SUPER_INTERFACE_METHOD(TreeMapClass, M_MAP_GET);
SUPER_INTERFACE_METHOD(TreeMapClass, M_MAP_GET_VALUE);
SUPER_INTERFACE_METHOD(TreeMapClass, M_MAP_GET_VALUES);
SUPER_INTERFACE_METHOD(TreeMapClass, M_MAP_FIND_BY_VALUE);
SUPER_INTERFACE_METHOD(TreeMapClass, M_MAP_GET_KEY);
SUPER_INTERFACE_METHOD(TreeMapClass, M_MAP_GET_KEYS);

#endif /* COMPONENTS_OO_BASE_MAP_TREE_MAP_R_ */
