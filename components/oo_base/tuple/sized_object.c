/*
 * sized_object.c
 *
 *  Created on: 28 de jan de 2019
 *      Author: lua
 */

#include <sized_object.r>
#include <sized_object.h>
#include <lua_assert.h>

/*-------------------------------------------------*/
/*------------ Static linked methods --------------*/
/*-------------------------------------------------*/
void* SizedObject_value(o_SizedObject _self){
	CAST(self, SizedObject);
	ASSERT(self, NULL);
	return self->object;
}
int SizedObject_size(o_SizedObject _self){
	CAST(self, SizedObject);
	ASSERT(self, -1);
	return self->object_size;
}
/*-------------------------------------------------*/
/*----------- Dynamic linked methods --------------*/
/*-------------------------------------------------*/
/*----------------- Clonable ---------------------*/
INTERFACE_METHOD(SizedObjectClass, NULL,  M_CLONABLE_CLONE);
/*------------------------------------------------*/
/*------------- OVERWRITTEN METHODS --------------*/
/*------------------------------------------------*/
static OVERWRITE_METHOD(SizedObject, M_CTOR){
	SUPER_CTOR(self, SizedObject);
	ASSERT(self, NULL);
	self->object = va_arg(*app, void*);
	self->object_size = va_arg(*app, int);
	return self;
}
static OVERWRITE_METHOD(SizedObject, M_DTOR){
	SUPER_DTOR(self, SizedObject);
	ASSERT(self, NULL);
	OOC_DELETE(self->object);
	return self;
}

// --------- Clonable Interface
static OVERWRITE_METHOD(SizedObject, M_CLONABLE_CLONE){
    CAST(self, SizedObject);
    ASSERT(self, NULL);
    return SizedObject(Clonable_safeClone(self->object, self->object_size), self->object_size);
}

// Sized Object Class ---------------------------------

static OVERWRITE_METHOD(SizedObjectClass, M_CTOR){
	SUPER_CTOR(self, SizedObjectClass);
	SELECTOR_LOOP(
		FIRST_INTERFACE_SELECTOR(SizedObjectClass, M_CLONABLE_CLONE)
	)
}

/*------------------------------------------------*/
/*------- Class descriptor and initializer -------*/
/*------------------------------------------------*/

const void* SizedObject_d;
const void* SizedObjectClass_d;

const void* initSizedObject(){
	return ooc_new(	SizedObjectClassClass(),
			"SizedObject",
			ObjectClass(),
			sizeof(SizedObject_r),
			LINK_METHOD(SizedObject, M_CTOR),
			LINK_METHOD(SizedObject, M_DTOR),
			LINK_INTERFACE_METHOD(SizedObject, SizedObjectClass, M_CLONABLE_CLONE),
			0);
}

const void* initSizedObjectClass(){
	return ooc_new(	ClassClass(),
			"SizedObjectClass",
			ClassClass(),
			sizeof(SizedObjectClass_r),
			LINK_METHOD(SizedObjectClass, M_CTOR),
			0);
}
