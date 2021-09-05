#ifndef TUPLE_H__
#define TUPLE_H__

#include <vector.h>
#include <sized_object.h>

typedef void* o_Tuple;

static inline o_Tuple Tuple(){
    return Vector();
}

void Tuple_addC_(o_Tuple o_tuple, void* object, int size_of_object);
#define Tuple_addC(o_tuple_, object_, type_) Tuple_addC_(o_tuple_, object_, sizeof(type_))
void Tuple_add(o_Tuple o_tuple, o_Object o_object);

void* Tuple_getC_(o_Tuple o_tuple, int i, int size_of_object);
#define Tuple_getC(o_tuple_, i_, type_) (type_*) Tuple_getC_(o_tuple_, i_, sizeof(type_));
o_Object Tuple_get(o_Tuple o_tuple, int i);

#endif //TUPLE_H__