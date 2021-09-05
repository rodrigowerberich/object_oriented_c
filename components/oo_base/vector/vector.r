/*
 * vector.r
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */

#ifndef OO_BASE_VECTOR_VECTOR_R_
#define OO_BASE_VECTOR_VECTOR_R_

#include <ooc.r>
#include <vector.h>

typedef struct Vector_r{
    const Object_r _; 				/* Vector : Object */
    void**         array_buffer;	/* The actual array that holds the vector elements */
    int            element_size;	/* The size of the type of object this vector holds  */
    int            buffer_size;		/* The total amount of buffer currently allocated  */
    int            curr_size;		/* The number of elements inside the buffer  */
} Vector_r;


typedef struct VectorClass_r{
	Class_r _;
	/*----------------- Clonable ---------------------*/
	CLASS_INTERFACE_METHOD(VectorClass, M_CLONABLE_CLONE);
	/*----------------- Iterable ---------------------*/
	CLASS_INTERFACE_METHOD(VectorClass, M_ITERABLE_CREATE);
	/*----------------- Collection -------------------*/
	CLASS_INTERFACE_METHOD(VectorClass, M_COLLECTION_ADD);
	CLASS_INTERFACE_METHOD(VectorClass, M_COLLECTION_ADD_ALL);
    CLASS_INTERFACE_METHOD(VectorClass, M_COLLECTION_ADD_ALL_C);
    CLASS_INTERFACE_METHOD(VectorClass, M_COLLECTION_ADD_ALL_C_POINTER);
	CLASS_INTERFACE_METHOD(VectorClass, M_COLLECTION_CLEAR);
	CLASS_INTERFACE_METHOD(VectorClass, M_COLLECTION_CONTAINS);
	CLASS_INTERFACE_METHOD(VectorClass, M_COLLECTION_IS_EMPTY);
	CLASS_INTERFACE_METHOD(VectorClass, M_COLLECTION_REMOVE);
	CLASS_INTERFACE_METHOD(VectorClass, M_COLLECTION_REMOVE_ALL);
	CLASS_INTERFACE_METHOD(VectorClass, M_COLLECTION_RETAIN_ALL);
	CLASS_INTERFACE_METHOD(VectorClass, M_COLLECTION_SIZE);
	CLASS_INTERFACE_METHOD(VectorClass, M_COLLECTION_ELEMENT_SIZE);
	CLASS_INTERFACE_METHOD(VectorClass, M_COLLECTION_TO_ARRAY);
	/*------------------- List ----------------------*/
	CLASS_INTERFACE_METHOD(VectorClass, M_LIST_ADD);
	CLASS_INTERFACE_METHOD(VectorClass, M_LIST_ADD_ALL);
    CLASS_INTERFACE_METHOD(VectorClass, M_LIST_ADD_ALL_C);
	CLASS_INTERFACE_METHOD(VectorClass, M_LIST_GET);
	CLASS_INTERFACE_METHOD(VectorClass, M_LIST_INDEX_OF);
	CLASS_INTERFACE_METHOD(VectorClass, M_LIST_LAST_INDEX_OF);
	CLASS_INTERFACE_METHOD(VectorClass, M_LIST_REMOVE);
	CLASS_INTERFACE_METHOD(VectorClass, M_LIST_SET);
	CLASS_INTERFACE_METHOD(VectorClass, M_LIST_SUBLIST);
}VectorClass_r;

/*----------------- Clonable ---------------------*/
SUPER_INTERFACE_METHOD(VectorClass, M_CLONABLE_CLONE);
/*----------------- Iterable ---------------------*/
SUPER_INTERFACE_METHOD(VectorClass, M_ITERABLE_CREATE);
/*----------------- Collection -------------------*/
SUPER_INTERFACE_METHOD(VectorClass, M_COLLECTION_ADD);
SUPER_INTERFACE_METHOD(VectorClass, M_COLLECTION_ADD_ALL);
SUPER_INTERFACE_METHOD(VectorClass, M_COLLECTION_ADD_ALL_C);
SUPER_INTERFACE_METHOD(VectorClass, M_COLLECTION_ADD_ALL_C_POINTER);
SUPER_INTERFACE_METHOD(VectorClass, M_COLLECTION_CLEAR);
SUPER_INTERFACE_METHOD(VectorClass, M_COLLECTION_CONTAINS);
SUPER_INTERFACE_METHOD(VectorClass, M_COLLECTION_IS_EMPTY);
SUPER_INTERFACE_METHOD(VectorClass, M_COLLECTION_REMOVE);
SUPER_INTERFACE_METHOD(VectorClass, M_COLLECTION_REMOVE_ALL);
SUPER_INTERFACE_METHOD(VectorClass, M_COLLECTION_RETAIN_ALL);
SUPER_INTERFACE_METHOD(VectorClass, M_COLLECTION_SIZE);
SUPER_INTERFACE_METHOD(VectorClass, M_COLLECTION_ELEMENT_SIZE);
SUPER_INTERFACE_METHOD(VectorClass, M_COLLECTION_TO_ARRAY);
/*------------------- List ----------------------*/
SUPER_INTERFACE_METHOD(VectorClass, M_LIST_ADD);
SUPER_INTERFACE_METHOD(VectorClass, M_LIST_ADD_ALL);
SUPER_INTERFACE_METHOD(VectorClass, M_LIST_ADD_ALL_C);
SUPER_INTERFACE_METHOD(VectorClass, M_LIST_GET);
SUPER_INTERFACE_METHOD(VectorClass, M_LIST_INDEX_OF);
SUPER_INTERFACE_METHOD(VectorClass, M_LIST_LAST_INDEX_OF);
SUPER_INTERFACE_METHOD(VectorClass, M_LIST_REMOVE);
SUPER_INTERFACE_METHOD(VectorClass, M_LIST_SET);
SUPER_INTERFACE_METHOD(VectorClass, M_LIST_SUBLIST);
#endif /* OO_BASE_VECTOR_VECTOR_R_ */
