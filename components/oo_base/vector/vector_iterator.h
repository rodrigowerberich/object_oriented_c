/*
 * vector_iterator.h
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */

#ifndef OO_BASE_VECTOR_VECTOR_ITERATOR_H_
#define OO_BASE_VECTOR_VECTOR_ITERATOR_H_

#include <ooc.h>
#include <iterator.h>

// Class implementation of the Iterator interface for the vector class

/*------------------------------------------------*/
/*----------- ClassVar declaration ---------------*/
/*------------------------------------------------*/
CLASS_DECLARATION(VectorIterator);
/*------------------------------------------------*/
/*------------ Class constructors ----------------*/
/*------------------------------------------------*/
// Create a vector iterator from a buffer and a buffer size
// You should't call this directly, you should alway use the Iterable_create method on the vector
static inline o_VectorIterator VectorIterator(void** buffer, int buffer_size){
	return ooc_new(VectorIteratorClass(), buffer, buffer_size);
}



#endif /* OO_BASE_VECTOR_VECTOR_ITERATOR_H_ */
