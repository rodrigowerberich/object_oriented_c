/*
 * vector_iterator.r
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */

#ifndef OO_BASE_VECTOR_VECTOR_ITERATOR_R_
#define OO_BASE_VECTOR_VECTOR_ITERATOR_R_

#include <ooc.r>
#include <vector_iterator.h>


typedef struct VectorIterator_r{
    Object_r _;             // The base object
    void** 	 buffer; 		// The buffer over which we will iterate
    int 	 buffer_size; 	// The buffer size
    int      curr_position; // The current position of the iterator
}VectorIterator_r;

#endif /* OO_BASE_VECTOR_VECTOR_ITERATOR_R_ */
