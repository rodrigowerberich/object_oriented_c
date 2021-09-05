/*
 * ooc.r
 *
 *  Created on: 28 de dez de 2018
 *      Author: lua
 */

#ifndef COMPONENTS_OO_BASE_OBJECT_OOC_R_
#define COMPONENTS_OO_BASE_OBJECT_OOC_R_

#include <ooc/ooc.h>
#include <ooc/ooc_macros.h>


struct ooc_method{
    const char* tag;
    ooc_method_t selector;
    ooc_method_t method;
};

typedef struct Object_r {
    uint32_t              magic;    // magic number to show that this is an object
    const struct Class_r* class;    // object's description
} Object_r;

typedef struct Class_r {
    const Object_r        _;       // class' description
    const char*           name;    // class' name
    const struct Class_r* super;   // class' super class
    size_t                size;    // class' object's size
    CLASS_DYNAMIC_METHOD(M_CTOR);
    CLASS_DYNAMIC_METHOD(M_DTOR);
    CLASS_DYNAMIC_METHOD(M_DIFFER);
} Class_r;

SUPER_DYNAMIC_METHOD(M_CTOR);
SUPER_DYNAMIC_METHOD(M_DTOR);
SUPER_DYNAMIC_METHOD(M_DIFFER);

#endif /* COMPONENTS_OO_BASE_OBJECT_OOC_R_ */
