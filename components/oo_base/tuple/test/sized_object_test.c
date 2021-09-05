/*
 * sized_object_test.c
 *
 *  Created on: 28 de jan de 2019
 *      Author: lua
 */

#include <sized_object.h>
#include <sized_object_test.h>
#include <vector.h>
#include <lua_assert.h>
#include <o_string.h>
#include <test_suite.h>
#include <vector_iterator.h>

UNIT_TEST(sized_string_clone);
static bool sized_string_clone(){
    o_Vector o_tuple = Vector();
    Collection_add(o_tuple, SizedObject(String("Banana"), 0));
    Collection_add(o_tuple, SizedObject(INT(95), sizeof(int)));
    o_Vector o_tuple_clone = Clonable_clone(o_tuple);
    ASSERT(Collection_size(o_tuple) == 2, false);
    ASSERT(Collection_size(o_tuple_clone) == 2, false);
    o_String o_string_original = SizedObject_value(List_get(o_tuple, 0));
    ASSERT(o_string_original, false);
    ASSERT(!ooc_differ(o_string_original, String("Banana")), 0);
    o_String o_string_clone = SizedObject_value(List_get(o_tuple_clone, 0));
    ASSERT(o_string_clone, false);
    ASSERT(!ooc_differ(o_string_clone, String("Banana")), false);
    ASSERT(o_string_original != o_string_clone, false);
    int* p_value_original = SizedObject_value(List_get(o_tuple, 1));
    ASSERT(p_value_original, false);
    ASSERT(*p_value_original == 95, false);
    int* p_value_clone = SizedObject_value(List_get(o_tuple_clone, 1));
    ASSERT(p_value_clone, false);
    ASSERT(*p_value_clone == 95, false);
    ASSERT(p_value_original != p_value_clone, false);
    OOC_DELETE(o_tuple);
    OOC_DELETE(o_tuple_clone);
    return true;
}

void sized_object_test(){
    VectorClass();
    StringClass();
    VectorIteratorClass();
    SizedObjectClass();
    RUN_TEST(sized_string_clone);
}
