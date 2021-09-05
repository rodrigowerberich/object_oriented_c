/*
 * collection_interface.h
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */
#ifndef OO_BASE_COLLECTION_INTERFACE_COLLECTION_INTERFACE_H_
#define OO_BASE_COLLECTION_INTERFACE_COLLECTION_INTERFACE_H_

#include <iterable_interface.h>
#include <stdbool.h>
/*------------------------------------------------*/
/*-------------- Helper defines ------------------*/
/*------------------------------------------------*/
// Just a shortcut to calculate the array of a c
// array like int array[] = {1,2,3,4};
// The result of ARRAY_C_SIZE(array_) will be 4
#define ARRAY_C_SIZE(array_) (sizeof(array_)/sizeof(array_[0]))
// Helper type to show that something is a CollectionInterface
typedef void* o_CollectionInterface;
/*------------------------------------------------*/
/*----- Interface methods declaration ------------*/
/*------------------------------------------------*/
// Adds an element to a Collection, the added object
// will now live inside the collection and be deleted
// by the collection, you should not delete it outside
#define M_COLLECTION_ADD_DEF   bool, Collection_add
#define M_COLLECTION_ADD_ARG   const void* _self, void* _o_element
#define M_COLLECTION_ADD_PARAM             _self,       _o_element
INTERFACE_METHOD_DECLARATION(M_COLLECTION_ADD);
// Adds all elements of a Collection into another,
// the original element will be copied to the new
// collection so changes made in one collection
// does not affect the other one, the other collection
// is not destroyed
#define M_COLLECTION_ADD_ALL_DEF   bool, Collection_addAll
#define M_COLLECTION_ADD_ALL_ARG   const void* _self, const o_CollectionInterface _o_collection
#define M_COLLECTION_ADD_ALL_PARAM             _self,                             _o_collection
INTERFACE_METHOD_DECLARATION(M_COLLECTION_ADD_ALL);
// Adds all elements of a c array into a Collection,
// the original elements of the array will be copied to
// the collection so changes made in the collection does not
// affect the original array
#define M_COLLECTION_ADD_ALL_C_DEF   bool, Collection_addAllC
#define M_COLLECTION_ADD_ALL_C_ARG   const void* _self, void* array, int size_of_vector, int size_of_element
#define M_COLLECTION_ADD_ALL_C_PARAM             _self,       array,     size_of_vector,     size_of_element
INTERFACE_METHOD_DECLARATION(M_COLLECTION_ADD_ALL_C);
// Simplifies the call to Collection_addAllC,
// automatically calculating the size of the array
// Ex:
//  int array[] = {15, 6, 8, 10};
//  Collection_simpleAddAllC(o_collection, array);
#define Collection_simpleAddAllC(self_, array_) Collection_addAllC(self_, array_, ARRAY_C_SIZE(array_), sizeof(array_[0]))
#define Collection_inplaceAddAllC(self_, type_, array_)\
{\
    type_ ___help_var_c____[] = array_;\
    Collection_simpleAddAllC(self_, ___help_var_c____);\
}
// Adds all elements of a c array of pointers into
// a Collection, the original elements of the array
// will be copied to the collection so changes made
// in the collection does not affect the original array
#define M_COLLECTION_ADD_ALL_C_POINTER_DEF   bool, Collection_addAllCPointer
#define M_COLLECTION_ADD_ALL_C_POINTER_ARG   const void* _self, void** array, int size_of_vector, int size_of_element
#define M_COLLECTION_ADD_ALL_C_POINTER_PARAM       _self,       array,     size_of_vector,     size_of_element
INTERFACE_METHOD_DECLARATION(M_COLLECTION_ADD_ALL_C_POINTER);
// Simplifies the calls to Collection_addAllCPointer both to objects and non objects
// Ex:
//  int* array_of_pointers[] = { INT(4), INT(9) };
//  Collection_simpleAddAllCPointer(o_collection, array_of_pointers, int);
//  ooc_deleteCArrayContent(array_of_pointers);
//  o_String array_of_objects[] = { String("Hi"), String("Hello") };
//  Collection_addAllCObject(o_collection, array_of_objects);
//  ooc_deleteCArrayContent(array_of_objects);
#define Collection_addAllCObject(self_, array_) Collection_addAllCPointer(self_, array_, ARRAY_C_SIZE(array_), sizeof(0))
#define Collection_inplaceAddAllCObject(container_, c_vector_)\
    {\
        o_Object ___help_var_c___[] = c_vector_;\
        Collection_addAllCObject(container_, ___help_var_c___);\
        ooc_deleteCArrayContent(___help_var_c___);\
    }
#define Collection_simpleAddAllCPointer(self_, array_, pointer_to_type_) Collection_addAllCPointer(self_, array_, ARRAY_C_SIZE(array_), sizeof(pointer_to_type_))
#define Collection_inplaceAddAllCPointer(container_, pointer_to_type_, c_vector_)\
    {\
        pointer_to_type_* ___help_var_c___[] = c_vector_;\
        Collection_simpleAddAllCPointer(container_, ___help_var_c___, pointer_to_type_);\
        ooc_deleteCArrayContent(___help_var_c___);\
    }
// Clears and deletes all the content of the collection
// after this the collections size must be zero
#define M_COLLECTION_CLEAR_DEF   void, Collection_clear
#define M_COLLECTION_CLEAR_ARG   const void* _self
#define M_COLLECTION_CLEAR_PARAM             _self
INTERFACE_METHOD_DECLARATION(M_COLLECTION_CLEAR);
// Checks if an element is contained in the collection, if
// the element is an object that is comparable and clonable or
// an c variable pointer it will be deleted, otherwise it will not
#define M_COLLECTION_CONTAINS_DEF   bool, Collection_contains
#define M_COLLECTION_CONTAINS_ARG   const void* _self, void* _o_element
#define M_COLLECTION_CONTAINS_PARAM             _self,       _o_element
INTERFACE_METHOD_DECLARATION(M_COLLECTION_CONTAINS);
// Indicates if there are no elements in the collection
#define M_COLLECTION_IS_EMPTY_DEF   bool, Collection_isEmpty
#define M_COLLECTION_IS_EMPTY_ARG   const void* _self
#define M_COLLECTION_IS_EMPTY_PARAM             _self
INTERFACE_METHOD_DECLARATION(M_COLLECTION_IS_EMPTY);
// Removes an element from the collection, the removal
// can be either by comparison or equallity (same pointer)
// The element is deleted
#define M_COLLECTION_REMOVE_DEF   bool, Collection_remove
#define M_COLLECTION_REMOVE_ARG   const void* _self, void* _o_element
#define M_COLLECTION_REMOVE_PARAM             _self,       _o_element
INTERFACE_METHOD_DECLARATION(M_COLLECTION_REMOVE);
// Removes all elements from the first collection that
// both collections have in common, the removal can be either by
// comparison or equality (same pointer), the original elements of
// the second collection are not affected
#define M_COLLECTION_REMOVE_ALL_DEF   bool, Collection_removeAll
#define M_COLLECTION_REMOVE_ALL_ARG   const void* _self, const o_CollectionInterface _o_collection
#define M_COLLECTION_REMOVE_ALL_PARAM             _self,                             _o_collection
INTERFACE_METHOD_DECLARATION(M_COLLECTION_REMOVE_ALL);
// Retains all elements from the first collection that
// both collections have in common, the retainment can be either by
// comparison or equality (same pointer), the original elements of
// the second collection are not affected
#define M_COLLECTION_RETAIN_ALL_DEF   bool, Collection_retainAll
#define M_COLLECTION_RETAIN_ALL_ARG   const void* _self, const o_CollectionInterface _o_collection
#define M_COLLECTION_RETAIN_ALL_PARAM             _self,                             _o_collection
INTERFACE_METHOD_DECLARATION(M_COLLECTION_RETAIN_ALL);
// The number of elements in the collection
#define M_COLLECTION_SIZE_DEF   int, Collection_size
#define M_COLLECTION_SIZE_ARG   const void* _self
#define M_COLLECTION_SIZE_PARAM             _self
INTERFACE_METHOD_DECLARATION(M_COLLECTION_SIZE);
// The size of the element inside, if not a c pointer, the value must be 0
#define M_COLLECTION_ELEMENT_SIZE_DEF   int, Collection_elementSize
#define M_COLLECTION_ELEMENT_SIZE_ARG   const void* _self
#define M_COLLECTION_ELEMENT_SIZE_PARAM             _self
INTERFACE_METHOD_DECLARATION(M_COLLECTION_ELEMENT_SIZE);
// Returns a pointer to a c array form of the collection
#define M_COLLECTION_TO_ARRAY_DEF   void**, Collection_toArray
#define M_COLLECTION_TO_ARRAY_ARG   void* _self, int* new_array_size
#define M_COLLECTION_TO_ARRAY_PARAM       _self,      new_array_size
INTERFACE_METHOD_DECLARATION(M_COLLECTION_TO_ARRAY);

#endif /* OO_BASE_COLLECTION_INTERFACE_COLLECTION_INTERFACE_H_ */
