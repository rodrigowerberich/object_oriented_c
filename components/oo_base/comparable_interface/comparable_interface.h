/*
 * comparable_interface.h
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */

#ifndef OO_BASE_COMPARABLE_INTERFACE_COMPARABLE_INTERFACE_H_
#define OO_BASE_COMPARABLE_INTERFACE_COMPARABLE_INTERFACE_H_

#include <ooc_macros.h>

/*------------------------------------------------*/
/*----- Interface methods declaration ------------*/
/*------------------------------------------------*/
// Compares two different objects and destroys the second one
// The comparison must follow these rules:
//      If the first is greater than the second:  result > 0
//      If they are equal:                        result = 0
//      If the first is smaller than the second: result < 0
#define M_COMPARABLE_COMPARE_TO_DEF   int, Comparable_compareTo
#define M_COMPARABLE_COMPARE_TO_ARG   const void* _self, void* _destroyable_other
#define M_COMPARABLE_COMPARE_TO_PARAM       _self,       _destroyable_other
INTERFACE_METHOD_DECLARATION(M_COMPARABLE_COMPARE_TO);

#endif /* OO_BASE_COMPARABLE_INTERFACE_COMPARABLE_INTERFACE_H_ */
