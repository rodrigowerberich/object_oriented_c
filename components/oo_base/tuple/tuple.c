#include <tuple.h>
#include <lua_assert.h>

void Tuple_addC_(o_Tuple o_tuple, void* object, int size_of_object){
    ASSERT(IS_A(o_tuple, Vector), );
    Collection_add(o_tuple, SizedObject(object, size_of_object));
}
void Tuple_add(o_Tuple o_tuple, o_Object o_object){
    ASSERT(IS_A(o_tuple, Vector), );
    ASSERT(ooc_isObject(o_object), );
    ASSERT(!IS_A(o_object, SizedObject), );
    Collection_add(o_tuple, o_object);
}
void* Tuple_getC_(o_Tuple o_tuple, int i, int size_of_object){
    ASSERT(IS_A(o_tuple, Vector), NULL);
    o_SizedObject o_object = List_get(o_tuple, i);
    ASSERT(IS_A(o_object, SizedObject), NULL);
    return (SizedObject_size(o_object) == size_of_object)? SizedObject_value(o_object): NULL;
}
o_Object Tuple_get(o_Tuple o_tuple, int i){
    ASSERT(IS_A(o_tuple, Vector), NULL);
    o_Object o_object = List_get(o_tuple, i);
    ASSERT(!IS_A(o_object, SizedObject), NULL);
    return o_object;
}