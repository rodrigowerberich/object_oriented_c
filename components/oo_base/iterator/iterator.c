/*
 * iterator.c
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */


#include <iterator.h>
#include <iterator.r>
#include <lua_assert.h>

/*-------------------------------------------------*/
/*----------- Dynamic linked methods --------------*/
/*-------------------------------------------------*/
DYNAMIC_METHOD(IteratorClass, ,M_ITERATOR_FIRST);
DYNAMIC_METHOD(IteratorClass, ,M_ITERATOR_NEXT);
DYNAMIC_METHOD(IteratorClass, true ,M_ITERATOR_IS_DONE);
DYNAMIC_METHOD(IteratorClass, NULL,M_ITERATOR_CURR_ITEM);
/*------------------------------------------------*/
/*------------- OVERWRITTEN METHODS --------------*/
/*------------------------------------------------*/
/*-------------------- Class ---------------------*/
static OVERWRITE_METHOD(IteratorClass, M_CTOR){
	SUPER_CTOR(self, IteratorClass);
	SELECTOR_LOOP(
		FIRST_SELECTOR(M_ITERATOR_FIRST)
		ADD_SELECTOR(M_ITERATOR_NEXT)
		ADD_SELECTOR(M_ITERATOR_IS_DONE)
		ADD_SELECTOR(M_ITERATOR_CURR_ITEM)
	)
}
/*-------------------------------*/
/*------- Initialization --------*/
/*-------------------------------*/
// IteratorClass description object
const void* IteratorClass_d;
// Automatic initializer
const void* initIteratorClass(){
	return ooc_new(	ClassClass(),
			"IteratorClass",
			ClassClass(),
			sizeof(IteratorClass_r),
			LINK_METHOD(IteratorClass, M_CTOR),
			0);
}

