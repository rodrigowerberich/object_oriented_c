/*
 * o_MockClonable.c
 *
 *  Created on: 8 de jan de 2019
 *      Author: lua
 */

#include <o_mock_clonable.h>
#include <o_mock_clonable.r>

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

#include <ooc/assert.h>
#include <ooc/malloc.h>

/*------------------------------------------------*/
/*-------------- DEFINE HELPERS ------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
/*------------------- Helper methods -------------*/
/*------------------------------------------------*/

/*------------------------------------------------*/
/*--------------- Class methods ------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
/*----------- Static linked methods --------------*/
/*------------------------------------------------*/

int MockClonable_getNumber(o_MockClonable _self){
    CAST(self, MockClonable);
    ASSERT(self, -1);
    return self->number;
}

/*-------------------------------------------------*/
/*----------- Dynamic linked methods --------------*/
/*-------------------------------------------------*/
INTERFACE_METHOD(MockClonableClass, NULL, M_CLONABLE_CLONE);
/*------------------------------------------------*/
/*------------- OVERWRITTEN METHODS --------------*/
/*------------------------------------------------*/
/*------------------- Object -------------------*/
static OVERWRITE_METHOD(MockClonable, M_CTOR){
    SUPER_CTOR(self, MockClonable);
    int number = va_arg(*app, int);
    self->number = number;
    return self;
}
static OVERWRITE_METHOD(MockClonable, M_CLONABLE_CLONE){
    CAST(self, MockClonable);
    ASSERT(self, NULL);
    return MockClonable(self->number);
}
/*------------------- MockClonable Class -------------------*/
static OVERWRITE_METHOD(MockClonableClass, M_CTOR){
    SUPER_CTOR(self, MockClonableClass);
    SELECTOR_LOOP(
        FIRST_INTERFACE_SELECTOR(MockClonableClass, M_CLONABLE_CLONE)
    )
}
/*-------------------------------*/
/*------- Initialization --------*/
/*-------------------------------*/
const void* MockClonable_d;
const void* initMockClonable() {
    return CLASS(
                MockClonableClassClass(),
                "MockClonable",
                ObjectClass(),
                sizeof(MockClonable_r),
                ARG(
                    LINK_METHOD(MockClonable, M_CTOR),
                    LINK_INTERFACE_METHOD(MockClonable, MockClonableClass, M_CLONABLE_CLONE)
                )
            );
}

const void* MockClonableClass_d;
const void* initMockClonableClass() {
    return CLASS(
                ClassClass(),
                "MockClonable",
                ClassClass(),
                sizeof(MockClonableClass_r),
                ARG(
                    LINK_METHOD(MockClonableClass, M_CTOR)
                )
            );
}

