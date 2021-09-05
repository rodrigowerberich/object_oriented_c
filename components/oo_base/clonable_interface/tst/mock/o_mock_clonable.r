/*
 * o_MockClonable.r
 *
 *  Created on: 8 de jan de 2019
 *      Author: lua
 */

#ifndef O_MOCK_CLONABLE_R__
#define O_MOCK_CLONABLE_R__

#include <ooc/object/ooc.r>
#include <o_mock_clonable.h>

typedef struct MockClonable_r{
    const Object_r _;             /* MockClonable : Object */
    int            number;
}MockClonable_r;

typedef struct MockClonableClass_r{
    const Class_r _;             /* MockClonableClass : Class*/
    CLASS_INTERFACE_METHOD(MockClonableClass, M_CLONABLE_CLONE);
}MockClonableClass_r;

SUPER_INTERFACE_METHOD(MockClonableClass, M_CLONABLE_CLONE);

#endif /* O_MOCK_CLONABLE_R__ */
