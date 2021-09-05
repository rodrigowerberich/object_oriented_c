/*
 * list_interface.h
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */

#ifndef OO_BASE_COLLECTION_INTERFACE_LIST_INTERFACE_H_
#define OO_BASE_COLLECTION_INTERFACE_LIST_INTERFACE_H_

#include <collection_interface.h>

// Lists are extensions of collections
/*------------------------------------------------*/
/*-------------- Helper defines ------------------*/
/*------------------------------------------------*/
// Helper type to show that something is a ListInterface
typedef void* o_ListInterface;
/*------------------------------------------------*/
/*----- Interface methods declaration ------------*/
/*------------------------------------------------*/
// Adds an element to a List, into the specified index
// the added object will now live inside the list and
// be deleted by the list, you should not delete it outside
#define M_LIST_ADD_DEF   bool, List_add
#define M_LIST_ADD_ARG   const void* _self, int index, void* _o_element
#define M_LIST_ADD_PARAM             _self,     index,       _o_element
INTERFACE_METHOD_DECLARATION(M_LIST_ADD);
// Adds all elements of a Collection into a list, into
// the specified position, pushing the other elements to
// the side. The original element will be copied to the new
// list so changes made in the collection does not
// affect the list and vice versa, the other collection
// is not destroyed
#define M_LIST_ADD_ALL_DEF   bool, List_addAll
#define M_LIST_ADD_ALL_ARG   const void* _self, int index, const void* _o_collection
#define M_LIST_ADD_ALL_PARAM             _self,     index,             _o_collection
INTERFACE_METHOD_DECLARATION(M_LIST_ADD_ALL);
// Adds all elements of a c array into a List, into
// the specified position the original elements of
// the array will be copied to the collection so changes
// made in the collection does not affect the original array
#define M_LIST_ADD_ALL_C_DEF   bool, List_addAllC
#define M_LIST_ADD_ALL_C_ARG   const void* _self, int index, void* array, int size_of_vector, int size_of_element
#define M_LIST_ADD_ALL_C_PARAM             _self,     index,       array,     size_of_vector,     size_of_element
INTERFACE_METHOD_DECLARATION(M_LIST_ADD_ALL_C);
// Simplifies the call to List_addAllC,
// automatically calculating the size of the array
// Ex:
//  int array[] = {15, 6, 8, 10};
//  List_addAllC(o_list, 2, array);
#define List_simpleAddAllC(self_, index_, array_) List_addAllC(self_, index_, array_, ARRAY_C_SIZE(array_), sizeof(array_[0]))
// Gets the object at position index,
// if the index is out of range, NULL
// will be returned
// The return is a pointer, so changes
// made to the returned object, will
// affect the content inside the list
#define M_LIST_GET_DEF   void*, List_get
#define M_LIST_GET_ARG   const void* _self, int index
#define M_LIST_GET_PARAM             _self,     index
INTERFACE_METHOD_DECLARATION(M_LIST_GET);
// Returns the index of the element, the element can
// be found by comparison or equality (same pointer),
// in the later option element is not deleted, otherwise
// it is. If none is found, it returns -1
#define M_LIST_INDEX_OF_DEF   int, List_indexOf
#define M_LIST_INDEX_OF_ARG   const void* _self, void* _o_element
#define M_LIST_INDEX_OF_PARAM             _self,       _o_element
INTERFACE_METHOD_DECLARATION(M_LIST_INDEX_OF);
// The same of List_indexOf but starting from the end
#define M_LIST_LAST_INDEX_OF_DEF   int, List_lastIndexOf
#define M_LIST_LAST_INDEX_OF_ARG   const void* _self, void* _o_element
#define M_LIST_LAST_INDEX_OF_PARAM             _self,       _o_element
INTERFACE_METHOD_DECLARATION(M_LIST_LAST_INDEX_OF);
// Removes the object at position index, if index is out of
// range nothing happens
#define M_LIST_REMOVE_DEF   bool, List_remove
#define M_LIST_REMOVE_ARG   const void* _self, int index
#define M_LIST_REMOVE_PARAM             _self,     index
INTERFACE_METHOD_DECLARATION(M_LIST_REMOVE);
// Changes the content of the list at position index
// to the new element erasing the old. If the index is
// out of range, nothing should happen
#define M_LIST_SET_DEF   bool, List_set
#define M_LIST_SET_ARG   const void* _self, int index, void* _o_new_element
#define M_LIST_SET_PARAM             _self,     index,       _o_new_element
INTERFACE_METHOD_DECLARATION(M_LIST_SET);
// Return a subset from the list containing the element
// from index fromIndex to toIndex
#define M_LIST_SUBLIST_DEF   o_ListInterface, List_subList
#define M_LIST_SUBLIST_ARG   void* _self, int fromIndex, int toIndex
#define M_LIST_SUBLIST_PARAM       _self,     fromIndex,     toIndex
INTERFACE_METHOD_DECLARATION(M_LIST_SUBLIST);

#endif /* OO_BASE_COLLECTION_INTERFACE_LIST_INTERFACE_H_ */
