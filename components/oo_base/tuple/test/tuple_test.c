#include <tuple_test.h>
#include <tuple.h>
#include <test_suite.h>
#include <o_string.h>
#include <limits.h>

static inline int g(o_Vector o_vector, int i){
    int* value = List_get(o_vector, i); 
    return value? *value: INT_MAX;
}

UNIT_TEST(tuple_test_test);
static bool tuple_test_test(){
    o_Tuple o_tuple = Tuple();
    o_Vector o_vector = VectorC(int);
    Collection_inplaceAddAllC(o_vector, int, ARG({1,2,3,4,5}));
    Tuple_addC(o_tuple, INT(0), int);
    Tuple_add(o_tuple, o_vector);
    Tuple_addC(o_tuple, INT(6), int);
    Tuple_add(o_tuple, String("Value"));
    int* p_v0 = Tuple_getC(o_tuple, 0, int);
    o_Vector o_v1_5 = Tuple_get(o_tuple, 1);
    int* p_v6 = Tuple_getC(o_tuple, 2, int);
    o_String o_str = Tuple_get(o_tuple, 3);
    ASSERT(p_v0, false);
    ASSERT(*p_v0 == 0, false);
    ASSERT(o_v1_5, false);
    ASSERT(Collection_size(o_v1_5) == 5, false);
    ASSERT((g(o_v1_5, 0) == 1) && (g(o_v1_5, 1) == 2) && (g(o_v1_5, 2) == 3) && (g(o_v1_5, 3) == 4) && (g(o_v1_5, 4) == 5) , false);
    ASSERT(p_v6, false);
    ASSERT(*p_v6 == 6, false);
    ASSERT(o_str, false);
    ASSERT(!ooc_differ(o_str, String("Value")), false);
    OOC_DELETE(o_tuple);
    return true;
}

void tuple_test(){
    VectorClass();
    SizedObjectClass();
    StringClass();
    RUN_TEST(tuple_test_test);
}

