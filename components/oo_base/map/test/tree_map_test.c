/*
 * tree_map_test.c
 *
 *  Created on: 9 de jan de 2019
 *      Author: lua
 */

#include <tree_map.h>
#include <lua_assert.h>
#include <o_string.h>
#include <test_suite.h>
#include <tree_map_iterator.h>
#include <vector.h>
#include <vector_iterator.h>

UNIT_TEST(tree_map_test_node_c);
static bool tree_map_test_node_c(){
    // Both not objects
    o_TreeMapNode o_node = TreeMapNodeKeyCValueCHelper(INT(5), int, INT(17), int);
    int* key = TreeMapNode_getKey(o_node);
    int* value = TreeMapNode_getValue(o_node);
    ASSERT(key && value, false);
    ASSERT(*key == 5 && *value == 17, false);
    ASSERT(TreeMapNode_compareKey(o_node, INT(2)) > 0, false);
    ASSERT(TreeMapNode_compareKey(o_node, INT(5)) == 0, false);
    ASSERT(TreeMapNode_compareKey(o_node, INT(8)) < 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, INT(2)) > 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, INT(17)) == 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, INT(34)) < 0, false);
    // Both not objects - clone
    o_TreeMapNode o_node_clone = Clonable_clone(o_node);
    int* key_clone = TreeMapNode_getKey(o_node_clone);
    int* value_clone = TreeMapNode_getValue(o_node_clone);
    ASSERT(key_clone && value_clone, false);
    ASSERT(*key_clone == 5 && *value_clone == 17, false);
    ASSERT(TreeMapNode_compareKey(o_node_clone, INT(2)) > 0, false);
    ASSERT(TreeMapNode_compareKey(o_node_clone, INT(5)) == 0, false);
    ASSERT(TreeMapNode_compareKey(o_node_clone, INT(8)) < 0, false);
    ASSERT(TreeMapNode_compareValue(o_node_clone, INT(2)) > 0, false);
    ASSERT(TreeMapNode_compareValue(o_node_clone, INT(17)) == 0, false);
    ASSERT(TreeMapNode_compareValue(o_node_clone, INT(34)) < 0, false);
    OOC_DELETE(o_node);
    OOC_DELETE(o_node_clone);
    // Value not object
    o_node = TreeMapNodeKeyCHelper(INT(50), int, String("Ola"));
    int* key1 = TreeMapNode_getKey(o_node);
    o_String value1 = TreeMapNode_getValue(o_node);
    ASSERT(key1 && value1, false);
    ASSERT(*key1 == 50 && !ooc_differ(value1, String("Ola")), false);
    ASSERT(TreeMapNode_compareKey(o_node, INT(20)) > 0, false);
    ASSERT(TreeMapNode_compareKey(o_node, INT(50)) == 0, false);
    ASSERT(TreeMapNode_compareKey(o_node, INT(80)) < 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, String("Abc")) > 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, String("Ola")) == 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, String("Zao")) < 0, false);
    // Value not object - clone
    o_node_clone = Clonable_clone(o_node);
    int* key_clone1 = TreeMapNode_getKey(o_node_clone);
    o_String value_clone1 = TreeMapNode_getValue(o_node_clone);
    ASSERT(key_clone1 && value_clone1, false);
    ASSERT(*key_clone1 == 50 && !ooc_differ(value_clone1, String("Ola")), false);
    ASSERT(TreeMapNode_compareKey(o_node_clone, INT(20)) > 0, false);
    ASSERT(TreeMapNode_compareKey(o_node_clone, INT(50)) == 0, false);
    ASSERT(TreeMapNode_compareKey(o_node_clone, INT(80)) < 0, false);
    ASSERT(TreeMapNode_compareValue(o_node_clone, String("Abc")) > 0, false);
    ASSERT(TreeMapNode_compareValue(o_node_clone, String("Ola")) == 0, false);
    ASSERT(TreeMapNode_compareValue(o_node_clone, String("Zao")) < 0, false);
    OOC_DELETE(o_node);
    OOC_DELETE(o_node_clone);
    // Value not object
    o_node = TreeMapNodeValueCHelper(String("Tchau"), INT(25), int);
    o_String key2 = TreeMapNode_getKey(o_node);
    int* value2 = TreeMapNode_getValue(o_node);
    ASSERT(key2 && value2, false);
    ASSERT(!ooc_differ(key2, String("Tchau")) && *value2 == 25, false);
    ASSERT(TreeMapNode_compareKey(o_node, String("Rau")) > 0, false);
    ASSERT(TreeMapNode_compareKey(o_node, String("Tchau")) == 0, false);
    ASSERT(TreeMapNode_compareKey(o_node, String("Zeta")) < 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, INT(19)) > 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, INT(25)) == 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, INT(37)) < 0, false);
    // Value not object - clone
    o_node_clone = Clonable_clone(o_node);
    o_String key_clone2 = TreeMapNode_getKey(o_node);
    int* value_clone2 = TreeMapNode_getValue(o_node);
    ASSERT(key_clone2 && value_clone2, false);
    ASSERT(!ooc_differ(key_clone2, String("Tchau")) && *value_clone2 == 25, false);
    ASSERT(TreeMapNode_compareKey(o_node, String("Rau")) > 0, false);
    ASSERT(TreeMapNode_compareKey(o_node, String("Tchau")) == 0, false);
    ASSERT(TreeMapNode_compareKey(o_node, String("Zeta")) < 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, INT(19)) > 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, INT(25)) == 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, INT(37)) < 0, false);
    OOC_DELETE(o_node);
    OOC_DELETE(o_node_clone);
    // Both objects
    o_node = TreeMapNode(String("Key"), String("Value"));
    o_String key3 = TreeMapNode_getKey(o_node);
    o_String value3 = TreeMapNode_getValue(o_node);
    ASSERT(key3 && value3, false);
    ASSERT(!ooc_differ(key3, String("Key")) && !ooc_differ(value3, String("Value")), false);
    ASSERT(TreeMapNode_compareKey(o_node, String("Joy")) > 0, false);
    ASSERT(TreeMapNode_compareKey(o_node, String("Key")) == 0, false);
    ASSERT(TreeMapNode_compareKey(o_node, String("Lol")) < 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, String("Apple")) > 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, String("Value")) == 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, String("Valve")) < 0, false);
    // Value not object - clone
    o_node_clone = Clonable_clone(o_node);
    o_String key_clone3 = TreeMapNode_getKey(o_node);
    o_String value_clone3 = TreeMapNode_getValue(o_node);
    ASSERT(key_clone3 && value_clone3, false);
    ASSERT(!ooc_differ(key_clone3, String("Key")) && !ooc_differ(value_clone3, String("Value")), false);
    ASSERT(TreeMapNode_compareKey(o_node, String("Joy")) > 0, false);
    ASSERT(TreeMapNode_compareKey(o_node, String("Key")) == 0, false);
    ASSERT(TreeMapNode_compareKey(o_node, String("Lol")) < 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, String("Apple")) > 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, String("Value")) == 0, false);
    ASSERT(TreeMapNode_compareValue(o_node, String("Valve")) < 0, false);
    OOC_DELETE(o_node);
    OOC_DELETE(o_node_clone);
    return true;
}

UNIT_TEST(tree_map_collection_add);
static bool tree_map_collection_add(){
    // Both not objects
    o_TreeMap o_map = TreeMap();
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCValueCHelper(INT(2), int, INT(99), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCValueCHelper(INT(5), int, INT(17), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCValueCHelper(INT(7), int, INT(35), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCValueCHelper(INT(9), int, INT(68), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCValueCHelper(INT(15), int, INT(98), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCValueCHelper(INT(17), int, INT(20), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCValueCHelper(INT(25), int, INT(11), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCValueCHelper(INT(28), int, INT(63), int)), false);
    ASSERT(!Collection_add(o_map, TreeMapNodeKeyCValueCHelper(INT(2), int, INT(66), int)), false);
    ASSERT(Collection_size(o_map) == 8, false);
    OOC_DELETE(o_map);
    // Value not object
    o_map = TreeMap();
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCHelper(INT(2), int, String("99"))), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCHelper(INT(5), int, String("17"))), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCHelper(INT(7), int, String("35"))), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCHelper(INT(9), int, String("68"))), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCHelper(INT(15), int, String("98"))), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCHelper(INT(17), int, String("20"))), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCHelper(INT(25), int, String("11"))), false);
    ASSERT(Collection_add(o_map, TreeMapNodeKeyCHelper(INT(28), int, String("63"))), false);
    ASSERT(!Collection_add(o_map, TreeMapNodeKeyCHelper(INT(2), int, String("66"))), false);
    ASSERT(Collection_size(o_map) == 8, false);
    OOC_DELETE(o_map);
    // Key not object
    o_map = TreeMap();
    ASSERT(Collection_add(o_map, TreeMapNodeValueCHelper(String("A"), INT(99), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeValueCHelper(String("B"), INT(17), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeValueCHelper(String("C"), INT(35), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeValueCHelper(String("D"), INT(68), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeValueCHelper(String("E"), INT(98), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeValueCHelper(String("F"), INT(20), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeValueCHelper(String("G"), INT(11), int)), false);
    ASSERT(Collection_add(o_map, TreeMapNodeValueCHelper(String("H"), INT(63), int)), false);
    ASSERT(!Collection_add(o_map, TreeMapNodeValueCHelper(String("A"), INT(66), int)), false);
    ASSERT(Collection_size(o_map) == 8, false);
    OOC_DELETE(o_map);
    // Both objects
    o_map = TreeMap();
    ASSERT(Collection_add(o_map, TreeMapNode(String("A"), String("99"))), false);
    ASSERT(Collection_add(o_map, TreeMapNode(String("B"), String("17"))), false);
    ASSERT(Collection_add(o_map, TreeMapNode(String("C"), String("35"))), false);
    ASSERT(Collection_add(o_map, TreeMapNode(String("D"), String("68"))), false);
    ASSERT(Collection_add(o_map, TreeMapNode(String("E"), String("98"))), false);
    ASSERT(Collection_add(o_map, TreeMapNode(String("F"), String("20"))), false);
    ASSERT(Collection_add(o_map, TreeMapNode(String("G"), String("11"))), false);
    ASSERT(Collection_add(o_map, TreeMapNode(String("H"), String("63"))), false);
    ASSERT(!Collection_add(o_map, TreeMapNode(String("A"), String("66"))), false);
    ASSERT(Collection_size(o_map) == 8, false);
    OOC_DELETE(o_map);
    return true;
}

UNIT_TEST(tree_map_collection_add_all);
static bool tree_map_collection_add_all(){
    // Both not objects
    o_TreeMapNode nodes1[] = {TreeMapNodeKeyCValueCHelper(INT(2), int, INT(99), int),
                              TreeMapNodeKeyCValueCHelper(INT(5), int, INT(17), int),
                              TreeMapNodeKeyCValueCHelper(INT(7), int, INT(35), int),
                              TreeMapNodeKeyCValueCHelper(INT(9), int, INT(68), int),
                              TreeMapNodeKeyCValueCHelper(INT(15), int, INT(98), int),
                              TreeMapNodeKeyCValueCHelper(INT(17), int, INT(20), int),
                              TreeMapNodeKeyCValueCHelper(INT(25), int, INT(11), int),
                              TreeMapNodeKeyCValueCHelper(INT(28), int, INT(63), int),
                              TreeMapNodeKeyCValueCHelper(INT(2), int, INT(66), int)};
    o_Vector o_vector = Vector();
    o_TreeMap o_map = TreeMap();
    Collection_addAllCObject(o_vector, nodes1);
    Collection_addAll(o_map, o_vector);
    ASSERT(Collection_size(o_map) == 8, false);
    o_Iterator o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        int* p_key = TreeMapNode_getKey(o_node);
        int* p_value = TreeMapNode_getValue(o_node);
        int* p_key_match = TreeMapNode_getKey(nodes1[i]);
        int* p_value_match = TreeMapNode_getValue(nodes1[i]);
        ASSERT(p_key && p_value, false);
        ASSERT(p_key_match && p_value_match, false);
        ASSERT( ( (*p_key) == (*p_key_match) ) && ( (*p_value) == (*p_value_match) ), false)
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    OOC_DELETE(o_vector);
    for(int i=0; i < ARRAY_C_SIZE(nodes1); i++){
        OOC_DELETE(nodes1[i]);
    }
    // Value not object
    o_TreeMapNode nodes2[] = {  TreeMapNodeKeyCHelper(INT(2), int, String("99")),
                                TreeMapNodeKeyCHelper(INT(5), int, String("17")),
                                TreeMapNodeKeyCHelper(INT(7), int, String("35")),
                                TreeMapNodeKeyCHelper(INT(9), int, String("68")),
                                TreeMapNodeKeyCHelper(INT(15), int, String("98")),
                                TreeMapNodeKeyCHelper(INT(17), int, String("20")),
                                TreeMapNodeKeyCHelper(INT(25), int, String("11")),
                                TreeMapNodeKeyCHelper(INT(28), int, String("63")),
                                TreeMapNodeKeyCHelper(INT(2), int, String("66"))};
    o_vector = Vector();
    o_map = TreeMap();
    Collection_addAllCObject(o_vector, nodes2);
    Collection_addAll(o_map, o_vector);
    ASSERT(Collection_size(o_map) == 8, false);
    o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        int* p_key = TreeMapNode_getKey(o_node);
        o_String o_value = TreeMapNode_getValue(o_node);
        int* p_key_match = TreeMapNode_getKey(nodes2[i]);
        o_String o_value_match = TreeMapNode_getValue(nodes2[i]);
        ASSERT(p_key && o_value, false);
        ASSERT(p_key_match && o_value_match, false);
        ASSERT( ( (*p_key) == (*p_key_match) ) && !ooc_differ(o_value, Clonable_clone(o_value_match)), false)
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    OOC_DELETE(o_vector);
    for(int i=0; i < ARRAY_C_SIZE(nodes2); i++){
        OOC_DELETE(nodes2[i]);
    }
    // Key not object
    o_TreeMapNode nodes3[] = {  TreeMapNodeValueCHelper(String("A"), INT(99), int),
                                TreeMapNodeValueCHelper(String("B"), INT(17), int),
                                TreeMapNodeValueCHelper(String("C"), INT(35), int),
                                TreeMapNodeValueCHelper(String("D"), INT(68), int),
                                TreeMapNodeValueCHelper(String("E"), INT(98), int),
                                TreeMapNodeValueCHelper(String("F"), INT(20), int),
                                TreeMapNodeValueCHelper(String("G"), INT(11), int),
                                TreeMapNodeValueCHelper(String("H"), INT(63), int),
                                TreeMapNodeValueCHelper(String("A"), INT(66), int)};
    o_vector = Vector();
    o_map = TreeMap();
    Collection_addAllCObject(o_vector, nodes3);
    Collection_addAll(o_map, o_vector);
    ASSERT(Collection_size(o_map) == 8, false);
    o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        o_String o_key = TreeMapNode_getKey(o_node);
        int* p_value = TreeMapNode_getValue(o_node);
        o_String o_key_match = TreeMapNode_getKey(nodes3[i]);
        int* p_value_match = TreeMapNode_getValue(nodes3[i]);
        ASSERT(o_key && p_value, false);
        ASSERT(o_key_match && p_value_match, false);
        ASSERT( !ooc_differ(o_key, Clonable_clone(o_key_match)) && ( (*p_value) == (*p_value_match) ), false)
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    OOC_DELETE(o_vector);
    for(int i=0; i < ARRAY_C_SIZE(nodes3); i++){
        OOC_DELETE(nodes3[i]);
    }
    // Both objects
    o_TreeMapNode nodes4[] = {  TreeMapNode(String("A"), String("99")),
                                TreeMapNode(String("B"), String("17")),
                                TreeMapNode(String("C"), String("35")),
                                TreeMapNode(String("D"), String("68")),
                                TreeMapNode(String("E"), String("98")),
                                TreeMapNode(String("F"), String("20")),
                                TreeMapNode(String("G"), String("11")),
                                TreeMapNode(String("H"), String("63")),
                                TreeMapNode(String("A"), String("66"))};
    o_vector = Vector();
    o_map = TreeMap();
    Collection_addAllCObject(o_vector, nodes4);
    Collection_addAll(o_map, o_vector);
    ASSERT(Collection_size(o_map) == 8, false);
    o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        o_String o_key = TreeMapNode_getKey(o_node);
        o_String o_value = TreeMapNode_getValue(o_node);
        o_String o_key_match = TreeMapNode_getKey(nodes4[i]);
        o_String o_value_match = TreeMapNode_getValue(nodes4[i]);
        ASSERT(o_key && o_value, false);
        ASSERT(o_key_match && o_value_match, false);
        ASSERT( !ooc_differ(o_key, Clonable_clone(o_key_match)) && !ooc_differ(o_value, Clonable_clone(o_value_match)), false)
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    OOC_DELETE(o_vector);
    for(int i=0; i < ARRAY_C_SIZE(nodes4); i++){
        OOC_DELETE(nodes4[i]);
    }
    return true;
}

UNIT_TEST(tree_map_collection_add_all_c);
static bool tree_map_collection_add_all_c(){
    // Both not objects
    o_TreeMapNode nodes1[] = {TreeMapNodeKeyCValueCHelper(INT(2), int, INT(99), int),
                              TreeMapNodeKeyCValueCHelper(INT(5), int, INT(17), int),
                              TreeMapNodeKeyCValueCHelper(INT(7), int, INT(35), int),
                              TreeMapNodeKeyCValueCHelper(INT(9), int, INT(68), int),
                              TreeMapNodeKeyCValueCHelper(INT(15), int, INT(98), int),
                              TreeMapNodeKeyCValueCHelper(INT(17), int, INT(20), int),
                              TreeMapNodeKeyCValueCHelper(INT(25), int, INT(11), int),
                              TreeMapNodeKeyCValueCHelper(INT(28), int, INT(63), int),
                              TreeMapNodeKeyCValueCHelper(INT(2), int, INT(66), int)};
    o_TreeMap o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes1);
    ASSERT(Collection_size(o_map) == 8, false);
    o_Iterator o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        int* p_key = TreeMapNode_getKey(o_node);
        int* p_value = TreeMapNode_getValue(o_node);
        int* p_key_match = TreeMapNode_getKey(nodes1[i]);
        int* p_value_match = TreeMapNode_getValue(nodes1[i]);
        ASSERT(p_key && p_value, false);
        ASSERT(p_key_match && p_value_match, false);
        ASSERT( ( (*p_key) == (*p_key_match) ) && ( (*p_value) == (*p_value_match) ), false)
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    for(int i=0; i < ARRAY_C_SIZE(nodes1); i++){
        OOC_DELETE(nodes1[i]);
    }
    // Value not object
    o_TreeMapNode nodes2[] = {  TreeMapNodeKeyCHelper(INT(2), int, String("99")),
                                TreeMapNodeKeyCHelper(INT(5), int, String("17")),
                                TreeMapNodeKeyCHelper(INT(7), int, String("35")),
                                TreeMapNodeKeyCHelper(INT(9), int, String("68")),
                                TreeMapNodeKeyCHelper(INT(15), int, String("98")),
                                TreeMapNodeKeyCHelper(INT(17), int, String("20")),
                                TreeMapNodeKeyCHelper(INT(25), int, String("11")),
                                TreeMapNodeKeyCHelper(INT(28), int, String("63")),
                                TreeMapNodeKeyCHelper(INT(2), int, String("66"))};
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes2);
    ASSERT(Collection_size(o_map) == 8, false);
    o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        int* p_key = TreeMapNode_getKey(o_node);
        o_String o_value = TreeMapNode_getValue(o_node);
        int* p_key_match = TreeMapNode_getKey(nodes2[i]);
        o_String o_value_match = TreeMapNode_getValue(nodes2[i]);
        ASSERT(p_key && o_value, false);
        ASSERT(p_key_match && o_value_match, false);
        ASSERT( ( (*p_key) == (*p_key_match) ) && !ooc_differ(o_value, Clonable_clone(o_value_match)), false)
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    for(int i=0; i < ARRAY_C_SIZE(nodes2); i++){
        OOC_DELETE(nodes2[i]);
    }
    // Key not object
    o_TreeMapNode nodes3[] = {  TreeMapNodeValueCHelper(String("A"), INT(99), int),
                                TreeMapNodeValueCHelper(String("B"), INT(17), int),
                                TreeMapNodeValueCHelper(String("C"), INT(35), int),
                                TreeMapNodeValueCHelper(String("D"), INT(68), int),
                                TreeMapNodeValueCHelper(String("E"), INT(98), int),
                                TreeMapNodeValueCHelper(String("F"), INT(20), int),
                                TreeMapNodeValueCHelper(String("G"), INT(11), int),
                                TreeMapNodeValueCHelper(String("H"), INT(63), int),
                                TreeMapNodeValueCHelper(String("A"), INT(66), int)};
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes3);
    ASSERT(Collection_size(o_map) == 8, false);
    o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        o_String o_key = TreeMapNode_getKey(o_node);
        int* p_value = TreeMapNode_getValue(o_node);
        o_String o_key_match = TreeMapNode_getKey(nodes3[i]);
        int* p_value_match = TreeMapNode_getValue(nodes3[i]);
        ASSERT(o_key && p_value, false);
        ASSERT(o_key_match && p_value_match, false);
        ASSERT( !ooc_differ(o_key, Clonable_clone(o_key_match)) && ( (*p_value) == (*p_value_match) ), false)
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    for(int i=0; i < ARRAY_C_SIZE(nodes3); i++){
        OOC_DELETE(nodes3[i]);
    }
    // Both objects
    o_TreeMapNode nodes4[] = {  TreeMapNode(String("A"), String("99")),
                                TreeMapNode(String("B"), String("17")),
                                TreeMapNode(String("C"), String("35")),
                                TreeMapNode(String("D"), String("68")),
                                TreeMapNode(String("E"), String("98")),
                                TreeMapNode(String("F"), String("20")),
                                TreeMapNode(String("G"), String("11")),
                                TreeMapNode(String("H"), String("63")),
                                TreeMapNode(String("A"), String("66"))};
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes4);
    ASSERT(Collection_size(o_map) == 8, false);
    o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        o_String o_key = TreeMapNode_getKey(o_node);
        o_String o_value = TreeMapNode_getValue(o_node);
        o_String o_key_match = TreeMapNode_getKey(nodes4[i]);
        o_String o_value_match = TreeMapNode_getValue(nodes4[i]);
        ASSERT(o_key && o_value, false);
        ASSERT(o_key_match && o_value_match, false);
        ASSERT( !ooc_differ(o_key, Clonable_clone(o_key_match)) && !ooc_differ(o_value, Clonable_clone(o_value_match)), false);
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    for(int i=0; i < ARRAY_C_SIZE(nodes4); i++){
        OOC_DELETE(nodes4[i]);
    }
    return true;
}

UNIT_TEST(tree_map_collection_clear_contains_is_empty);
static bool tree_map_collection_clear_contains_is_empty(){
    // Both not objects
    o_TreeMapNode nodes1[] = {TreeMapNodeKeyCValueCHelper(INT(9), int, INT(22), int),
                              TreeMapNodeKeyCValueCHelper(INT(15), int, INT(11), int),
                              TreeMapNodeKeyCValueCHelper(INT(2), int, INT(9), int)};
    o_TreeMap o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes1);
    ASSERT(Collection_size(o_map) == 3, false);
    ASSERT(!Collection_isEmpty(o_map), false);
    ASSERT(Collection_contains(o_map, TreeMapNodeKeyCValueCHelper(INT(15), int, INT(11), int)), false);
    ASSERT(!Collection_contains(o_map, TreeMapNodeKeyCValueCHelper(INT(17), int, INT(11), int)), false);
    ASSERT(!Collection_contains(o_map, TreeMapNodeKeyCValueCHelper(INT(15), int, INT(18), int)), false);
    Collection_clear(o_map);
    ASSERT(Collection_size(o_map) == 0, false);
    ASSERT(Collection_isEmpty(o_map), false);
    Collection_addAllCObject(o_map, nodes1);
    ASSERT(Collection_size(o_map) == 3, false);
    ASSERT(!Collection_isEmpty(o_map), false);
    o_TreeMapNode o_node1 = Map_get(o_map, INT(9));
    ASSERT(o_node1, false);
    int* p_key1 = TreeMapNode_getKey(o_node1);
    int* p_value1 = TreeMapNode_getValue(o_node1);
    ASSERT(p_key1 && p_value1, false);
    ASSERT((*p_key1 == 9) && (*p_value1 == 22), false);
    o_TreeMapNode o_node_not_found = Map_get(o_map, INT(90));
    ASSERT(o_node_not_found == NULL, false);
    OOC_DELETE(o_map);
    for(int i=0; i < ARRAY_C_SIZE(nodes1); i++){
        OOC_DELETE(nodes1[i]);
    }
    // Value not object
    o_TreeMapNode nodes2[] = {  TreeMapNodeKeyCHelper(INT(28), int, String("Tree")),
                                TreeMapNodeKeyCHelper(INT(51), int, String("Banana")),
                                TreeMapNodeKeyCHelper(INT(74), int, String("Kite")),
                                TreeMapNodeKeyCHelper(INT(99), int, String("Kitty"))};
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes2);
    ASSERT(Collection_size(o_map) == 4, false);
    ASSERT(!Collection_isEmpty(o_map), false);
    Collection_clear(o_map);
    ASSERT(Collection_size(o_map) == 0, false);
    ASSERT(Collection_isEmpty(o_map), false);
    Collection_addAllCObject(o_map, nodes2);
    ASSERT(Collection_size(o_map) == 4, false);
    ASSERT(!Collection_isEmpty(o_map), false);
    o_TreeMapNode o_node2 = Map_get(o_map, INT(74));
    ASSERT(o_node2, false);
    int* p_key2 = TreeMapNode_getKey(o_node2);
    o_String o_value2 = TreeMapNode_getValue(o_node2);
    ASSERT(p_key2 && o_value2, false);
    ASSERT((*p_key2 == 74) && !ooc_differ(o_value2, String("Kite")), false);
    o_node_not_found = Map_get(o_map, INT(7));
    ASSERT(o_node_not_found == NULL, false);
    OOC_DELETE(o_map);
    for(int i=0; i < ARRAY_C_SIZE(nodes2); i++){
        OOC_DELETE(nodes2[i]);
    }
    // Key not object
    o_TreeMapNode nodes3[] = {  TreeMapNodeValueCHelper(String("Arvore"), INT(489), int),
                                TreeMapNodeValueCHelper(String("Baia"), INT(312), int),
                                TreeMapNodeValueCHelper(String("Cachorro"), INT(46), int),
                                TreeMapNodeValueCHelper(String("Duende"), INT(874), int),
                                TreeMapNodeValueCHelper(String("Elevador"), INT(984), int)};
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes3);
    ASSERT(Collection_size(o_map) == 5, false);
    ASSERT(!Collection_isEmpty(o_map), false);
    Collection_clear(o_map);
    ASSERT(Collection_size(o_map) == 0, false);
    ASSERT(Collection_isEmpty(o_map), false);
    Collection_addAllCObject(o_map, nodes3);
    ASSERT(Collection_size(o_map) == 5, false);
    ASSERT(!Collection_isEmpty(o_map), false);
    o_TreeMapNode o_node3 = Map_get(o_map, String("Duende"));
    ASSERT(o_node3, false);
    o_String o_key3 = TreeMapNode_getKey(o_node3);
    int* p_value3 = TreeMapNode_getValue(o_node3);
    ASSERT(o_key3 && p_value3, false);
    ASSERT( !ooc_differ(o_key3, String("Duende")) && (*p_value3 == 874), false);
    o_node_not_found = Map_get(o_map, String("Ornitorrinco"));
    ASSERT(o_node_not_found == NULL, false);
    OOC_DELETE(o_map);
    for(int i=0; i < ARRAY_C_SIZE(nodes3); i++){
        OOC_DELETE(nodes3[i]);
    }
    // Both objects
    o_TreeMapNode nodes4[] = {  TreeMapNode(String("All the thing!"), String("Nothing!")),
                                TreeMapNode(String("Bye bye now!"), String("Hello!"))};
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes4);
    ASSERT(Collection_size(o_map) == 2, false);
    ASSERT(!Collection_isEmpty(o_map), false);
    Collection_clear(o_map);
    ASSERT(Collection_size(o_map) == 0, false);
    ASSERT(Collection_isEmpty(o_map), false);
    Collection_addAllCObject(o_map, nodes4);
    ASSERT(Collection_size(o_map) == 2, false);
    ASSERT(!Collection_isEmpty(o_map), false);
    o_TreeMapNode o_node4 = Map_get(o_map, String("Bye bye now!"));
    ASSERT(o_node4, false);
    o_String o_key4 = TreeMapNode_getKey(o_node4);
    o_String o_value4 = TreeMapNode_getValue(o_node4);
    ASSERT(o_key4 && o_value4, false);
    ASSERT( !ooc_differ(o_key4, String("Bye bye now!")) && !ooc_differ(o_value4, String("Hello!")), false);
    o_node_not_found = Map_get(o_map, String("Ornitorrinco gigante"));
    ASSERT(o_node_not_found == NULL, false);
    OOC_DELETE(o_map);
    for(int i=0; i < ARRAY_C_SIZE(nodes4); i++){
        OOC_DELETE(nodes4[i]);
    }
    return true;
}

UNIT_TEST(tree_map_remove);
static bool tree_map_remove(){
    // Both not objects
    o_TreeMapNode nodes1[] = {TreeMapNodeKeyCValueCHelper(INT(9), int, INT(22), int),
                              TreeMapNodeKeyCValueCHelper(INT(15), int, INT(11), int),
                              TreeMapNodeKeyCValueCHelper(INT(2), int, INT(9), int)};
    o_TreeMap o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes1);
    ASSERT(Collection_size(o_map) == 3, false);
    ASSERT(Collection_remove(o_map, TreeMapNodeKeyCValueCHelper(INT(9), int, INT(22), int)),  false);
    ASSERT(Collection_size(o_map) == 2, false);
    ASSERT(!Collection_remove(o_map, TreeMapNodeKeyCValueCHelper(INT(18), int, INT(25), int)),  false);
    ASSERT(Collection_size(o_map) == 2, false);
    OOC_DELETE(o_map);
    for(int i=0; i < ARRAY_C_SIZE(nodes1); i++){
        OOC_DELETE(nodes1[i]);
    }
    // Value not object
    o_TreeMapNode nodes2[] = {  TreeMapNodeKeyCHelper(INT(28), int, String("Tree")),
                                TreeMapNodeKeyCHelper(INT(51), int, String("Banana")),
                                TreeMapNodeKeyCHelper(INT(74), int, String("Kite")),
                                TreeMapNodeKeyCHelper(INT(99), int, String("Kitty"))};
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes2);
    ASSERT(Collection_size(o_map) == 4, false);
    ASSERT(Collection_remove(o_map, TreeMapNodeKeyCHelper(INT(51), int, String("Banana"))),  false);
    ASSERT(Collection_size(o_map) == 3, false);
    ASSERT(!Collection_remove(o_map, TreeMapNodeKeyCHelper(INT(124), int, String("Ball"))),  false);
    ASSERT(Collection_size(o_map) == 3, false);
    OOC_DELETE(o_map);
    for(int i=0; i < ARRAY_C_SIZE(nodes2); i++){
        OOC_DELETE(nodes2[i]);
    }
    // Key not object
    o_TreeMapNode nodes3[] = {  TreeMapNodeValueCHelper(String("Arvore"), INT(489), int),
                                TreeMapNodeValueCHelper(String("Baia"), INT(312), int),
                                TreeMapNodeValueCHelper(String("Cachorro"), INT(46), int),
                                TreeMapNodeValueCHelper(String("Duende"), INT(874), int),
                                TreeMapNodeValueCHelper(String("Elevador"), INT(984), int)};
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes3);
    ASSERT(Collection_size(o_map) == 5, false);
    ASSERT(Collection_remove(o_map, TreeMapNodeValueCHelper(String("Cachorro"), INT(46), int)),  false);
    ASSERT(Collection_size(o_map) == 4, false);
    ASSERT(!Collection_remove(o_map, TreeMapNodeValueCHelper(String("Leao"), INT(98), int)),  false);
    ASSERT(Collection_size(o_map) == 4, false);
    OOC_DELETE(o_map);
    for(int i=0; i < ARRAY_C_SIZE(nodes3); i++){
        OOC_DELETE(nodes3[i]);
    }
    // Both objects
    o_TreeMapNode nodes4[] = {  TreeMapNode(String("All the things!"), String("Nothing!")),
                                TreeMapNode(String("Bye bye now!"), String("Hello!"))};
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes4);
    ASSERT(Collection_size(o_map) == 2, false);
    ASSERT(Collection_remove(o_map, TreeMapNode(String("All the things!"), String("Nothing!"))),  false);
    ASSERT(Collection_size(o_map) == 1, false);
    ASSERT(!Collection_remove(o_map, TreeMapNode(String("Other things"), String("Something"))),  false);
    ASSERT(Collection_size(o_map) == 1, false);
    OOC_DELETE(o_map);
    for(int i=0; i < ARRAY_C_SIZE(nodes4); i++){
        OOC_DELETE(nodes4[i]);
    }
    return true;
}

UNIT_TEST(tree_map_remove_all);
static bool tree_map_remove_all(){
    // Both not objects
    o_TreeMapNode nodes1[] = {TreeMapNodeKeyCValueCHelper(INT(9), int, INT(22), int),
                              TreeMapNodeKeyCValueCHelper(INT(15), int, INT(11), int),
                              TreeMapNodeKeyCValueCHelper(INT(2), int, INT(9), int)};
    o_TreeMapNode nodes_to_remove1[] = {  TreeMapNodeKeyCValueCHelper(INT(9), int, INT(22), int),
                                          TreeMapNodeKeyCValueCHelper(INT(17), int, INT(35), int),
                                          TreeMapNodeKeyCValueCHelper(INT(2), int, INT(9), int)};
    o_TreeMap o_map = TreeMap();
    o_Vector o_vector = Vector();
    Collection_addAllCObject(o_map, nodes1);
    Collection_addAllCObject(o_vector, nodes_to_remove1);
    ASSERT(Collection_size(o_map) == 3, false);
    ASSERT(Collection_removeAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == 1, false);
    ASSERT(!Collection_removeAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == 1, false);
    OOC_DELETE(o_map);
    OOC_DELETE(o_vector);
    ooc_deleteCArrayContent(nodes1);
    ooc_deleteCArrayContent(nodes_to_remove1);
    // Value not object
    o_TreeMapNode nodes2[] = {  TreeMapNodeKeyCHelper(INT(28), int, String("Tree")),
                                TreeMapNodeKeyCHelper(INT(51), int, String("Banana")),
                                TreeMapNodeKeyCHelper(INT(74), int, String("Kite")),
                                TreeMapNodeKeyCHelper(INT(99), int, String("Kitty"))};
    o_TreeMapNode nodes_to_remove2[] = {  TreeMapNodeKeyCHelper(INT(25), int, String("Tree")),
                                          TreeMapNodeKeyCHelper(INT(28), int, String("Tree")),
                                          TreeMapNodeKeyCHelper(INT(74), int, String("Kite")),
                                          TreeMapNodeKeyCHelper(INT(25), int, String("Apple"))};
    o_map = TreeMap();
    o_vector = Vector();
    Collection_addAllCObject(o_map, nodes2);
    Collection_addAllCObject(o_vector, nodes_to_remove2);
    ASSERT(Collection_size(o_map) == 4, false);
    ASSERT(Collection_removeAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == 2, false);
    ASSERT(!Collection_removeAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == 2, false);
    OOC_DELETE(o_map);
    OOC_DELETE(o_vector);
    ooc_deleteCArrayContent(nodes2);
    ooc_deleteCArrayContent(nodes_to_remove2);
    // Key not object
    o_TreeMapNode nodes3[] = {  TreeMapNodeValueCHelper(String("Arvore"), INT(489), int),
                                TreeMapNodeValueCHelper(String("Baia"), INT(312), int),
                                TreeMapNodeValueCHelper(String("Cachorro"), INT(46), int),
                                TreeMapNodeValueCHelper(String("Duende"), INT(874), int),
                                TreeMapNodeValueCHelper(String("Elevador"), INT(984), int)};
    o_TreeMapNode nodes_to_remove3[] = {  TreeMapNodeValueCHelper(String("Louca"), INT(489), int),
                                          TreeMapNodeValueCHelper(String("Baia"), INT(312), int),
                                          TreeMapNodeValueCHelper(String("Pao"), INT(46), int),
                                          TreeMapNodeValueCHelper(String("Duende"), INT(555), int),
                                          TreeMapNodeValueCHelper(String("Elevador"), INT(984), int)};
    o_map = TreeMap();
    o_vector = Vector();
    Collection_addAllCObject(o_map, nodes3);
    Collection_addAllCObject(o_vector, nodes_to_remove3);
    ASSERT(Collection_size(o_map) == 5, false);
    ASSERT(Collection_removeAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == 3, false);
    ASSERT(!Collection_removeAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == 3, false);
    OOC_DELETE(o_map);
    OOC_DELETE(o_vector);
    ooc_deleteCArrayContent(nodes3);
    ooc_deleteCArrayContent(nodes_to_remove3);
    // Both objects
    o_TreeMapNode nodes4[] = {  TreeMapNode(String("All the things!"), String("Nothing!")),
                                TreeMapNode(String("Bye bye now!"), String("Hello!"))};
    o_TreeMapNode nodes_to_remove4[] = {  TreeMapNode(String("All the things!"), String("Nothing!")),
                                          TreeMapNode(String("Bye hello now!"), String("Hello!")),
                                          TreeMapNode(String("All things!"), String("Nothing!")),
                                          TreeMapNode(String("Bye bye now!"), String("Something!"))};
    o_map = TreeMap();
    o_vector = Vector();
    Collection_addAllCObject(o_map, nodes4);
    Collection_addAllCObject(o_vector, nodes_to_remove4);
    ASSERT(Collection_size(o_map) == 2, false);
    ASSERT(Collection_removeAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == 1, false);
    ASSERT(!Collection_removeAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == 1, false);
    OOC_DELETE(o_map);
    OOC_DELETE(o_vector);
    ooc_deleteCArrayContent(nodes4);
    ooc_deleteCArrayContent(nodes_to_remove4);
    return true;
}

UNIT_TEST(tree_map_retain_all);
static bool tree_map_retain_all(){
    // Both not objects
    o_TreeMapNode nodes1[] = {TreeMapNodeKeyCValueCHelper(INT(9), int, INT(22), int),
                              TreeMapNodeKeyCValueCHelper(INT(15), int, INT(11), int),
                              TreeMapNodeKeyCValueCHelper(INT(2), int, INT(9), int)};
    o_TreeMapNode nodes_to_retain1[] = {  TreeMapNodeKeyCValueCHelper(INT(9), int, INT(22), int),
                                          TreeMapNodeKeyCValueCHelper(INT(17), int, INT(35), int),
                                          TreeMapNodeKeyCValueCHelper(INT(2), int, INT(9), int)};
    o_TreeMapNode nodes_result1[] = {  TreeMapNodeKeyCValueCHelper(INT(2), int, INT(9), int),
                                       TreeMapNodeKeyCValueCHelper(INT(9), int, INT(22), int)};
    o_TreeMap o_map = TreeMap();
    o_Vector o_vector = Vector();
    Collection_addAllCObject(o_map, nodes1);
    Collection_addAllCObject(o_vector, nodes_to_retain1);
    ASSERT(Collection_size(o_map) == ARRAY_C_SIZE(nodes1), false);
    ASSERT(Collection_retainAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == ARRAY_C_SIZE(nodes_result1), false);
    ASSERT(Collection_retainAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == ARRAY_C_SIZE(nodes_result1), false);
    o_Iterator o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        ASSERT( Comparable_compareTo(o_node, Clonable_clone(nodes_result1[i])) == 0, false);
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    OOC_DELETE(o_vector);
    ooc_deleteCArrayContent(nodes1);
    ooc_deleteCArrayContent(nodes_to_retain1);
    ooc_deleteCArrayContent(nodes_result1);
    // Value not object
    o_TreeMapNode nodes2[] = {  TreeMapNodeKeyCHelper(INT(28), int, String("Tree")),
                                TreeMapNodeKeyCHelper(INT(51), int, String("Banana")),
                                TreeMapNodeKeyCHelper(INT(74), int, String("Kite")),
                                TreeMapNodeKeyCHelper(INT(99), int, String("Kitty"))};
    o_TreeMapNode nodes_to_retain2[] = {  TreeMapNodeKeyCHelper(INT(25), int, String("Tree")),
                                          TreeMapNodeKeyCHelper(INT(28), int, String("Tree")),
                                          TreeMapNodeKeyCHelper(INT(74), int, String("Kite")),
                                          TreeMapNodeKeyCHelper(INT(25), int, String("Apple"))};
    o_TreeMapNode nodes_result2[] = {  TreeMapNodeKeyCHelper(INT(28), int, String("Tree")),
                                       TreeMapNodeKeyCHelper(INT(74), int, String("Kite"))};
    o_map = TreeMap();
    o_vector = Vector();
    Collection_addAllCObject(o_map, nodes2);
    Collection_addAllCObject(o_vector, nodes_to_retain2);
    ASSERT(Collection_size(o_map) == ARRAY_C_SIZE(nodes2), false);
    ASSERT(Collection_retainAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == ARRAY_C_SIZE(nodes_result2), false);
    ASSERT(Collection_retainAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == ARRAY_C_SIZE(nodes_result2), false);
    o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        ASSERT( Comparable_compareTo(o_node, Clonable_clone(nodes_result2[i])) == 0, false);
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    OOC_DELETE(o_vector);
    ooc_deleteCArrayContent(nodes2);
    ooc_deleteCArrayContent(nodes_to_retain2);
    ooc_deleteCArrayContent(nodes_result2);
    // Key not object
    o_TreeMapNode nodes3[] = {  TreeMapNodeValueCHelper(String("Arvore"), INT(489), int),
                                TreeMapNodeValueCHelper(String("Baia"), INT(312), int),
                                TreeMapNodeValueCHelper(String("Cachorro"), INT(46), int),
                                TreeMapNodeValueCHelper(String("Duende"), INT(874), int),
                                TreeMapNodeValueCHelper(String("Elevador"), INT(984), int)};
    o_TreeMapNode nodes_to_retain3[] = {  TreeMapNodeValueCHelper(String("Louca"), INT(489), int),
                                          TreeMapNodeValueCHelper(String("Baia"), INT(312), int),
                                          TreeMapNodeValueCHelper(String("Pao"), INT(46), int),
                                          TreeMapNodeValueCHelper(String("Duende"), INT(555), int),
                                          TreeMapNodeValueCHelper(String("Elevador"), INT(984), int)};
    o_TreeMapNode nodes_result3[] = {  TreeMapNodeValueCHelper(String("Baia"), INT(312), int),
                                       TreeMapNodeValueCHelper(String("Elevador"), INT(984), int)};
    o_map = TreeMap();
    o_vector = Vector();
    Collection_addAllCObject(o_map, nodes3);
    Collection_addAllCObject(o_vector, nodes_to_retain3);
    ASSERT(Collection_size(o_map) == ARRAY_C_SIZE(nodes3), false);
    ASSERT(Collection_retainAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == ARRAY_C_SIZE(nodes_result3), false);
    ASSERT(Collection_retainAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == ARRAY_C_SIZE(nodes_result3), false);
    o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        ASSERT( Comparable_compareTo(o_node, Clonable_clone(nodes_result3[i])) == 0, false);
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    OOC_DELETE(o_vector);
    ooc_deleteCArrayContent(nodes3);
    ooc_deleteCArrayContent(nodes_to_retain3);
    ooc_deleteCArrayContent(nodes_result3);
    // Both objects
    o_TreeMapNode nodes4[] = {  TreeMapNode(String("All the things!"), String("Nothing!")),
                                TreeMapNode(String("Bye bye now!"), String("Hello!"))};
    o_TreeMapNode nodes_to_retain4[] = {  TreeMapNode(String("All the things!"), String("Nothing!")),
                                          TreeMapNode(String("Bye hello now!"), String("Hello!")),
                                          TreeMapNode(String("All things!"), String("Nothing!")),
                                          TreeMapNode(String("Bye bye now!"), String("Something!"))};
    o_TreeMapNode nodes_result4[] = {  TreeMapNode(String("All the things!"), String("Nothing!")) };
    o_map = TreeMap();
    o_vector = Vector();
    Collection_addAllCObject(o_map, nodes4);
    Collection_addAllCObject(o_vector, nodes_to_retain4);
    ASSERT(Collection_size(o_map) == ARRAY_C_SIZE(nodes4), false);
    ASSERT(Collection_retainAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == ARRAY_C_SIZE(nodes_result4), false);
    ASSERT(Collection_retainAll(o_map, o_vector),  false);
    ASSERT(Collection_size(o_map) == ARRAY_C_SIZE(nodes_result4), false);
    o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        ASSERT( Comparable_compareTo(o_node, Clonable_clone(nodes_result4[i])) == 0, false);
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    OOC_DELETE(o_vector);
    ooc_deleteCArrayContent(nodes4);
    ooc_deleteCArrayContent(nodes_to_retain4);
    ooc_deleteCArrayContent(nodes_result4);
    return true;
}

UNIT_TEST(tree_map_to_array);
static bool tree_map_to_array(){
    // Both not objects
    o_TreeMapNode nodes1[] = {TreeMapNodeKeyCValueCHelper(INT(9), int, INT(22), int),
                              TreeMapNodeKeyCValueCHelper(INT(15), int, INT(11), int),
                              TreeMapNodeKeyCValueCHelper(INT(2), int, INT(9), int)};
    o_TreeMap o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes1);
    int array_size;
    void** map_c_array1 = Collection_toArray(o_map, &array_size);
    ASSERT(map_c_array1 && map_c_array1[0], false);
    ASSERT( (Collection_size(o_map) == ARRAY_C_SIZE(nodes1)) && (array_size == ARRAY_C_SIZE(nodes1)) , false);
    o_Iterator o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        ASSERT( Comparable_compareTo(o_node, Clonable_clone(map_c_array1[i])) == 0, false);
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    ooc_deleteCArrayContent(nodes1);
    for(int i = 0; i < array_size; i++){
        OOC_DELETE(map_c_array1[i]);
    }
    OOC_DELETE(map_c_array1);
    // Value not object
    o_TreeMapNode nodes2[] = {  TreeMapNodeKeyCHelper(INT(28), int, String("Tree")),
                                TreeMapNodeKeyCHelper(INT(51), int, String("Banana")),
                                TreeMapNodeKeyCHelper(INT(74), int, String("Kite")),
                                TreeMapNodeKeyCHelper(INT(99), int, String("Kitty"))};
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes2);
    void** map_c_array2 = Collection_toArray(o_map, &array_size);
    ASSERT(map_c_array2 && map_c_array2[0], false);
    ASSERT( (Collection_size(o_map) == ARRAY_C_SIZE(nodes2)) && (array_size == ARRAY_C_SIZE(nodes2)), false);
    o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        ASSERT( Comparable_compareTo(o_node, Clonable_clone(map_c_array2[i])) == 0, false);
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    ooc_deleteCArrayContent(nodes2);
    for(int i = 0; i < array_size; i++){
        OOC_DELETE(map_c_array2[i]);
    }
    OOC_DELETE(map_c_array2);
    // Key not object
    o_TreeMapNode nodes3[] = {  TreeMapNodeValueCHelper(String("Arvore"), INT(489), int),
                                TreeMapNodeValueCHelper(String("Baia"), INT(312), int),
                                TreeMapNodeValueCHelper(String("Cachorro"), INT(46), int),
                                TreeMapNodeValueCHelper(String("Duende"), INT(874), int),
                                TreeMapNodeValueCHelper(String("Elevador"), INT(984), int)};
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes3);
    void** map_c_array3 = Collection_toArray(o_map, &array_size);
    ASSERT(map_c_array3 && map_c_array3[0], false);
    ASSERT( (Collection_size(o_map) == ARRAY_C_SIZE(nodes3)) && (array_size == ARRAY_C_SIZE(nodes3)), false);
    o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        ASSERT( Comparable_compareTo(o_node, Clonable_clone(map_c_array3[i])) == 0, false);
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    ooc_deleteCArrayContent(nodes3);
    for(int i = 0; i < array_size; i++){
        OOC_DELETE(map_c_array3[i]);
    }
    OOC_DELETE(map_c_array3);
    // Both objects
    o_TreeMapNode nodes4[] = {  TreeMapNode(String("All the things!"), String("Nothing!")),
                                TreeMapNode(String("Bye bye now!"), String("Hello!"))};
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes4);
    void** map_c_array4 = Collection_toArray(o_map, &array_size);
    ASSERT(map_c_array4 && map_c_array4[0], false);
    ASSERT( (Collection_size(o_map) == ARRAY_C_SIZE(nodes4)) && (array_size == ARRAY_C_SIZE(nodes4)), false);
    o_iterator = Iterable_create(o_map);
    for(int i = 0;!Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode o_node = Iterator_currItem(o_iterator);
        ASSERT(o_node, false);
        ASSERT( Comparable_compareTo(o_node, Clonable_clone(map_c_array4[i])) == 0, false);
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_map);
    ooc_deleteCArrayContent(nodes4);
    for(int i = 0; i < array_size; i++){
        OOC_DELETE(map_c_array4[i]);
    }
    OOC_DELETE(map_c_array4);
    return true;
}

UNIT_TEST(tree_map_list_add);
static bool tree_map_list_add(){
    // Both not objects
    o_TreeMap o_map = TreeMap();
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(2), int, INT(99), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(5), int, INT(17), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(7), int, INT(35), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(9), int, INT(68), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(15), int, INT(98), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(17), int, INT(20), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(25), int, INT(11), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(28), int, INT(63), int), false);
    ASSERT(!Map_addKeyCValueCHelper(o_map, INT(2), int, INT(66), int), false);
    ASSERT(Collection_size(o_map) == 8, false);
    OOC_DELETE(o_map);
    // Value not object
    o_map = TreeMap();
    ASSERT(Map_addKeyCHelper(o_map, INT(2), int, String("99")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(5), int, String("17")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(7), int, String("35")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(9), int, String("68")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(15), int, String("98")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(17), int, String("20")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(25), int, String("11")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(28), int, String("63")), false);
    ASSERT(!Map_addKeyCHelper(o_map, INT(2), int, String("66")), false);
    ASSERT(Collection_size(o_map) == 8, false);
    OOC_DELETE(o_map);
    // Key not object
    o_map = TreeMap();
    ASSERT(Map_addValueCHelper(o_map, String("A"), INT(99), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("B"), INT(17), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("C"), INT(35), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("D"), INT(68), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("E"), INT(98), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("F"), INT(20), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("G"), INT(11), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("H"), INT(63), int), false);
    ASSERT(!Map_addValueCHelper(o_map, String("A"), INT(66), int), false);
    ASSERT(Collection_size(o_map) == 8, false);
    OOC_DELETE(o_map);
    // Both objects
    o_map = TreeMap();
    ASSERT(Map_add(o_map, String("A"), String("99")), false);
    ASSERT(Map_add(o_map, String("B"), String("17")), false);
    ASSERT(Map_add(o_map, String("C"), String("35")), false);
    ASSERT(Map_add(o_map, String("D"), String("68")), false);
    ASSERT(Map_add(o_map, String("E"), String("98")), false);
    ASSERT(Map_add(o_map, String("F"), String("20")), false);
    ASSERT(Map_add(o_map, String("G"), String("11")), false);
    ASSERT(Map_add(o_map, String("H"), String("63")), false);
    ASSERT(!Map_add(o_map, String("A"), String("66")), false);
    ASSERT(Collection_size(o_map) == 8, false);
    OOC_DELETE(o_map);
    return true;
}

UNIT_TEST(tree_map_list_find_by_value_remove_by_key_remove_by_value);
static bool tree_map_list_find_by_value_remove_by_key_remove_by_value(){
    // Both not objects
    o_TreeMap o_map = TreeMap();
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(2), int, INT(99), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(5), int, INT(17), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(7), int, INT(35), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(9), int, INT(68), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(15), int, INT(98), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(17), int, INT(20), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(25), int, INT(11), int), false);
    ASSERT(Map_addKeyCValueCHelper(o_map, INT(28), int, INT(63), int), false);
    ASSERT(!Map_addKeyCValueCHelper(o_map, INT(2), int, INT(66), int), false);
    ASSERT(Collection_size(o_map) == 8, false);
    o_TreeMapNode o_node = Map_findByValue(o_map, INT(98));
    ASSERT(o_node, false);
    ASSERT(Comparable_compareTo(o_node, TreeMapNodeKeyCValueCHelper(INT(15), int, INT(98), int)) == 0, false)
    o_node = Map_findByValue(o_map, INT(154));
    ASSERT(!o_node, false);
    ASSERT(Map_deleteByValue(o_map, INT(98)), false);
    ASSERT(Collection_size(o_map) == 7, false);
    ASSERT(!Map_deleteByValue(o_map, INT(9000)), false);
    ASSERT(Collection_size(o_map) == 7, false);
    ASSERT(Map_deleteByKey(o_map, INT(25)), false);
    ASSERT(Collection_size(o_map) == 6, false);
    ASSERT(!Map_deleteByKey(o_map, INT(954)), false);
    ASSERT(Collection_size(o_map) == 6, false);
    OOC_DELETE(o_map);
    // Value not object
    o_map = TreeMap();
    ASSERT(Map_addKeyCHelper(o_map, INT(2), int, String("99")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(5), int, String("17")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(7), int, String("35")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(9), int, String("68")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(15), int, String("98")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(17), int, String("20")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(25), int, String("11")), false);
    ASSERT(Map_addKeyCHelper(o_map, INT(28), int, String("63")), false);
    ASSERT(!Map_addKeyCHelper(o_map, INT(2), int, String("66")), false);
    ASSERT(Collection_size(o_map) == 8, false);
    o_node = Map_findByValue(o_map, String("11"));
    ASSERT(o_node, false);
    ASSERT( Comparable_compareTo(o_node, TreeMapNodeKeyCHelper(INT(25), int, String("11"))) == 0, false)
    o_node = Map_findByValue(o_map, String("Albatroz"));
    ASSERT(!o_node, false);
    ASSERT(Map_deleteByValue(o_map, String("20")), false);
    ASSERT(Collection_size(o_map) == 7, false);
    ASSERT(!Map_deleteByValue(o_map, String("Cat")), false);
    ASSERT(Collection_size(o_map) == 7, false);
    ASSERT(Map_deleteByKey(o_map, INT(28)), false);
    ASSERT(Collection_size(o_map) == 6, false);
    ASSERT(!Map_deleteByKey(o_map, INT(356)), false);
    ASSERT(Collection_size(o_map) == 6, false);
    OOC_DELETE(o_map);
    // Key not object
    o_map = TreeMap();
    ASSERT(Map_addValueCHelper(o_map, String("A"), INT(99), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("B"), INT(17), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("C"), INT(35), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("D"), INT(68), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("E"), INT(98), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("F"), INT(20), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("G"), INT(11), int), false);
    ASSERT(Map_addValueCHelper(o_map, String("H"), INT(63), int), false);
    ASSERT(!Map_addValueCHelper(o_map, String("A"), INT(66), int), false);
    ASSERT(Collection_size(o_map) == 8, false);
    o_node = Map_findByValue(o_map, INT(63));
    ASSERT(o_node, false);
    ASSERT( Comparable_compareTo(o_node, TreeMapNodeValueCHelper(String("H"), INT(63), int)) == 0, false)
    o_node = Map_findByValue(o_map, INT(154));
    ASSERT(!o_node, false);
    ASSERT(Map_deleteByValue(o_map, INT(17)), false);
    ASSERT(Collection_size(o_map) == 7, false);
    ASSERT(!Map_deleteByValue(o_map, INT(3254)), false);
    ASSERT(Collection_size(o_map) == 7, false);
    ASSERT(Map_deleteByKey(o_map, String("F")), false);
    ASSERT(Collection_size(o_map) == 6, false);
    ASSERT(!Map_deleteByKey(o_map, String("Sabao")), false);
    ASSERT(Collection_size(o_map) == 6, false);
    OOC_DELETE(o_map);
    // Both objects
    o_map = TreeMap();
    ASSERT(Map_add(o_map, String("A"), String("99")), false);
    ASSERT(Map_add(o_map, String("B"), String("17")), false);
    ASSERT(Map_add(o_map, String("C"), String("35")), false);
    ASSERT(Map_add(o_map, String("D"), String("68")), false);
    ASSERT(Map_add(o_map, String("E"), String("98")), false);
    ASSERT(Map_add(o_map, String("F"), String("20")), false);
    ASSERT(Map_add(o_map, String("G"), String("11")), false);
    ASSERT(Map_add(o_map, String("H"), String("63")), false);
    ASSERT(!Map_add(o_map, String("A"), String("66")), false);
    ASSERT(Collection_size(o_map) == 8, false);
    o_node = Map_findByValue(o_map, String("98"));
    ASSERT(o_node, false);
    ASSERT( Comparable_compareTo(o_node, TreeMapNode(String("E"), String("98"))) == 0, false)
    o_node = Map_findByValue(o_map, String("Zorro"));
    ASSERT(!o_node, false);
    ASSERT(Map_deleteByValue(o_map, String("35")), false);
    ASSERT(Collection_size(o_map) == 7, false);
    ASSERT(!Map_deleteByValue(o_map, String("Katze")), false);
    ASSERT(Collection_size(o_map) == 7, false);
    ASSERT(Map_deleteByKey(o_map, String("D")), false);
    ASSERT(Collection_size(o_map) == 6, false);
    ASSERT(!Map_deleteByKey(o_map, String("Mitsy")), false);
    ASSERT(Collection_size(o_map) == 6, false);
    OOC_DELETE(o_map);
    return true;
}

UNIT_TEST(tree_map_get_key_get_key_get_values);
static bool tree_map_get_key_get_key_get_values(){
    // Both not objects
    o_TreeMapNode nodes1[] = {TreeMapNodeKeyCValueCHelper(INT(9), int, INT(22), int),
                              TreeMapNodeKeyCValueCHelper(INT(15), int, INT(11), int),
                              TreeMapNodeKeyCValueCHelper(INT(2), int, INT(9), int)};
    int* key_results1 [] = { INT(2), INT(9), INT(15) };
    int* value_results1 [] = { INT(9), INT(22), INT(11) };
    o_TreeMap o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes1);
    int* p_key1 = Map_getKey(o_map, INT(22));
    ASSERT(p_key1, false);
    ASSERT(*p_key1 == 9, false);
    o_Vector o_key_vector = Map_getKeys(o_map);
    ASSERT(o_key_vector, false);
    ASSERT(Collection_size(o_key_vector) == ARRAY_C_SIZE(key_results1), false);
    o_Iterator o_iterator = Iterable_create(o_key_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        int* p_key = Iterator_currItem(o_iterator);
        ASSERT(p_key, false);
        ASSERT(*p_key == *key_results1[i], false);
    }
    OOC_DELETE(o_iterator);
    o_Vector o_value_vector = Map_getValues(o_map);
    ASSERT(o_value_vector, false);
    ASSERT(Collection_size(o_value_vector) == ARRAY_C_SIZE(value_results1), false);
    o_iterator = Iterable_create(o_value_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        int* p_value = Iterator_currItem(o_iterator);
        ASSERT(p_value, false);
        ASSERT(*p_value == *value_results1[i], false);
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_key_vector);
    OOC_DELETE(o_value_vector);
    OOC_DELETE(o_map);
    ooc_deleteCArrayContent(nodes1);
    ooc_deleteCArrayContent(key_results1);
    ooc_deleteCArrayContent(value_results1);
    // Value not object
    o_TreeMapNode nodes2[] = {  TreeMapNodeKeyCHelper(INT(28), int, String("Tree")),
                                TreeMapNodeKeyCHelper(INT(51), int, String("Banana")),
                                TreeMapNodeKeyCHelper(INT(74), int, String("Kite")),
                                TreeMapNodeKeyCHelper(INT(99), int, String("Kitty"))};
    int* key_results2 [] = { INT(28), INT(51), INT(74), INT(99) };
    o_String value_results2[] = {String("Tree"), String("Banana"), String("Kite"), String("Kitty")};
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes2);
    int* p_key2 = Map_getKey(o_map, String("Kitty"));
    ASSERT(p_key2, false);
    ASSERT(*p_key2 == 99, false);
    o_key_vector = Map_getKeys(o_map);
    ASSERT(o_key_vector, false);
    ASSERT(Collection_size(o_key_vector) == ARRAY_C_SIZE(key_results2), false);
    o_iterator = Iterable_create(o_key_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        int* p_key = Iterator_currItem(o_iterator);
        ASSERT(p_key, false);
        ASSERT(*p_key == *key_results2[i], false);
    }
    OOC_DELETE(o_iterator);
    o_value_vector = Map_getValues(o_map);
    ASSERT(o_value_vector, false);
    ASSERT(Collection_size(o_value_vector) == ARRAY_C_SIZE(value_results2), false);
    o_iterator = Iterable_create(o_value_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_String o_value = Iterator_currItem(o_iterator);
        ASSERT(o_value, false);
        ASSERT(!ooc_differ(o_value, Clonable_clone(value_results2[i])), false);
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_key_vector);
    OOC_DELETE(o_value_vector);
    OOC_DELETE(o_map);
    ooc_deleteCArrayContent(nodes2);
    ooc_deleteCArrayContent(key_results2);
    ooc_deleteCArrayContent(value_results2);
    // Key not object
    o_TreeMapNode nodes3[] = {  TreeMapNodeValueCHelper(String("Arvore"), INT(489), int),
                                TreeMapNodeValueCHelper(String("Baia"), INT(312), int),
                                TreeMapNodeValueCHelper(String("Cachorro"), INT(46), int),
                                TreeMapNodeValueCHelper(String("Duende"), INT(874), int),
                                TreeMapNodeValueCHelper(String("Elevador"), INT(984), int)};
    o_String key_results3 [] = { String("Arvore"), String("Baia"),
            String("Cachorro"), String("Duende"), String("Elevador") };
    int* value_results3 [] = { INT(489), INT(312), INT(46), INT(874), INT(984) };
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes3);
    o_String o_key3 = Map_getKey(o_map, INT(874));
    ASSERT(o_key3, false);
    ASSERT( !ooc_differ(o_key3, String("Duende")) , false);
    o_key_vector = Map_getKeys(o_map);
    ASSERT(o_key_vector, false);
    ASSERT(Collection_size(o_key_vector) == ARRAY_C_SIZE(key_results3), false);
    o_iterator = Iterable_create(o_key_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_String o_key = Iterator_currItem(o_iterator);
        ASSERT(o_key, false);
        ASSERT( !ooc_differ(o_key, Clonable_clone(key_results3[i])), false);
    }
    OOC_DELETE(o_iterator);
    o_value_vector = Map_getValues(o_map);
    ASSERT(o_value_vector, false);
    ASSERT(Collection_size(o_value_vector) == ARRAY_C_SIZE(value_results3), false);
    o_iterator = Iterable_create(o_value_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        int* p_value = Iterator_currItem(o_iterator);
        ASSERT(p_value, false);
        ASSERT(*p_value == *value_results3[i], false);
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_key_vector);
    OOC_DELETE(o_value_vector);
    OOC_DELETE(o_map);
    ooc_deleteCArrayContent(nodes3);
    ooc_deleteCArrayContent(key_results3);
    ooc_deleteCArrayContent(value_results3);
    // Both objects
    o_TreeMapNode nodes4[] = {  TreeMapNode(String("All the things!"), String("Nothing!")),
                                TreeMapNode(String("Bye bye now!"), String("Hello!"))};
    o_String key_results4 [] = { String("All the things!"), String("Bye bye now!") };
    o_String value_results4[] = { String("Nothing!"), String("Hello!") };
    o_map = TreeMap();
    Collection_addAllCObject(o_map, nodes4);
    o_String o_key4 = Map_getKey(o_map, String("Nothing!"));
    ASSERT(o_key4, false);
    ASSERT( !ooc_differ(o_key4, String("All the things!")) , false);
    o_key_vector = Map_getKeys(o_map);
    ASSERT(o_key_vector, false);
    ASSERT(Collection_size(o_key_vector) == ARRAY_C_SIZE(key_results4), false);
    o_iterator = Iterable_create(o_key_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_String o_key = Iterator_currItem(o_iterator);
        ASSERT(o_key, false);
        ASSERT( !ooc_differ(o_key, Clonable_clone(key_results4[i])), false);
    }
    OOC_DELETE(o_iterator);
    o_value_vector = Map_getValues(o_map);
    ASSERT(o_value_vector, false);
    ASSERT(Collection_size(o_value_vector) == ARRAY_C_SIZE(value_results4), false);
    o_iterator = Iterable_create(o_value_vector);
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_String o_value = Iterator_currItem(o_iterator);
        ASSERT(o_value, false);
        ASSERT(!ooc_differ(o_value, Clonable_clone(value_results4[i])), false);
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_key_vector);
    OOC_DELETE(o_value_vector);
    OOC_DELETE(o_map);
    ooc_deleteCArrayContent(nodes4);
    ooc_deleteCArrayContent(key_results4);
    ooc_deleteCArrayContent(value_results4);
    return true;
}

void tree_map_test(){
    TreeMapNodeClass();
    TreeMapClass();
    TreeMapIteratorClass();
    StringClass();
    VectorClass();
    VectorIteratorClass();
    RUN_TEST(tree_map_test_node_c);
    RUN_TEST(tree_map_collection_add);
    RUN_TEST(tree_map_collection_add_all);
    RUN_TEST(tree_map_collection_add_all_c);
    RUN_TEST(tree_map_collection_clear_contains_is_empty);
    RUN_TEST(tree_map_remove);
    RUN_TEST(tree_map_remove_all);
    RUN_TEST(tree_map_retain_all);
    RUN_TEST(tree_map_to_array);
    RUN_TEST(tree_map_list_add);
    RUN_TEST(tree_map_list_find_by_value_remove_by_key_remove_by_value);
    RUN_TEST(tree_map_get_key_get_key_get_values);
}