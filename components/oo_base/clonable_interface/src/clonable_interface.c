/*
 * cloneable_interface.c
 *
 *  Created on: 6 de jan de 2019
 *      Author: lua
 */

#include <ooc/clonable_interface.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ooc/ooc.h>
#include <ooc/malloc.h>


/*------------------------------------------------*/
/*----- Interface methods implementation ---------*/
/*------------------------------------------------*/
INTERFACE_METHOD_IMPLEMENTATION(NULL, M_CLONABLE_CLONE);
/*------------------------------------------------*/
/*---- Interface helper methods implementation ---*/
/*------------------------------------------------*/
void* Clonable_safeClone(const void * self, int element_size){
    if(ooc_isObject(self)){
        return Clonable_clone(self);
    }else{
        void* new = ooc_malloc(element_size);
        memcpy(new, self, element_size);
		return new;
    }
}
