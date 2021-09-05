/*
 * itereable_interface.h
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */

#ifndef OO_BASE_ITERATOR_ITERABLE_INTERFACE_H_
#define OO_BASE_ITERATOR_ITERABLE_INTERFACE_H_

#include <ooc_macros.h>
#include <iterator.h>
/*------------------------------------------------*/
/*----- Interface methods declaration ------------*/
/*------------------------------------------------*/
// Creates an iterator object for the object it represents
#define M_ITERABLE_CREATE_DEF   o_Iterator, Iterable_create
#define M_ITERABLE_CREATE_ARG   const void* _self
#define M_ITERABLE_CREATE_PARAM             _self
INTERFACE_METHOD_DECLARATION(M_ITERABLE_CREATE);

#endif /* OO_BASE_ITERATOR_ITERABLE_INTERFACE_H_ */
