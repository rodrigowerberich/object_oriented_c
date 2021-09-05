/*
 * vector_iterator.c
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */


#include <vector_iterator.h>
#include <vector_iterator.r>
#include <lua_assert.h>

/*------------------------------------------------*/
/*------------- OVERWRITTEN METHODS --------------*/
/*------------------------------------------------*/
static OVERWRITE_METHOD(VectorIterator, M_CTOR){
	SUPER_CTOR(self, VectorIterator);
	self->buffer = va_arg(*app, void**);
	self->buffer_size = va_arg(*app, int);
	self->curr_position = 0;
	return self;
}

static OVERWRITE_METHOD(VectorIterator, M_ITERATOR_FIRST){
	CAST(self, VectorIterator);
	ASSERT(self, );
	self->curr_position = 0;
}

static OVERWRITE_METHOD(VectorIterator, M_ITERATOR_NEXT){
	CAST(self, VectorIterator);
	ASSERT(self, );
	if(self->curr_position < self->buffer_size){
		self->curr_position += 1;
	}
}

static OVERWRITE_METHOD(VectorIterator, M_ITERATOR_IS_DONE){
	CAST(self, VectorIterator);
	ASSERT(self, false);
	return (self->curr_position == self->buffer_size);
}

static OVERWRITE_METHOD(VectorIterator, M_ITERATOR_CURR_ITEM){
	CAST(self, VectorIterator);
	ASSERT(self, NULL);
	if(self->curr_position < self->buffer_size){
		return self->buffer[self->curr_position];
	}
	return NULL;
}

/*------------------------------------------------*/
/*------- Class descriptor and initializer -------*/
/*------------------------------------------------*/	
const void* VectorIterator_d;

const void* initVectorIterator(){
	return ooc_new(	IteratorClassClass(),
			"VectorIterator",
			ObjectClass(),
			sizeof(VectorIterator_r),
			LINK_METHOD(VectorIterator, M_CTOR),
			LINK_METHOD(VectorIterator, M_ITERATOR_FIRST),
			LINK_METHOD(VectorIterator, M_ITERATOR_NEXT),
			LINK_METHOD(VectorIterator, M_ITERATOR_IS_DONE),
			LINK_METHOD(VectorIterator, M_ITERATOR_CURR_ITEM),
			0);
}
