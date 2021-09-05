/*
 * vector.c
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */


#include <clonable_interface.h>
#include <vector.h>
#include <vector.r>
#include <comparable_interface.h>
#include <lua_assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <vector_iterator.h>
#include <ooc.h>
#include <lua_malloc.h>

/*------------------------------------------------*/
/*------------------- Helper methods -------------*/
/*------------------------------------------------*/

// Increases the buffer size to be able to fit the new size
// Be careful calling this, if new_size is smaller than
// double the current buffer size, the buffer will double
// otherwise it will become 1.5 times the new_size
static void vector_expand(Vector_r* vector, size_t new_size) {
    if (2 * vector->buffer_size > new_size) {
        vector->buffer_size = 2 * vector->buffer_size;
    } else {
        vector->buffer_size = 1.5 * new_size;
    }
    vector->array_buffer = lua_realloc(vector->array_buffer, vector->buffer_size*sizeof(void*));
}

// Adds to vector curr_size the extra space and expands the
// vector if necessary
static void vector_add_space(Vector_r* vector, size_t extra_space){
    vector->curr_size += extra_space;
    if (vector->buffer_size <= vector->curr_size) {
        vector_expand(vector, vector->curr_size);
    }
}
// Changes the contents of two position of the vector
static void vector_swap(Vector_r* vector, size_t pos1, size_t pos2){
    void** current = vector->array_buffer+pos1;
    void** ooc_new = vector->array_buffer+pos2;
    void* temp = *current;
    *current = *ooc_new;
    *ooc_new = temp;
}
/*-------------------------------------------------*/
/*----------- Dynamic linked methods --------------*/
/*-------------------------------------------------*/
/*----------------- Clonable ---------------------*/
INTERFACE_METHOD(VectorClass, NULL,  M_CLONABLE_CLONE);
/*----------------- Iterable ---------------------*/
INTERFACE_METHOD(VectorClass, NULL, M_ITERABLE_CREATE);
/*----------------- Collection -------------------*/
INTERFACE_METHOD(VectorClass, false, M_COLLECTION_ADD);
INTERFACE_METHOD(VectorClass, false, M_COLLECTION_ADD_ALL);
INTERFACE_METHOD(VectorClass, false, M_COLLECTION_ADD_ALL_C);
INTERFACE_METHOD(VectorClass, false, M_COLLECTION_ADD_ALL_C_POINTER);
INTERFACE_METHOD(VectorClass, ,      M_COLLECTION_CLEAR);
INTERFACE_METHOD(VectorClass, false, M_COLLECTION_CONTAINS);
INTERFACE_METHOD(VectorClass, false, M_COLLECTION_IS_EMPTY);
INTERFACE_METHOD(VectorClass, false, M_COLLECTION_REMOVE);
INTERFACE_METHOD(VectorClass, false, M_COLLECTION_REMOVE_ALL);
INTERFACE_METHOD(VectorClass, false, M_COLLECTION_RETAIN_ALL);
INTERFACE_METHOD(VectorClass, -1,    M_COLLECTION_SIZE);
INTERFACE_METHOD(VectorClass, 0,     M_COLLECTION_ELEMENT_SIZE);
INTERFACE_METHOD(VectorClass, NULL,  M_COLLECTION_TO_ARRAY);
/*------------------- List ----------------------*/
INTERFACE_METHOD(VectorClass, false, M_LIST_ADD);
INTERFACE_METHOD(VectorClass, false, M_LIST_ADD_ALL);
INTERFACE_METHOD(VectorClass, false, M_LIST_ADD_ALL_C);
INTERFACE_METHOD(VectorClass, NULL,  M_LIST_GET);
INTERFACE_METHOD(VectorClass, -1,    M_LIST_INDEX_OF);
INTERFACE_METHOD(VectorClass, -1,    M_LIST_LAST_INDEX_OF);
INTERFACE_METHOD(VectorClass, false, M_LIST_REMOVE);
INTERFACE_METHOD(VectorClass, false, M_LIST_SET);
INTERFACE_METHOD(VectorClass, NULL,  M_LIST_SUBLIST);
/*------------------------------------------------*/
/*------------- OVERWRITTEN METHODS --------------*/
/*------------------------------------------------*/
static OVERWRITE_METHOD(Vector, M_CTOR){
	SUPER_CTOR(self, Vector);
	ASSERT(self, NULL);
	self->buffer_size = va_arg(*app, int) + VECTOR_MIN_CAPACITY;
	self->element_size = va_arg(*app, int);
	self->array_buffer = lua_malloc(self->buffer_size*sizeof(void*));
	self->curr_size = 0;
	return self;
}
static OVERWRITE_METHOD(Vector, M_DTOR){
	SUPER_DTOR(self, Vector);
	ASSERT(self, NULL);
	for(int i = 0; i < self->curr_size; i++){
		void* element = self->array_buffer[i];
		OOC_DELETE(element);
	}
	OOC_DELETE(self->array_buffer);
	return self;
}

// --------- Clonable Interface
static OVERWRITE_METHOD(Vector, M_CLONABLE_CLONE){
    CAST(self, Vector);
    ASSERT(self, NULL);
    o_Vector clone_vector = VectorCSize(self->buffer_size, self->element_size);
    Collection_addAll(clone_vector, self);
    return clone_vector;
}

// --------- Iterable Interface
static OVERWRITE_METHOD(Vector, M_ITERABLE_CREATE){
    CAST(self, Vector);
    ASSERT(self, NULL);
    return VectorIterator(self->array_buffer, self->curr_size);
}

// --------- Collection Interface
static OVERWRITE_METHOD(Vector, M_COLLECTION_ADD){
	CAST(self, Vector);
	ASSERT(self, false);
	int old_size = self->curr_size;
	vector_add_space(self, 1);
	self->array_buffer[old_size] = _o_element;
	return true;
}

static OVERWRITE_METHOD(Vector, M_COLLECTION_ADD_ALL){
	CAST(self, Vector);
	o_Iterator o_iterator = Iterable_create(_o_collection);
	ASSERT(self && o_iterator, false);
	while(!Iterator_isDone(o_iterator)){
		void* element = Iterator_currItem(o_iterator);
		Vector_Collection_add(self, Clonable_safeClone(element, self->element_size));
		Iterator_next(o_iterator);
	}
	OOC_DELETE(o_iterator);
	return true;
}

static OVERWRITE_METHOD(Vector, M_COLLECTION_ADD_ALL_C){
    CAST(self, Vector);
    ASSERT(self, false);
    for( int i = 0; i < size_of_vector; i++ ){
        Vector_Collection_add(self, Clonable_safeClone(array+(i*size_of_element), size_of_element));
    }
    return true;
}

static OVERWRITE_METHOD(Vector, M_COLLECTION_ADD_ALL_C_POINTER){
    CAST(self, Vector);
    ASSERT(self, false);
    for( int i = 0; i < size_of_vector; i++ ){
        Vector_Collection_add(self, Clonable_safeClone(array[i], size_of_element));
    }
    return true;
}

static OVERWRITE_METHOD(Vector, M_COLLECTION_CLEAR){
    CAST(self, Vector);
    ASSERT(self, );
    for(int i=0; i < self->curr_size; i++){
    	OOC_DELETE(self->array_buffer[i]);
    }
    self->curr_size = 0;
}

static OVERWRITE_METHOD(Vector, M_LIST_INDEX_OF); // Forward declaration

static OVERWRITE_METHOD(Vector, M_COLLECTION_CONTAINS){
    return (Vector_List_indexOf(_self, _o_element) != -1);
}

static OVERWRITE_METHOD(Vector, M_COLLECTION_IS_EMPTY){
    CAST(self, Vector);
    ASSERT(self, 1);
    return self->curr_size == 0;
}
static OVERWRITE_METHOD(Vector, M_COLLECTION_REMOVE){
    CAST(self, Vector);
    ASSERT(self, false);
    bool removed = false;
	bool is_same_pointer = false;
    if(ooc_isObject(_o_element)){
        CHECK_INTERFACE(compare, _o_element, M_COMPARABLE_COMPARE_TO);
    	CHECK_INTERFACE(clone,_o_element ,M_CLONABLE_CLONE);
    	bool is_comparable = compare != NULL;
		bool is_cloneable = clone != NULL;
		for(int i=0; i < self->curr_size; i++){
	    	if(is_comparable && is_cloneable){
	    		if(compare(self->array_buffer[i], clone(_o_element)) == 0){
	    			OOC_DELETE(self->array_buffer[i]);
	    			removed = true;
	    		}
	    	}else{
				if(!ooc_differ(_o_element, self->array_buffer[i])){
					OOC_DELETE(self->array_buffer[i]);
					removed = true;
				}
	    	}
	    }
    }else{
        for(int i=0; i < self->curr_size; i++){
			if(memcmp(self->array_buffer[i], _o_element, self->element_size) == 0){
				if(self->array_buffer[i] == _o_element){
					is_same_pointer = true;
				}
				OOC_DELETE(self->array_buffer[i]);
				removed = true;
			}
        }
    }
    if(removed){
        int first_null_position = -1;
        for(int i = 0; i < self->curr_size; i++){
            if(self->array_buffer[i] == NULL){
    			if(first_null_position == -1){
    				first_null_position = i;
    			}
    		}else if(first_null_position != -1){
    				vector_swap(self, first_null_position, i);
    				first_null_position += 1;
    		}
    	}
        self->curr_size = first_null_position;
        if(is_same_pointer){
			OOC_NULLIFY(_o_element);
		}else{
			OOC_DELETE(_o_element);
		}

        return true;
    }
    OOC_DELETE(_o_element);
    return false;
}

static OVERWRITE_METHOD(Vector, M_COLLECTION_REMOVE_ALL){
	CAST(self, Vector);
	o_Iterator o_iterator = Iterable_create(_o_collection);
	ASSERT(self && o_iterator, false);
	while(!Iterator_isDone(o_iterator)){
	    void* element = Iterator_currItem(o_iterator);
	    void* element1 = Clonable_safeClone(element, self->element_size);
	    Vector_Collection_remove(self, element1);
	    Iterator_next(o_iterator);
	}
	OOC_DELETE(o_iterator);
	return true;
}

static OVERWRITE_METHOD(Vector, M_COLLECTION_RETAIN_ALL){
	CAST(self, Vector);
	o_Vector o_new_vector = ooc_new(VectorClass(), self->buffer_size, self->element_size);
	o_Iterator o_iterator = Iterable_create(self);
	ASSERT(self && o_iterator, false);
	bool added = false;
	while(!Iterator_isDone(o_iterator)){
		void* element = Iterator_currItem(o_iterator);
		if(Vector_Collection_contains(_o_collection, Clonable_safeClone(element, self->element_size))){
			Vector_Collection_add(o_new_vector, Clonable_safeClone(element, self->element_size));
			added = true;
		}
		Iterator_next(o_iterator);
	}
	OOC_DELETE(o_iterator);
	if(added){
		Vector_Collection_clear(self);
		Vector_Collection_addAll(self, o_new_vector);
		OOC_DELETE(o_new_vector);
		return true;
	}
	OOC_DELETE(o_new_vector);
	return false;
}

static OVERWRITE_METHOD(Vector, M_COLLECTION_SIZE){
    CAST(self, Vector);
	ASSERT(self, 0);
    return self->curr_size;
}

static OVERWRITE_METHOD(Vector, M_COLLECTION_ELEMENT_SIZE){
    CAST(self, Vector);
	ASSERT(self, 0);
    return self->element_size;
}

static OVERWRITE_METHOD(Vector, M_COLLECTION_TO_ARRAY){
    CAST(self, Vector);
	ASSERT(self, 0);
	if(!Vector_Collection_isEmpty(self)){
		void** copy_array = lua_malloc(self->curr_size*sizeof(void*));
		for(int i=0; i < self->curr_size; i++){
		    copy_array[i] = Clonable_safeClone(self->array_buffer[i], self->element_size);
		}
		*new_array_size = self->curr_size;
	    return copy_array;
	}
	*new_array_size = -1;
	return NULL;
}

// List interface ------------------------------------------------

static OVERWRITE_METHOD(Vector, M_LIST_ADD){
    CAST(self, Vector);
    ASSERT(self, false);
    if( (index < 0) || (index > self->curr_size)){
        OOC_DELETE(_o_element);
        return false;
    }
    int old_size = self->curr_size;
    vector_add_space(self, 1);
    if(self->buffer_size < self->curr_size+2){
        vector_expand(self, self->curr_size+1);
    }
    for(int i=old_size-1;  i >= (int) index+1; i--){
        vector_swap(self, i, i+1);
    }
    vector_swap(self, index, index+1);
    self->array_buffer[index] = _o_element;
    return true;
}

static OVERWRITE_METHOD(Vector, M_LIST_ADD_ALL){
    CAST(self, Vector);
    ASSERT(self, false);
    if( (index < 0) || (index > self->curr_size)){
        return false;
    }
    int old_size = self->curr_size;
    int other_size = Collection_size(_o_collection);
    vector_add_space(self, other_size);
    if(self->buffer_size < self->curr_size+2*other_size){
        vector_expand(self, self->curr_size+other_size);
    }
    for(int i=old_size-1;  i >= (index+other_size); i--){
        vector_swap(self, i, i+other_size);
    }
    o_Iterator o_iterator = Iterable_create(_o_collection);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        vector_swap(self, i+index, i+index+other_size);
        void* element = Iterator_currItem(o_iterator);
        self->array_buffer[i+index] = Clonable_safeClone(element, self->element_size);
    }
    OOC_DELETE(o_iterator);
    return true;
}

static OVERWRITE_METHOD(Vector, M_LIST_ADD_ALL_C){
    CAST(self, Vector);
    ASSERT(self, false);
    if(index < 0){
        return false;
    }
    if(index >= self->curr_size){
        index = ( self->curr_size == 0 )? 0 : (self->curr_size);
    }
    size_t old_size = self->curr_size;
    int conv_size = size_of_vector;
    vector_add_space(self, size_of_vector);
    if(self->buffer_size < self->curr_size+2*size_of_vector){
        vector_expand(self, self->curr_size+size_of_vector);
    }
    for(int i=old_size-1;  i >= index+conv_size; i--){
        vector_swap(self, i, i+size_of_vector);
    }
    for(int i=0; i < size_of_vector; i++){
        vector_swap(self, (i+index), (i+index+size_of_vector));
        self->array_buffer[i+index] = Clonable_safeClone(array+(i*self->element_size), self->element_size);
    }
    return true;
}

static OVERWRITE_METHOD(Vector, M_LIST_GET){
    CAST(self, Vector);
	ASSERT(self && (index < self->curr_size), NULL);
	return self->array_buffer[index];
}

static OVERWRITE_METHOD(Vector, M_LIST_INDEX_OF){
	CAST(self, Vector);
	ASSERT(self, -1);
	if(ooc_isObject(_o_element)){
		CHECK_INTERFACE(compare, _o_element, M_COMPARABLE_COMPARE_TO);
		CHECK_INTERFACE(clone, _o_element, M_CLONABLE_CLONE);
		bool is_comparable = compare != NULL;
		bool is_cloneable = clone != NULL;
		for(int i=0; i < self->curr_size; i++){
			if(is_comparable && is_cloneable){
				if(compare(self->array_buffer[i], clone(_o_element)) == 0){
				    OOC_DELETE(_o_element);
					return i;
				}
			}else{
			    // Do not delete in this case, because they are
			    // exactly the same pointer!
				if(!ooc_differ(_o_element, self->array_buffer[i])){
					return i;
				}
			}
		}
	}else{
		for(int i=0; i < self->curr_size; i++){
			if(memcmp(self->array_buffer[i], _o_element, self->element_size) == 0){
				OOC_DELETE(_o_element);
				return i;
			}
		}
	}
	OOC_DELETE(_o_element);
	return -1;
}

static OVERWRITE_METHOD(Vector, M_LIST_LAST_INDEX_OF){
	CAST(self, Vector);
	ASSERT(self, -1);
	if(ooc_isObject(_o_element)){
		CHECK_INTERFACE(compare, _o_element, M_COMPARABLE_COMPARE_TO);
		CHECK_INTERFACE(clone, _o_element, M_CLONABLE_CLONE);
		bool is_comparable = compare != NULL;
		bool is_cloneable = clone != NULL;
		for(int i=(self->curr_size-1); i > -1; i--){
			if(is_comparable && is_cloneable){
				if(compare(self->array_buffer[i], clone(_o_element)) == 0){
					OOC_DELETE(_o_element);
					return i;
				}
			}else{
				if(!ooc_differ(_o_element, self->array_buffer[i])){
					OOC_DELETE(_o_element);
					return i;
				}
			}
		}
	}else{
		for(int i=(self->curr_size-1); i > -1; i--){
			if(memcmp(self->array_buffer[i], _o_element, self->element_size) == 0){
				OOC_DELETE(_o_element);
				return i;
			}
		}
	}
	OOC_DELETE(_o_element);
	return -1;
}

static OVERWRITE_METHOD(Vector, M_LIST_REMOVE){
	CAST(self, Vector);
	ASSERT(self && (index < self->curr_size), false);
	OOC_DELETE(self->array_buffer[index]);
	 for(int i = index; i < self->curr_size; i++){
		vector_swap(self, i, i+1);
	}
	self->curr_size -= 1;
	return true;
}

static OVERWRITE_METHOD(Vector, M_LIST_SET){
	CAST(self, Vector);
	ASSERT(self && (index < self->curr_size), false);
	OOC_DELETE(self->array_buffer[index]);
	self->array_buffer[index] = _o_new_element;
	return true;
}

static OVERWRITE_METHOD(Vector, M_LIST_SUBLIST){
	CAST(self, Vector);
	ASSERT(self && (fromIndex <= toIndex) && (toIndex < self->curr_size), false);
	o_Vector o_sub_vector = ooc_new(VectorClass(), (toIndex-fromIndex)+1, self->element_size);
	for(int i=fromIndex; i < toIndex+1; i++){
	    Vector_Collection_add(o_sub_vector, Clonable_safeClone(self->array_buffer[i], self->element_size));
	}
	return o_sub_vector;
}

// VectorClass ------------------------------------------------

static OVERWRITE_METHOD(VectorClass, M_CTOR){
	SUPER_CTOR(self, VectorClass);
	SELECTOR_LOOP(
		FIRST_INTERFACE_SELECTOR(VectorClass, M_CLONABLE_CLONE)
		ADD_INTERFACE_SELECTOR(VectorClass, M_ITERABLE_CREATE)
		ADD_INTERFACE_SELECTOR(VectorClass, M_COLLECTION_ADD)
		ADD_INTERFACE_SELECTOR(VectorClass, M_COLLECTION_ADD_ALL)
		ADD_INTERFACE_SELECTOR(VectorClass, M_COLLECTION_ADD_ALL_C)
        ADD_INTERFACE_SELECTOR(VectorClass, M_COLLECTION_ADD_ALL_C_POINTER)
		ADD_INTERFACE_SELECTOR(VectorClass, M_COLLECTION_CLEAR)
		ADD_INTERFACE_SELECTOR(VectorClass, M_COLLECTION_CONTAINS)
		ADD_INTERFACE_SELECTOR(VectorClass, M_COLLECTION_IS_EMPTY)
		ADD_INTERFACE_SELECTOR(VectorClass, M_COLLECTION_REMOVE)
		ADD_INTERFACE_SELECTOR(VectorClass, M_COLLECTION_REMOVE_ALL)
		ADD_INTERFACE_SELECTOR(VectorClass, M_COLLECTION_RETAIN_ALL)
		ADD_INTERFACE_SELECTOR(VectorClass, M_COLLECTION_SIZE)
		ADD_INTERFACE_SELECTOR(VectorClass, M_COLLECTION_ELEMENT_SIZE)
		ADD_INTERFACE_SELECTOR(VectorClass, M_COLLECTION_TO_ARRAY)
		ADD_INTERFACE_SELECTOR(VectorClass, M_LIST_ADD)
		ADD_INTERFACE_SELECTOR(VectorClass, M_LIST_ADD_ALL)
		ADD_INTERFACE_SELECTOR(VectorClass, M_LIST_ADD_ALL_C)
		ADD_INTERFACE_SELECTOR(VectorClass, M_LIST_GET)
		ADD_INTERFACE_SELECTOR(VectorClass, M_LIST_INDEX_OF)
		ADD_INTERFACE_SELECTOR(VectorClass, M_LIST_LAST_INDEX_OF)
		ADD_INTERFACE_SELECTOR(VectorClass, M_LIST_REMOVE)
		ADD_INTERFACE_SELECTOR(VectorClass, M_LIST_SET)
		ADD_INTERFACE_SELECTOR(VectorClass, M_LIST_SUBLIST)
	)
}

/*------------------------------------------------*/
/*------- Class descriptor and initializer -------*/
/*------------------------------------------------*/

const void* Vector_d;
const void* VectorClass_d;

const void* initVector(){
	return ooc_new(	VectorClassClass(),
			"Vector",
			ObjectClass(),
			sizeof(Vector_r),
			LINK_METHOD(Vector, M_CTOR),
			LINK_METHOD(Vector, M_DTOR),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_CLONABLE_CLONE),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_ITERABLE_CREATE),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_COLLECTION_ADD),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_COLLECTION_ADD_ALL),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_COLLECTION_ADD_ALL_C),
            LINK_INTERFACE_METHOD(Vector, VectorClass, M_COLLECTION_ADD_ALL_C_POINTER),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_COLLECTION_CLEAR),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_COLLECTION_CONTAINS),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_COLLECTION_IS_EMPTY),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_COLLECTION_REMOVE),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_COLLECTION_REMOVE_ALL),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_COLLECTION_RETAIN_ALL),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_COLLECTION_SIZE),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_COLLECTION_ELEMENT_SIZE),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_COLLECTION_TO_ARRAY),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_LIST_ADD),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_LIST_ADD_ALL),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_LIST_ADD_ALL_C),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_LIST_GET),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_LIST_INDEX_OF),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_LIST_LAST_INDEX_OF),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_LIST_REMOVE),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_LIST_SET),
			LINK_INTERFACE_METHOD(Vector, VectorClass, M_LIST_SUBLIST),
			0);
}

const void* initVectorClass(){
	return ooc_new(	ClassClass(),
			"VectorClass",
			ClassClass(),
			sizeof(VectorClass_r),
			LINK_METHOD(VectorClass, M_CTOR),
			0);
}

