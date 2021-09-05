/*
 * tuple.h
 *
 *  Created on: 28 de jan de 2019
 *      Author: lua
 */

#ifndef OO_BASE_TUPLE_SIZED_OBJECT_H_
#define OO_BASE_TUPLE_SIZED_OBJECT_H_

#include <ooc.h>
#include <clonable_interface.h>

/*------------------------------------------------*/
/*----------- ClassVar declaration ---------------*/
/*------------------------------------------------*/
CLASS_DECLARATION(SizedObject);
CLASS_DECLARATION(SizedObjectClass);
/*------------------------------------------------*/
/*------------ Class constructors ----------------*/
/*------------------------------------------------*/
static inline o_SizedObject SizedObject(void* object, size_t object_size){
    return ooc_new(SizedObjectClass(), object, object_size);
}
// Returns the actual object underneath
void* SizedObject_value(o_SizedObject o_sized_object);
// Returns the size of the object underneath
int SizedObject_size(o_SizedObject o_sized_object);
/*------------------------------------------------*/
/*-------------- Interface Methods ---------------*/
/*------------------------------------------------*/
/*----------------- Clonable ---------------------*/
INTERFACE_METHOD_HEADER(SizedObjectClass, M_CLONABLE_CLONE);

#endif /* OO_BASE_TUPLE_SIZED_OBJECT_H_ */
