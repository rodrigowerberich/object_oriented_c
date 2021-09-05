/*
 * o_string.r
 *
 *  Created on: 8 de jan de 2019
 *      Author: lua
 */

#ifndef COMPONENTS_OO_BASE_O_STRING_O_STRING_R_
#define COMPONENTS_OO_BASE_O_STRING_O_STRING_R_

#include <ooc.r>
#include <o_string.h>

typedef struct String_r{
    const Object_r _;             /* String : Object */
    char*          buffer;
    int            str_size;
    int            buffer_size;
}String_r;

typedef struct StringClass_r{
    const Class_r _;             /* StringClass : Class*/
    CLASS_INTERFACE_METHOD(StringClass, M_COMPARABLE_COMPARE_TO);
    CLASS_INTERFACE_METHOD(StringClass, M_CLONABLE_CLONE);
}StringClass_r;

SUPER_INTERFACE_METHOD(StringClass, M_COMPARABLE_COMPARE_TO);
SUPER_INTERFACE_METHOD(StringClass, M_CLONABLE_CLONE);

#endif /* COMPONENTS_OO_BASE_O_STRING_O_STRING_R_ */
