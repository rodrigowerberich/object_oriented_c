/*
 * tree_map.h
 *
 *  Created on: 9 de jan de 2019
 *      Author: lua
 */

#ifndef COMPONENTS_OO_BASE_MAP_TREE_MAP_H_
#define COMPONENTS_OO_BASE_MAP_TREE_MAP_H_

#include <ooc.h>
#include <map_interface.h>
#include <clonable_interface.h>
#include <comparable_interface.h>

/*------------------------------------------------*/
/*----------- ClassVar declaration ---------------*/
/*------------------------------------------------*/
CLASS_DECLARATION(TreeMapNode);
CLASS_DECLARATION(TreeMapNodeClass);
CLASS_DECLARATION(TreeMap);
CLASS_DECLARATION(TreeMapClass);
/*------------------------------------------------*/
/*------------ Class constructors ----------------*/
/*------------------------------------------------*/
/*--------------- Tree Map Node ------------------*/

// Usage rules:
// Avoid using float or double as keys because their comparison can be flawed
// When using an object as a key, the object must implement both the comparable and clonable interfaces

// Creates a node in which both the key and the value are normal c variables
// To simplify creation, use the TreeMapNodeKeyCValueCHelper macro
//  Ex:
//      o_TreeMapNode node = TreeMapNodeKeyCValueCHelper(INT(3), int, FLOAT(2.7), float);
static inline o_TreeMapNode TreeMapNodeKeyCValueC(void* key, size_t key_size, void* value, size_t value_size){
    return ooc_new(TreeMapNodeClass(), key, key_size, value, value_size);
}
#define TreeMapNodeKeyCValueCHelper(key_, key_type_, value_, value_type_) TreeMapNodeKeyCValueC(key_, sizeof(key_type_), value_, sizeof(value_type_))
// Creates a node in which only the key is a normal c variables
// To simplify creation, use the TreeMapNodeKeyCHelper macro
//  Ex:
//      o_TreeMapNode node = TreeMapNodeKeyCHelper(INT(3), int, String("Three"));
static inline o_TreeMapNode TreeMapNodeKeyC(void* key, size_t key_size, void* value){
    return TreeMapNodeKeyCValueC(key, key_size, value, 0);
}
#define TreeMapNodeKeyCHelper(key_, key_type_, value_) TreeMapNodeKeyC(key_, sizeof(key_type_), value_)
// Creates a node in which only the value is a normal c variables
// To simplify creation, use the TreeMapNodeValueCHelper macro
//  Ex:
//      o_TreeMapNode node = TreeMapNodeValueCHelper(String("Three"), INT(3), int);
static inline o_TreeMapNode TreeMapNodeValueC(void* key, void* value, size_t value_size){
    return TreeMapNodeKeyCValueC(key, 0, value, value_size);
}
#define TreeMapNodeValueCHelper(key_, value_, value_type_) TreeMapNodeValueC(key_, value_, sizeof(value_type_))
// Creates a node in which both key and value are objects
//  Ex:
//      o_TreeMapNode node = TreeMapNode(String("Bye"), String("Hi"));
static inline o_TreeMapNode TreeMapNode(void* key, void* value){
    return TreeMapNodeKeyCValueC(key, 0, value, 0);
}
/*------------------ Tree Map---------------------*/
// Creates a map into which you must insert only TreeMapNode objects
static inline o_TreeMap TreeMap(){
    return ooc_new(TreeMapClass());
}
/*------------------------------------------------*/
/*--------------- Class methods ------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
/*----------- Static linked methods --------------*/
/*------------------------------------------------*/
/*--------------- Tree Map Node ------------------*/
/*------------------------------------------------*/
void* TreeMapNode_getKey(const void* _self);
void* TreeMapNode_getValue(const void* _self);
// Compares only the keys between two nodes
int TreeMapNode_compareKey(const void* _self, void* other_key);
// Compares only the value of a node with a given value, the key is ignored
int TreeMapNode_compareValue(const void* _self, void* other_value);
/*------------------------------------------------*/
/*-------------- Interface Methods ---------------*/
/*------------------------------------------------*/
/*--------------- Tree Map Node ------------------*/
/*------------------------------------------------*/
/*----------------- Clonable ---------------------*/
INTERFACE_METHOD_HEADER(TreeMapNodeClass, M_CLONABLE_CLONE);
/*---------------- Comparable --------------------*/
INTERFACE_METHOD_HEADER(TreeMapNodeClass, M_COMPARABLE_COMPARE_TO);
/*------------------------------------------------*/
/*---------------- Tree Map ----------------------*/
/*------------------------------------------------*/
/*----------------- Clonable ---------------------*/
INTERFACE_METHOD_HEADER(TreeMapClass, M_CLONABLE_CLONE);
/*----------------- Iterable ---------------------*/
INTERFACE_METHOD_HEADER(TreeMapClass, M_ITERABLE_CREATE);
/*----------------- Collection -------------------*/
INTERFACE_METHOD_HEADER(TreeMapClass, M_COLLECTION_ADD);
INTERFACE_METHOD_HEADER(TreeMapClass, M_COLLECTION_ADD_ALL);
INTERFACE_METHOD_HEADER(TreeMapClass, M_COLLECTION_ADD_ALL_C_POINTER);
INTERFACE_METHOD_HEADER(TreeMapClass, M_COLLECTION_CLEAR);
INTERFACE_METHOD_HEADER(TreeMapClass, M_COLLECTION_CONTAINS);
INTERFACE_METHOD_HEADER(TreeMapClass, M_COLLECTION_IS_EMPTY);
INTERFACE_METHOD_HEADER(TreeMapClass, M_COLLECTION_REMOVE);
INTERFACE_METHOD_HEADER(TreeMapClass, M_COLLECTION_REMOVE_ALL);
INTERFACE_METHOD_HEADER(TreeMapClass, M_COLLECTION_RETAIN_ALL);
INTERFACE_METHOD_HEADER(TreeMapClass, M_COLLECTION_SIZE);
INTERFACE_METHOD_HEADER(TreeMapClass, M_COLLECTION_TO_ARRAY);
/*--------------- Map interface ------------------*/
INTERFACE_METHOD_HEADER(TreeMapClass, M_MAP_ADD);
INTERFACE_METHOD_HEADER(TreeMapClass, M_MAP_DELETE_BY_VALUE);
INTERFACE_METHOD_HEADER(TreeMapClass, M_MAP_DELETE_BY_KEY);
INTERFACE_METHOD_HEADER(TreeMapClass, M_MAP_GET);
INTERFACE_METHOD_HEADER(TreeMapClass, M_MAP_GET_KEY);
INTERFACE_METHOD_HEADER(TreeMapClass, M_MAP_GET_KEYS);
INTERFACE_METHOD_HEADER(TreeMapClass, M_MAP_GET_VALUES);
INTERFACE_METHOD_HEADER(TreeMapClass, M_MAP_FIND_BY_VALUE);
#endif /* COMPONENTS_OO_BASE_MAP_TREE_MAP_H_ */
