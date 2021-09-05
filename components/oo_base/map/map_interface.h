/*
 * map_interface.h
 *
 *  Created on: 9 de jan de 2019
 *      Author: lua
 */

#ifndef COMPONENTS_OO_BASE_MAP_MAP_INTERFACE_H_
#define COMPONENTS_OO_BASE_MAP_MAP_INTERFACE_H_

#include <collection_interface.h>
#include <vector.h>
#include <stdbool.h>
/*------------------------------------------------*/
/*-------------- Helper defines ------------------*/
/*------------------------------------------------*/
// Helper type to show that something is a MapInterface
typedef void* o_MapInterface;
/*------------------------------------------------*/
/*----- Interface methods declaration ------------*/
/*------------------------------------------------*/
// Adds a key and value of c type, you can use the helper macros
// and functions to ease the work
#define M_MAP_ADD_DEF   bool, Map_addKeyCValueC
#define M_MAP_ADD_ARG   void* _self, void* key, int key_size,  void* _o_value, int value_size
#define M_MAP_ADD_PARAM       _self,       key,     key_size,        _o_value,     value_size
INTERFACE_METHOD_DECLARATION(M_MAP_ADD);
// Ex 1:
//  o_MapInterface o_map;
//  ... Create some map
//  Map_addKeyCValueCHelper(INT(3), int, INT(-7), int);
#define Map_addKeyCValueCHelper(self_, key_, type_of_key_, value_, type_of_value_)\
    Map_addKeyCValueC(self_, key_, sizeof(type_of_key_), value_, sizeof(type_of_value_))
// Ex 2:
//  o_MapInterface o_map;
//  ... Create some map
//  Map_addKeyCHelper(INT(3), int, String("Hi"));    
static inline bool Map_addKeyC(void* _self, void* key, int key_size,  void* _o_value){
    return Map_addKeyCValueC(_self, key, key_size, _o_value, 0);
}
#define Map_addKeyCHelper(self_, key_, type_of_key_, value_)\
    Map_addKeyC(self_, key_, sizeof(type_of_key_), value_)
// Ex 3:
//  o_MapInterface o_map;
//  ... Create some map
//  Map_addValueCHelper(String("Hi"), INT(3), int);
static inline bool Map_addValueC(void* _self, void* key, void* _o_value, int value_size){
    return Map_addKeyCValueC(_self, key, 0, _o_value, value_size);
}
#define Map_addValueCHelper(self_, key_, value_, type_of_value_)\
    Map_addValueC(self_, key_, value_, sizeof(type_of_value_))
// Ex 4:
//  o_MapInterface o_map;
//  ... Create some map
//  Map_add(String("Hi"), String("Bye"));
static inline bool Map_add(void* _self, void* key, void* _o_value){
    return Map_addKeyCValueC(_self, key, 0, _o_value, 0);
}
// Searches and deletes the first node found with that value,
// if no nodes are found, returns false
#define M_MAP_DELETE_BY_VALUE_DEF   bool, Map_deleteByValue
#define M_MAP_DELETE_BY_VALUE_ARG   void* _self,  void* _o_value
#define M_MAP_DELETE_BY_VALUE_PARAM       _self,        _o_value
INTERFACE_METHOD_DECLARATION(M_MAP_DELETE_BY_VALUE);
// Searches and deletes the node found with that key,
// if no nodes are found, returns false
#define M_MAP_DELETE_BY_KEY_DEF   bool, Map_deleteByKey
#define M_MAP_DELETE_BY_KEY_ARG   void* _self,  void* _o_key
#define M_MAP_DELETE_BY_KEY_PARAM       _self,        _o_key
INTERFACE_METHOD_DECLARATION(M_MAP_DELETE_BY_KEY);
// Retrieves the node with the given key, if none is found
// returns NULL
#define M_MAP_GET_DEF   void*, Map_get
#define M_MAP_GET_ARG   void* _self,  void* _o_key
#define M_MAP_GET_PARAM       _self,        _o_key
INTERFACE_METHOD_DECLARATION(M_MAP_GET);
// Retrieves the value of the given key, if none is found
// returns NULL
#define M_MAP_GET_VALUE_DEF   void*, Map_getValue
#define M_MAP_GET_VALUE_ARG   void* _self,  void* _o_key
#define M_MAP_GET_VALUE_PARAM       _self,        _o_key
INTERFACE_METHOD_DECLARATION(M_MAP_GET_VALUE);
// Returns a vector with all the values contained in the map
#define M_MAP_GET_VALUES_DEF   o_Vector, Map_getValues
#define M_MAP_GET_VALUES_ARG   void* _self
#define M_MAP_GET_VALUES_PARAM       _self
INTERFACE_METHOD_DECLARATION(M_MAP_GET_VALUES);
// Retrieves the first node found with that value
#define M_MAP_FIND_BY_VALUE_DEF   void*, Map_findByValue
#define M_MAP_FIND_BY_VALUE_ARG   void* _self, void* _o_value
#define M_MAP_FIND_BY_VALUE_PARAM       _self,       _o_value
INTERFACE_METHOD_DECLARATION(M_MAP_FIND_BY_VALUE);
// Retrieves the key of the node with the given value, if none is found
// returns NULL
#define M_MAP_GET_KEY_DEF   void*, Map_getKey
#define M_MAP_GET_KEY_ARG   void* _self,  void* _o_value
#define M_MAP_GET_KEY_PARAM       _self,        _o_value
INTERFACE_METHOD_DECLARATION(M_MAP_GET_KEY);
// Returns a vector with all the keys contained in the map
#define M_MAP_GET_KEYS_DEF   o_Vector, Map_getKeys
#define M_MAP_GET_KEYS_ARG   void* _self
#define M_MAP_GET_KEYS_PARAM       _self
INTERFACE_METHOD_DECLARATION(M_MAP_GET_KEYS);


#endif /* COMPONENTS_OO_BASE_MAP_MAP_INTERFACE_H_ */
