/*
 * vector_test.c
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */

#include <vector_test.h>
#include <vector.h>
#include <vector_iterator.h>
#include <clonable_interface.h>
#include <lua_assert.h>
#include <o_string.h>
#include <test_suite.h>
#include <limits.h>

UNIT_TEST(vector_create_add_contains_size_iterator);
static bool vector_create_add_contains_size_iterator(){
    int* numbers[] = {INT(1),INT(35),INT(8),INT(9),INT(25),INT(3)};
	int expected_outcome[] = {1, 35, 8, 9, 25,3, 35, 8, 9, 25};
	int expected_outcome2[] = {1, 3};
	o_Vector o_vector = VectorC(int);
	for(int i=0; i < 6; i++){
		Collection_add(o_vector, numbers[i]);
		ASSERT(Collection_contains(o_vector, Clonable_cloneC(numbers[i],int)), false);
	}
	ASSERT(Collection_size(o_vector) == 6, false);
	ASSERT(Collection_contains(o_vector, INT(35)), false);
	ASSERT(!Collection_contains(o_vector, INT(99)), false);
	o_Iterator o_iterator = Iterable_create(o_vector);
	ASSERT(o_iterator, false);
	for(int i=0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
		int* p_num = (int*) Iterator_currItem(o_iterator);
		if(p_num){
			ASSERT(*p_num == *numbers[i], false);
		}
	}
	OOC_DELETE(o_iterator);
	int fromIndex = 1;
	int toIndex = 4;
	o_Vector o_vector_sub = List_subList(o_vector, fromIndex, toIndex);
	o_iterator = Iterable_create(o_vector_sub);
	ASSERT(Collection_size(o_vector_sub) == ((toIndex-fromIndex)+1), false);
	for(int i=fromIndex; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
		int* p_num = (int*) Iterator_currItem(o_iterator);
		if(p_num){
			ASSERT(*p_num == *numbers[i], false);
		}
	}
	Collection_addAll(o_vector, o_vector_sub);
	ASSERT(Collection_size(o_vector) == 6+((toIndex-fromIndex)+1), false);
	OOC_DELETE(o_iterator);
	for(int i=0; i < Collection_size(o_vector); i++){
		int* p_num = List_get(o_vector, i);
		if(p_num){
			ASSERT(*p_num == expected_outcome[i], false);
		}
	}
	Collection_remove(o_vector, INT(25));
	ASSERT(Collection_size(o_vector) == 6+((toIndex-fromIndex)+1)-2, false);
	ASSERT(List_indexOf(o_vector, INT(25)) == -1, false);
	ASSERT(List_lastIndexOf(o_vector, INT(25)) == -1, false);
	ASSERT(List_indexOf(o_vector, INT(35)) == 1, false);
	ASSERT(List_lastIndexOf(o_vector, INT(35)) == 5, false);
	ASSERT(List_set(o_vector, 2, INT(6)), false);
	int* p_num6 = List_get(o_vector, 2);
	ASSERT(*p_num6 == 6, false);
	List_remove(o_vector, 2);
	ASSERT(!Collection_contains(o_vector, INT(6)) && (Collection_size(o_vector) == 6+((toIndex-fromIndex)+1)-3), false);
	Collection_removeAll(o_vector, o_vector_sub);
	ASSERT(Collection_size(o_vector) == 2, NULL);
	for(int i=0; i < Collection_size(o_vector); i++){
		int* p_num = List_get(o_vector, i);
		if(p_num){
			ASSERT((*p_num) == expected_outcome2[i], false);
		}
	}
	int array_size = 0;
	int** array = (int**) Collection_toArray(o_vector, &array_size);
	ASSERT(array && array_size == 2, false);
	for(int i=0; i < array_size; i++){
		int* element = array[i];
		if(element){
		    ASSERT((*element) == expected_outcome2[i], false);
		}
		OOC_DELETE(element);
	}
	OOC_DELETE(array);
	Collection_addAll(o_vector, o_vector_sub);
	ASSERT(Collection_size(o_vector) == 6, false);
	Collection_retainAll(o_vector, o_vector_sub);
	ASSERT(Collection_size(o_vector) == 4, false);
	Collection_clear(o_vector);
	ASSERT(Collection_isEmpty(o_vector) && Collection_size(o_vector) == 0, false);
	OOC_DELETE(o_vector_sub);
	OOC_DELETE(o_vector);
	return true;
}

UNIT_TEST(vector_retain_all_list_add);
static bool vector_retain_all_list_add(){
    int* numbers1[] = {INT(10), INT(27), INT(27),INT(8),INT(9), INT(9), INT(25),INT(3), INT(3)};
    int* numbers2[] = {INT(27),INT(33),INT(25), INT(3)};
    int expected_outcome[] = {27, 27, 25, 3, 3};
    int expected_outcome2[] = {5, 27, 27, 26, 25, 3, 3, 35};
    int expected_outcome3[] = {27, 33, 25, 3, 5, 27, 27, 27, 33, 25, 3, 26, 25, 3, 3, 35, 27, 33, 25, 3};
    o_Vector o_vector1 = VectorC(int);
    o_Vector o_vector2 = VectorC(int);
    for(int i=0; i < sizeof(numbers1)/sizeof(int*); i++){
        Collection_add(o_vector1, numbers1[i]);
    }
    for(int i=0; i < sizeof(numbers2)/sizeof(int*); i++){
        Collection_add(o_vector2, numbers2[i]);
    }
    Collection_retainAll(o_vector1, o_vector2);
    ASSERT(Collection_size(o_vector1) == ARRAY_C_SIZE(expected_outcome), false);
    o_Iterator o_iterator = Iterable_create(o_vector1);
    ASSERT(o_iterator, false);
    for(int i=0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        int* p_num = (int*) Iterator_currItem(o_iterator);
        if(p_num){
            ASSERT(*p_num == expected_outcome[i], false);
        }
    }
    OOC_DELETE(o_iterator);
    List_add(o_vector1, 0, INT(5));
    List_add(o_vector1, -1, INT(5));
    List_add(o_vector1, INT_MAX, INT(5));
    ASSERT(Collection_size(o_vector1) == (ARRAY_C_SIZE(expected_outcome)+ 1), false);
    List_add(o_vector1, 3, INT(26));
    List_add(o_vector1, 7, INT(35));
    ASSERT(Collection_size(o_vector1) == (ARRAY_C_SIZE(expected_outcome2)), false);
    o_iterator = Iterable_create(o_vector1);
    for(int i=0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        int* p_num = (int*) Iterator_currItem(o_iterator);
        if(p_num){
            ASSERT(*p_num == expected_outcome2[i], false);
        }
    }
    OOC_DELETE(o_iterator);
    List_addAll(o_vector1, 8, o_vector2);
    ASSERT(Collection_size(o_vector1) == (ARRAY_C_SIZE(expected_outcome2)+4), false);
    List_addAll(o_vector1, 3, o_vector2);
    ASSERT(Collection_size(o_vector1) == (ARRAY_C_SIZE(expected_outcome2)+8), false);
    List_addAll(o_vector1, 0, o_vector2);
    ASSERT(Collection_size(o_vector1) == ARRAY_C_SIZE(expected_outcome3), false);
    List_addAll(o_vector1, -1, o_vector2);
    List_addAll(o_vector1, INT_MAX, o_vector2);
    ASSERT(Collection_size(o_vector1) == ARRAY_C_SIZE(expected_outcome3), false);
    o_iterator = Iterable_create(o_vector1);
    for(int i=0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        int* p_num = (int*) Iterator_currItem(o_iterator);
        if(p_num){
            ASSERT(*p_num == expected_outcome3[i], false);
        }
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_vector1);
    OOC_DELETE(o_vector2);
    return true;
}

UNIT_TEST(vector_add_all);
static bool vector_add_all(){
    int numbers1[] = {10, 27, 27, 8, 9, 9, 25, 3, 3};
    int numbers2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int expected_result[] = {10, 27, 27, 8 , 9, 9, 25, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int expected_result1[] = {10, 27, 27, 8 , 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 9, 25, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int expected_result2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 10, 27, 27, 8 , 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 9, 25, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    o_Vector o_vector = VectorC(int);
    Collection_simpleAddAllC(o_vector, numbers1);
    ASSERT(Collection_size(o_vector) == 9, false);
    o_Iterator o_iterator = Iterable_create(o_vector);
    for(int i=0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        int* p_num = (int*) Iterator_currItem(o_iterator);
        if(p_num){
            ASSERT(*p_num == numbers1[i], false);
        }
    }
    OOC_DELETE(o_iterator);
    List_simpleAddAllC(o_vector, 100 ,numbers2);
    ASSERT(Collection_size(o_vector) == 20, false);
    o_iterator = Iterable_create(o_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        int* p_num = (int*) Iterator_currItem(o_iterator);
        if(p_num){
            ASSERT(*p_num == expected_result[i], false);
        }
    }
    OOC_DELETE(o_iterator);
    List_simpleAddAllC(o_vector, 5 ,numbers2);
    List_simpleAddAllC(o_vector, -1 ,numbers2);
    ASSERT(Collection_size(o_vector) == 31, false);
    o_iterator = Iterable_create(o_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        int* p_num = (int*) Iterator_currItem(o_iterator);
        if(p_num){
            ASSERT(*p_num == expected_result1[i], false);
        }
    }
    OOC_DELETE(o_iterator);
    List_simpleAddAllC(o_vector, 0 ,numbers2);
    ASSERT(Collection_size(o_vector) == 42, false);
    o_iterator = Iterable_create(o_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        int* p_num = (int*) Iterator_currItem(o_iterator);
        if(p_num){
            ASSERT(*p_num == expected_result2[i], false);
        }
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_vector);
    return true;
}

UNIT_TEST(vector_of_strings);
static bool vector_of_strings(){
    o_String strings1[] = {String("a"), String("b"), String("c"), String("d")};
    o_Vector o_vector = Vector();
    Collection_addAllCObject(o_vector, strings1);
    o_Iterator o_iterator = Iterable_create(o_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_String o_string = Iterator_currItem(o_iterator);
        ASSERT(o_string, false);
        ASSERT(o_string != strings1[i], false);
        ASSERT(!ooc_differ(o_string, Clonable_clone(strings1[i])), false);
    }
    OOC_DELETE(o_iterator);
    for(int i = 0; i < ARRAY_C_SIZE(strings1); i++){
        OOC_DELETE(strings1[i]);
    }
    OOC_DELETE(o_vector);
    return true;
}

UNIT_TEST(vector_clone);
static bool vector_clone(){
    o_String strings1[] = {String("a"), String("b"), String("c"), String("d")};
    o_Vector o_vector = Vector();
    Collection_addAllCObject(o_vector, strings1);
    o_Vector o_clone_vector = Clonable_clone(o_vector);
    o_Iterator o_iterator = Iterable_create(o_vector);
    o_Iterator o_iterator1 = Iterable_create(o_clone_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator), Iterator_next(o_iterator1)){
        o_String o_string = Iterator_currItem(o_iterator);
        o_String o_string_clone = Iterator_currItem(o_iterator1);
        ASSERT(o_string && o_string_clone, false);
        ASSERT(o_string != strings1[i], false);
        ASSERT(o_string != o_string_clone, false);
        ASSERT(!ooc_differ(o_string, Clonable_clone(strings1[i])), false);
        ASSERT(!ooc_differ(o_string_clone, Clonable_clone(strings1[i])), false);

    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_iterator1);
    ooc_deleteCArrayContent(strings1);
    OOC_DELETE(o_vector);
    OOC_DELETE(o_clone_vector);
    uint8_t chars1[] = { 'a', 'b', 'c', 'd' };
    o_vector = VectorC(uint8_t);
    Collection_simpleAddAllC(o_vector, chars1);
    o_clone_vector = Clonable_clone(o_vector);
    o_iterator = Iterable_create(o_vector);
    o_iterator1 = Iterable_create(o_clone_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator), Iterator_next(o_iterator1)){
        uint8_t* p_value = Iterator_currItem(o_iterator);
        uint8_t* p_value_clone = Iterator_currItem(o_iterator1);
        ASSERT(p_value && p_value_clone, false);
        ASSERT(p_value != &chars1[i], false);
        ASSERT(p_value_clone != &chars1[i], false);
        ASSERT(*p_value == chars1[i], false);
        ASSERT(*p_value_clone == chars1[i], false);

    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_iterator1);
    OOC_DELETE(o_vector);
    OOC_DELETE(o_clone_vector);
    return true;
}

UNIT_TEST(vector_inplace_add_all);
static bool vector_inplace_add_all(){
    o_Vector o_string_vector = Vector();
    Collection_inplaceAddAllCObject(o_string_vector, ARG({String("a"), String("b"), String("c"), String("d")}));
    OOC_DELETE(o_string_vector);
    o_Vector o_int_vector = VectorC(int);
    Collection_inplaceAddAllC(o_string_vector, int, ARG({1, 2, 3, 4}));
    OOC_DELETE(o_int_vector);
    OOC_DELETE(o_string_vector);
    return true;
}

void vector_test(){
    VectorClass();
    StringClass();
    VectorIteratorClass();
	RUN_TEST(vector_create_add_contains_size_iterator);
	RUN_TEST(vector_retain_all_list_add);
	RUN_TEST(vector_add_all);
	RUN_TEST(vector_of_strings);
	RUN_TEST(vector_clone);
	RUN_TEST(vector_inplace_add_all);
}
