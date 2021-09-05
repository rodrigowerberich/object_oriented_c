/*
 * vector.h
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */

#ifndef OO_BASE_VECTOR_VECTOR_H_
#define OO_BASE_VECTOR_VECTOR_H_

#include <ooc.h>
#include <list_interface.h>
#include <clonable_interface.h>

/*------------------------------------------------*/
/*-------------- Helper defines ------------------*/
/*------------------------------------------------*/
#define VECTOR_MIN_CAPACITY 5
#define SIZE_OF_VECTOR_OF_OBJECT 0
/*------------------------------------------------*/
/*----------- ClassVar declaration ---------------*/
/*------------------------------------------------*/
CLASS_DECLARATION(Vector);
CLASS_DECLARATION(VectorClass);
/*------------------------------------------------*/
/*------------ Class constructors ----------------*/
/*------------------------------------------------*/
// If you want to define a vector of objects with a defined capacity
// Ex:
//      o_Vector vec = VectorSize();
static inline o_Vector VectorSize(size_t container_size){
    return ooc_new(VectorClass(), container_size, SIZE_OF_VECTOR_OF_OBJECT);
}
// This is the default constructor for a vector of objects
static inline o_Vector Vector(){
    return VectorSize(VECTOR_MIN_CAPACITY);
}
// If you wan't to define a container size for c variables, use this
static inline o_Vector VectorCSize(size_t container_size, size_t type_size){
    return ooc_new(VectorClass(), container_size, type_size);
}
// This macro is to help pass the type as a parameter directly, instead of sizeof
#define VectorCSizeHelper(container_size_, type_) VectorCSize(container_size_, sizeof(type_))
// This is the default constructor for a vector of c variables
#define VectorC(type_) VectorCSizeHelper(VECTOR_MIN_CAPACITY, type_)

/*------------------------------------------------*/
/*-------------- Interface Methods ---------------*/
/*------------------------------------------------*/
/*----------------- Clonable ---------------------*/
INTERFACE_METHOD_HEADER(VectorClass, M_CLONABLE_CLONE);
/*----------------- Iterable ---------------------*/
INTERFACE_METHOD_HEADER(VectorClass, M_ITERABLE_CREATE);
/*----------------- Collection -------------------*/
INTERFACE_METHOD_HEADER(VectorClass, M_COLLECTION_ADD);
INTERFACE_METHOD_HEADER(VectorClass, M_COLLECTION_ADD_ALL);
INTERFACE_METHOD_HEADER(VectorClass, M_COLLECTION_ADD_ALL_C);
INTERFACE_METHOD_HEADER(VectorClass, M_COLLECTION_ADD_ALL_C_POINTER);
INTERFACE_METHOD_HEADER(VectorClass, M_COLLECTION_CLEAR);
INTERFACE_METHOD_HEADER(VectorClass, M_COLLECTION_CONTAINS);
INTERFACE_METHOD_HEADER(VectorClass, M_COLLECTION_IS_EMPTY);
INTERFACE_METHOD_HEADER(VectorClass, M_COLLECTION_REMOVE);
INTERFACE_METHOD_HEADER(VectorClass, M_COLLECTION_REMOVE_ALL);
INTERFACE_METHOD_HEADER(VectorClass, M_COLLECTION_RETAIN_ALL);
INTERFACE_METHOD_HEADER(VectorClass, M_COLLECTION_SIZE);
INTERFACE_METHOD_HEADER(VectorClass, M_COLLECTION_ELEMENT_SIZE);
INTERFACE_METHOD_HEADER(VectorClass, M_COLLECTION_TO_ARRAY);
/*------------------- List ----------------------*/
INTERFACE_METHOD_HEADER(VectorClass, M_LIST_ADD);
INTERFACE_METHOD_HEADER(VectorClass, M_LIST_ADD_ALL);
INTERFACE_METHOD_HEADER(VectorClass, M_LIST_ADD_ALL_C);
INTERFACE_METHOD_HEADER(VectorClass, M_LIST_GET);
INTERFACE_METHOD_HEADER(VectorClass, M_LIST_INDEX_OF);
INTERFACE_METHOD_HEADER(VectorClass, M_LIST_LAST_INDEX_OF);
INTERFACE_METHOD_HEADER(VectorClass, M_LIST_REMOVE);
INTERFACE_METHOD_HEADER(VectorClass, M_LIST_SET);
INTERFACE_METHOD_HEADER(VectorClass, M_LIST_SUBLIST);

#endif /* OO_BASE_VECTOR_VECTOR_H_ */
