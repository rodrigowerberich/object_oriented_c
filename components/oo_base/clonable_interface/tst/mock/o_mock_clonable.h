/*
 * o_MockClonable.h
 *
 *  Created on: 8 de jan de 2019
 *      Author: lua
 */

#ifndef O_MOCK_CLONABLE_H__
#define O_MOCK_CLONABLE_H__

/*
 * vector.h
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */

#include <ooc/ooc.h>
#include <ooc/clonable_interface.h>

/*------------------------------------------------*/
/*----------- ClassVar declaration ---------------*/
/*------------------------------------------------*/
CLASS_DECLARATION(MockClonable);
CLASS_DECLARATION(MockClonableClass);
/*------------------------------------------------*/
/*------------ Class constructors ----------------*/
/*------------------------------------------------*/
static inline o_MockClonable MockClonable(int number){ return ooc_new(MockClonableClass(), number, 0);}
/*------------------------------------------------*/
/*--------------- Class methods ------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
/*----------- Static linked methods --------------*/
/*------------------------------------------------*/

int MockClonable_getNumber(o_MockClonable _self);

/*------------------------------------------------*/
/*------------- Interface methods ----------------*/
/*------------------------------------------------*/
INTERFACE_METHOD_HEADER(MockClonableClass, M_CLONABLE_CLONE);
#endif /* O_MOCK_CLONABLE_H__ */
