/*
 * clonable_interface.h
 *
 *  Created on: 4 de jan de 2019
 *      Author: lua
 */

#ifndef OO_BASE_CLONEABLE_INTERFACE_H_
#define OO_BASE_CLONABLE_INTERFACE_H_

#include <ooc/ooc_macros.h>

/*------------------------------------------------*/
/*----- Interface methods declaration ------------*/
/*------------------------------------------------*/
// Creates a clone from the object
#define M_CLONABLE_CLONE_DEF   void*, Clonable_clone
#define M_CLONABLE_CLONE_ARG   const void* _self
#define M_CLONABLE_CLONE_PARAM       _self
INTERFACE_METHOD_DECLARATION(M_CLONABLE_CLONE);
/*------------------------------------------------*/
/*----- Interface helper methods declaration -----*/
/*------------------------------------------------*/
// If the pointer of self is an ooc object,
// the Clonable_clone function is called, otherwise,
// a memcpy of element_size is performed
void* Clonable_safeClone(const void * self, int element_size);
/*------------------------------------------------*/
/*----- Interface helper defines declaration -----*/
/*------------------------------------------------*/
#define Clonable_cloneC(pointer_, type_) ((type_*) Clonable_safeClone(pointer_, sizeof(type_)))
// This defines are used for convinience 
#define OOC_CLONE(self_) Clonable_clone(self_)
#define OOC_CLONE_S(self_, size_) Clonable_safeClone(self_, size_)
#define OOC_CLONE_C(pointer_, type_) Clonable_cloneC(pointer_, type_)

#endif /* OO_BASE_CLONEABLE_INTERFACE_H_ */
