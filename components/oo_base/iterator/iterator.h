/*
 * iterator.h
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */

#ifndef OO_BASE_ITERATOR_ITERATOR_H_
#define OO_BASE_ITERATOR_ITERATOR_H_

#include <ooc.h>
#include <stdbool.h>

/*------------------------------------------------*/
/*----------- ClassVar declaration ---------------*/
/*------------------------------------------------*/
// Iterator is an abstract class, there is no way
// to instanciate it
typedef void* o_Iterator;
CLASS_DECLARATION(IteratorClass);
#define for_iterator(_o_iterator) for(;!Iterator_isDone(_o_iterator);Iterator_next(_o_iterator))
/*------------------------------------------------*/
/*--------------- Class methods ------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
/*----------- Dynamic linked methods -------------*/
/*------------------------------------------------*/
// Returns to the first element of the iterator
#define M_ITERATOR_FIRST_DEF   void, Iterator_first
#define M_ITERATOR_FIRST_ARG   const void* _self
#define M_ITERATOR_FIRST_PARAM             _self
DYNAMIC_METHOD_HEADER(M_ITERATOR_FIRST);
// Advances to the next element of the iterator
#define M_ITERATOR_NEXT_DEF   void, Iterator_next
#define M_ITERATOR_NEXT_ARG   const void* _self
#define M_ITERATOR_NEXT_PARAM             _self
DYNAMIC_METHOD_HEADER(M_ITERATOR_NEXT);
// Checks if the iterator has reached its end
#define M_ITERATOR_IS_DONE_DEF 	 bool, Iterator_isDone
#define M_ITERATOR_IS_DONE_ARG   const void* _self
#define M_ITERATOR_IS_DONE_PARAM             _self
DYNAMIC_METHOD_HEADER(M_ITERATOR_IS_DONE);
// Get the actual object the iterator points to
#define M_ITERATOR_CURR_ITEM_DEF   void*, Iterator_currItem
#define M_ITERATOR_CURR_ITEM_ARG   const void* _self
#define M_ITERATOR_CURR_ITEM_PARAM             _self
DYNAMIC_METHOD_HEADER(M_ITERATOR_CURR_ITEM);

#endif /* OO_BASE_ITERATOR_ITERATOR_H_ */
