/*
 * sized_object.r
 *
 *  Created on: 28 de jan de 2019
 *      Author: lua
 */

#ifndef OO_BASE_TUPLE_SIZED_OBJECT_R_
#define OO_BASE_TUPLE_SIZED_OBJECT_R_

#include <ooc.r>
#include <sized_object.h>

typedef struct SizedObject_r{
    const Object_r _;               /* SizedObject : Object */
    void*          object;          /* A pointer to the object itself */
    int            object_size;     /* The size of the object being pointed to */
} SizedObject_r;


typedef struct SizedObjectClass_r{
	Class_r _;
	/*----------------- Clonable ---------------------*/
	CLASS_INTERFACE_METHOD(SizedObjectClass, M_CLONABLE_CLONE);
}SizedObjectClass_r;

/*----------------- Clonable ---------------------*/
SUPER_INTERFACE_METHOD(SizedObjectClass, M_CLONABLE_CLONE);

#endif /* OO_BASE_TUPLE_SIZED_OBJECT_R_ */
