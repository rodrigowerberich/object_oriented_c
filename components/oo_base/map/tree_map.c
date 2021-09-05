/*
 * tree_map.c
 *
 *  Created on: 9 de jan de 2019
 *      Author: lua
 */

#include <tree_map.h>
#include <tree_map.r>
#include <lua_assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <clonable_interface.h>
#include <comparable_interface.h>
#include <tree_map_helper_functions.h>
#include <tree_map_iterator.h>

/*------------------------------------------------*/
/*-------------- DEFINE HELPERS ------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
/*------------------- Helper methods -------------*/
/*------------------------------------------------*/
// Returns the node with the minimun key from the tree pointed by the node
TreeMapNode_r* tree_map_minimun(TreeMapNode_r* node){
    if(node){
        while(node->left){
            node = node->left;
        }
    }
    return node;
}
// Returns the node with the maximun key from the tree pointed by the node
TreeMapNode_r* tree_map_maximum(TreeMapNode_r* node){
    if(node){
        while(node->right){
            node = node->right;
        }
    }
    return node;
}
// Completely destroys and frees the three pointed by the node
static void tree_map_destroy(TreeMapNode_r* node){
    if(node){
        tree_map_destroy(node->left);
        tree_map_destroy(node->right);
        OOC_DELETE(node);
    }
}
// Add the node into the apropriate position of the binary tree
static bool tree_map_add(TreeMap_r* self, TreeMapNode_r* node){
    TreeMapNode_r* aux_y = 0;
    TreeMapNode_r* aux_x = self->root;
    while(aux_x != 0){
        aux_y = aux_x;
        if(tree_map_compare_keys(node, aux_x) < 0){
            aux_x = aux_x->left;
        }else if(tree_map_compare_keys(node, aux_x) > 0){
            aux_x = aux_x->right;
        }else{
            OOC_DELETE(node);
            return false;
        }
    }
    node->parent = aux_y;
    if(aux_y == NULL){
        self->root = node;
    }else if( tree_map_compare_keys(node, aux_y) < 0 ){
        aux_y->left = node;
    }else if( tree_map_compare_keys(node, aux_y) > 0 ){
        aux_y->right = node;
    }else{
        OOC_DELETE(node);
        return false;
    }
    return true;
}
// Calculate the height of the tree, that is how long is
// the deepest branch of it
int tree_map_height(TreeMapNode_r* node){
   if(node == NULL){
       return 0;
   }else{
       int left_heigth = tree_map_height(node->left);
       int right_height = tree_map_height(node->right);
       if(left_heigth > right_height){
           return left_heigth+1;
       }else{
           return right_height+1;
       }
   }
}
// Returns the mininum possible height for a tree of num_elements nodes
int tree_map_best_height(int num_element){
    // return ceil(log(num_element+1)/log(2));
    return ceil(log1p(num_element)/log(2));
}
// Transforms the three represented by the node into a vector,
// inserting it into the vector passed
void tree_map_nodes_vector(TreeMapNode_r* node, o_Vector vector){
    if(node){
        tree_map_nodes_vector(node->left, vector);
        Collection_add(vector, Clonable_clone(node));
        tree_map_nodes_vector(node->right, vector);
    }
}
// Returns a vector with the order in which to
// insert an ordered vector that goes from index 0 to index n-1, 
// being n the number of elements in the vector, into a tree to make
// it balanced
// Usage:
//  o_Vector order_vec = VectorC(int);
//  tree_map_rebalance_vector(0, 6, order_vec);
//  ... 
//  OOC_DELETE(order_vec);
// Given an ordered vector of keys 
//  Ex: [0,10,25,38,41,50,67]
// This function will return [3, 1, 0, 2, 5, 4 ,6]
void tree_map_rebalance_vector(int start, int end, o_Vector o_vector){
    int insert_now = floor((start+end)/2);
    Collection_add(o_vector, INT(insert_now));
    if(start <= insert_now-1){
        tree_map_rebalance_vector(start, insert_now-1, o_vector);
    }
    if(end >= insert_now+1){
        tree_map_rebalance_vector(insert_now+1, end, o_vector);
    }
}
// Checks if the tree height is 2 nodes above the best possible for that amount of nodes,
// if it is, rebalances it to have its optimum height
static void  tree_map_rebalance(TreeMap_r* self){
    int best_height = tree_map_best_height(self->node_count);
    if( (self->height - best_height) > 2){
        o_Vector o_vector = Vector();
        tree_map_nodes_vector(self->root, o_vector);
        tree_map_destroy(self->root);
        self->root = NULL;
        o_Vector order_vec = VectorC(int);
        tree_map_rebalance_vector(0, Collection_size(o_vector)-1, order_vec);
        o_Iterator o_iterator = Iterable_create(order_vec);
        for(;!Iterator_isDone(o_iterator); Iterator_next(o_iterator)){
            int* p_index_to_insert = Iterator_currItem(o_iterator);
            if(p_index_to_insert){
                tree_map_add(self, Clonable_clone(List_get(o_vector, *p_index_to_insert)));
            }
        }
        OOC_DELETE(o_iterator);
        OOC_DELETE(o_vector);
        OOC_DELETE(order_vec);
        self->height = tree_map_height(self->root);
    }
#if 0
    printf("Height: %d, Len: %d, Best Height: %d\n", self->height, self->node_count, best_height);
#endif 
}
// Changes node U for node V in the tree structure, but only for the parents,
// That means that whoever was the parent of node u is now the parent of node v,
// and node u does not have a parent anymore
static void tree_map_transplant(TreeMap_r* map, TreeMapNode_r* node_u, TreeMapNode_r* node_v){
    if(node_u->parent == NULL){
        map->root = node_v;
    }else if(node_u == node_u->parent->left){
        node_u->parent->left = node_v;
    }else{
        node_u->parent->right = node_v;
    }
    if(node_v != NULL){
        node_v->parent = node_u->parent;
    }
}
// Removes a node from the tree
static bool tree_map_delete(TreeMap_r* self, TreeMapNode_r* node){
    ASSERT(self && node, false);
    if(node->left == NULL){
        tree_map_transplant(self, node, node->right);
    }else if(node->right == NULL){
        tree_map_transplant(self, node, node->left);
    }else{
        TreeMapNode_r* node_y = tree_map_minimun(node->right);
        if(node_y->parent != node){
            tree_map_transplant(self, node_y, node_y->right);
            node_y->right = node->right;
            node_y->right->parent = node_y;
        }
        tree_map_transplant(self, node, node_y);
        node_y->left = node->left;
        node_y->left->parent = node_y;
    }
    OOC_DELETE(node);
    self->node_count--;
    self->height = tree_map_height(self->root);
    tree_map_rebalance(self);
    return true;
}
/*------------------------------------------------*/
/*--------------- Class methods ------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
/*----------- Static linked methods --------------*/
/*------------------------------------------------*/

void* TreeMapNode_getKey(const void* _self){
    CAST(self, TreeMapNode);
    ASSERT(self, NULL);
    return self->key;
}
void* TreeMapNode_getValue(const void* _self){
    CAST(self, TreeMapNode);
    ASSERT(self, NULL);
    return self->value;
}
int TreeMapNode_compareKey(const void* _self, void* other_key){
    CAST(self, TreeMapNode);
    ASSERT(self, INT_MAX);
    CHECK_INTERFACE(compareTo, self->key, M_COMPARABLE_COMPARE_TO);
    if(compareTo){
        return compareTo(self->key, other_key);
    }else{
        if(ooc_isObject(other_key)){
            return ooc_differ(self->key, other_key);
        }else{
            int result = memcmp(self->key, other_key, self->key_size);
            OOC_DELETE(other_key);
            return result;
        }
    }
}
int TreeMapNode_compareValue(const void* _self, void* other_value){
    CAST(self, TreeMapNode);
    ASSERT(self, INT_MAX);
    CHECK_INTERFACE(compareTo, self->value, M_COMPARABLE_COMPARE_TO);
    if(compareTo){
        return compareTo(self->value, other_value);
    }else{
        if(ooc_isObject(other_value)){
            return ooc_differ(self->value, other_value);
        }else{
            int result = memcmp(self->value, other_value, self->value_size);
            OOC_DELETE(other_value);
            return result;
        }
    }
}

/*------------------------------------------------*/
/*----------- Dynamic linked methods -------------*/
/*------------------------------------------------*/
/*--------------- Tree Map Node ------------------*/
/*------------------------------------------------*/
/*----------------- Clonable ---------------------*/
INTERFACE_METHOD(TreeMapNodeClass, NULL, M_CLONABLE_CLONE);
/*---------------- Comparable --------------------*/
INTERFACE_METHOD(TreeMapNodeClass, NULL, M_COMPARABLE_COMPARE_TO);
/*------------------ Tree Map---------------------*/
/*----------------- Clonable ---------------------*/
INTERFACE_METHOD(TreeMapClass, NULL, M_CLONABLE_CLONE);
/*----------------- Iterable ---------------------*/
INTERFACE_METHOD(TreeMapClass, NULL, M_ITERABLE_CREATE);
/*----------------- Collection -------------------*/
INTERFACE_METHOD(TreeMapClass, false, M_COLLECTION_ADD);
INTERFACE_METHOD(TreeMapClass, false, M_COLLECTION_ADD_ALL);
INTERFACE_METHOD(TreeMapClass, false, M_COLLECTION_ADD_ALL_C_POINTER);
INTERFACE_METHOD(TreeMapClass, ,M_COLLECTION_CLEAR);
INTERFACE_METHOD(TreeMapClass, false, M_COLLECTION_CONTAINS);
INTERFACE_METHOD(TreeMapClass, false, M_COLLECTION_IS_EMPTY);
INTERFACE_METHOD(TreeMapClass, false, M_COLLECTION_REMOVE);
INTERFACE_METHOD(TreeMapClass, false, M_COLLECTION_REMOVE_ALL);
INTERFACE_METHOD(TreeMapClass, false, M_COLLECTION_RETAIN_ALL);
INTERFACE_METHOD(TreeMapClass, -1, M_COLLECTION_SIZE);
INTERFACE_METHOD(TreeMapClass, NULL, M_COLLECTION_TO_ARRAY);
/*--------------- Map interface ------------------*/
INTERFACE_METHOD(TreeMapClass, false, M_MAP_ADD);
INTERFACE_METHOD(TreeMapClass, false, M_MAP_DELETE_BY_VALUE);
INTERFACE_METHOD(TreeMapClass, false, M_MAP_DELETE_BY_KEY);
INTERFACE_METHOD(TreeMapClass, NULL, M_MAP_GET);
INTERFACE_METHOD(TreeMapClass, NULL, M_MAP_GET_VALUE);
INTERFACE_METHOD(TreeMapClass, NULL, M_MAP_GET_VALUES);
INTERFACE_METHOD(TreeMapClass, NULL, M_MAP_FIND_BY_VALUE);
INTERFACE_METHOD(TreeMapClass, NULL, M_MAP_GET_KEY);
INTERFACE_METHOD(TreeMapClass, NULL, M_MAP_GET_KEYS);
/*------------------------------------------------*/
/*------------- OVERWRITTEN METHODS --------------*/
/*------------------------------------------------*/
/*--------------- Tree Map Node ------------------*/
static OVERWRITE_METHOD(TreeMapNode, M_CTOR){
    SUPER_CTOR(self, TreeMapNode);
    ASSERT(self, NULL);
    self->key = va_arg(*app, void*);
    self->key_size = va_arg(*app, size_t);
    self->value = va_arg(*app, void*);
    self->value_size = va_arg(*app, size_t);
    self->left = NULL;
    self->right = NULL;
    self->parent = NULL;
    return self;
}

static OVERWRITE_METHOD(TreeMapNode, M_DTOR){
    SUPER_DTOR(self, TreeMapNode);
    ASSERT(self, NULL);
    OOC_DELETE(self->key);
    OOC_DELETE(self->value);
    return self;
}
/*----------------- Clonable ---------------------*/
static OVERWRITE_METHOD(TreeMapNode, M_CLONABLE_CLONE){
    CAST(self, TreeMapNode);
    ASSERT(self, NULL);
    void* key;
    void* value;
    key = Clonable_safeClone(self->key, self->key_size);
    value = Clonable_safeClone(self->value, self->value_size);
    return TreeMapNodeKeyCValueC(key, self->key_size, value, self->value_size);
}
/*---------------- Comparable --------------------*/
static OVERWRITE_METHOD(TreeMapNode, M_COMPARABLE_COMPARE_TO){
    CAST(self, TreeMapNode);
    CAST(destroyable_other, TreeMapNode);
    ASSERT(self && destroyable_other, -1);
    if(tree_map_compare_values(self, destroyable_other) == 0){
        int result = tree_map_compare_keys(self, destroyable_other);
        OOC_DELETE(destroyable_other);
        return result;
    }
    OOC_DELETE(destroyable_other);
    return -1;
}
/*----------- Tree Map Node Class -----------------*/
static OVERWRITE_METHOD(TreeMapNodeClass, M_CTOR){
    SUPER_CTOR(self, TreeMapNodeClass);
    SELECTOR_LOOP(
        FIRST_INTERFACE_SELECTOR(TreeMapNodeClass, M_CLONABLE_CLONE)
        ADD_INTERFACE_SELECTOR(TreeMapNodeClass, M_COMPARABLE_COMPARE_TO)
    )
}
/*---------------- Tree Map ----------------------*/
static OVERWRITE_METHOD(TreeMap, M_CTOR){
    SUPER_CTOR(self, TreeMap);
    ASSERT(self, NULL);
    self->node_count = 0;
    self->height = 0;
    return self;
}
static OVERWRITE_METHOD(TreeMap, M_DTOR){
    SUPER_DTOR(self, TreeMap);
    ASSERT(self, NULL);
    tree_map_destroy(self->root);
    OOC_NULLIFY(self->root);
    return self;
}
/*----------------- Clonable ---------------------*/
static OVERWRITE_METHOD(TreeMap, M_CLONABLE_CLONE){
    CAST(self, TreeMap);
    ASSERT(self, NULL);
    o_Iterator o_iterator = Iterable_create(self);
    o_TreeMap clone = TreeMap();
    for_iterator(o_iterator){
        Collection_add(clone ,OOC_CLONE(Iterator_currItem(o_iterator)));
    }
    OOC_DELETE(o_iterator);
    return clone;
}
/*----------------- Iterable ---------------------*/
static OVERWRITE_METHOD(TreeMap, M_ITERABLE_CREATE){
    CAST(self, TreeMap);
    ASSERT(self, NULL);
    return TreeMapIterator(self->root);
}
/*----------------- Collection -------------------*/
static OVERWRITE_METHOD(TreeMap, M_COLLECTION_ADD){
    CAST(self, TreeMap);
    CAST(o_element, TreeMapNode);
    ASSERT(self && o_element, NULL);
    if(tree_map_add(self, o_element)){
        self->node_count++;
        self->height = tree_map_height(self->root);
        tree_map_rebalance(self);
        return true;
    }
    return false;
}

static OVERWRITE_METHOD(TreeMap, M_COLLECTION_ADD_ALL){
    CAST(self, TreeMap);
    o_Iterator o_iterator = Iterable_create(_o_collection);
    ASSERT(self && o_iterator, false);
    bool added_any_node = false;
    for(int i = 0; !Iterator_isDone(o_iterator); i++, Iterator_next(o_iterator)){
        o_TreeMapNode _node = Iterator_currItem(o_iterator);
        CAST(node, TreeMapNode);
        ASSERT(node, false);
        if(tree_map_add(self, TreeMapNode_Clonable_clone(node))){
            self->node_count++;
            added_any_node = true;
        }
    }
    OOC_DELETE(o_iterator);
    if(added_any_node){
        self->height = tree_map_height(self->root);
        tree_map_rebalance(self);
        return true;
    }
    return false;
}

static OVERWRITE_METHOD(TreeMap, M_COLLECTION_ADD_ALL_C_POINTER){
    CAST(self, TreeMap);
    ASSERT(self, false);
    bool added_any_node = false;
    for(int i = 0; i < size_of_vector; i++){
        o_TreeMapNode _node = array[i];
        CAST(node, TreeMapNode);
        ASSERT(node, false);
        if(tree_map_add(self, TreeMapNode_Clonable_clone(node))){
            self->node_count++;
            added_any_node = true;
        }
    }
    if(added_any_node){
        self->height = tree_map_height(self->root);
        tree_map_rebalance(self);
        return true;
    }
    return false;
}

static OVERWRITE_METHOD(TreeMap, M_COLLECTION_CLEAR){
    CAST(self, TreeMap);
    ASSERT(self, );
    tree_map_destroy(self->root);
    self->root = NULL;
    self->node_count = 0;
    return;
}

static OVERWRITE_METHOD(TreeMap, M_COLLECTION_CONTAINS){
    CAST(self, TreeMap);
    CAST(o_element, TreeMapNode);
    ASSERT(self && o_element, false);
    o_TreeMapNode node = Map_get(self, Clonable_safeClone(o_element->key, o_element->key_size));
    if(node && (tree_map_compare_values(o_element, node) == 0)){
        OOC_DELETE(o_element);
        return true;
    }
    OOC_DELETE(o_element);
    return false;
}

static OVERWRITE_METHOD(TreeMap, M_COLLECTION_IS_EMPTY){
    CAST(self, TreeMap);
    ASSERT(self, false);
    return self->node_count == 0;
}

static OVERWRITE_METHOD(TreeMap, M_COLLECTION_REMOVE){
    CAST(self, TreeMap);
    CAST(o_element, TreeMapNode);
    ASSERT(self && o_element, false);
    o_TreeMapNode node = Map_get(self, Clonable_safeClone(o_element->key, o_element->key_size));
    if(!node){
        OOC_DELETE(o_element);
        return false;
    }
    if(tree_map_compare_values(node, o_element) == 0){
        tree_map_delete(self, node);
        // The function tree_map_delete already
        // deletes the pointer node, if by chance
        // the o_element is exactly the same object
        // (they have the same pointer) trying to
        // delete it again will corrupt the heap
        // This parts ensures that this doesn't happen
        if(node != o_element){
            OOC_DELETE(o_element);
        }
        return true;
    }
    OOC_DELETE(o_element);
    return false;
}

static OVERWRITE_METHOD(TreeMap, M_COLLECTION_REMOVE_ALL){
    CAST(self, TreeMap);
    ASSERT(self, false);
    o_Iterator o_iterator = Iterable_create(_o_collection);
    bool removed = false;
    for(;!Iterator_isDone(o_iterator); Iterator_next(o_iterator)){
        o_TreeMapNode _node = Iterator_currItem(o_iterator);
        CAST(node, TreeMapNode);
        ASSERT(node, false);
        if(TreeMap_Collection_remove(self, Clonable_clone(node))){
            removed = true;
        }
    }
    OOC_DELETE(o_iterator);
    return removed;
}

static OVERWRITE_METHOD(TreeMap, M_COLLECTION_RETAIN_ALL){
    CAST(self, TreeMap);
    CHECK_INTERFACE(contains, _o_collection, M_COLLECTION_CONTAINS);
    ASSERT(self && contains, false);
    o_TreeMap o_new_map = TreeMap();
    bool added = false;
    o_Iterator o_iterator = Iterable_create(self);
    for(;!Iterator_isDone(o_iterator); Iterator_next(o_iterator)){
        o_TreeMapNode _node = Iterator_currItem(o_iterator);
        CAST(node, TreeMapNode);
        ASSERT(node, false);
        if(contains(_o_collection, Clonable_clone(node))){
            TreeMap_Collection_add(o_new_map, Clonable_clone(node));
            added = true;
        }
    }
    OOC_DELETE(o_iterator);
    if(added){
        TreeMap_Collection_clear(self);
        TreeMap_Collection_addAll(self, o_new_map);
    }
    OOC_DELETE(o_new_map);
    return added;
}

static OVERWRITE_METHOD(TreeMap, M_COLLECTION_SIZE){
    CAST(self, TreeMap);
    ASSERT(self, -1);
    return self->node_count;
}

static OVERWRITE_METHOD(TreeMap, M_COLLECTION_TO_ARRAY){
    CAST(self, TreeMap);
    ASSERT(self, NULL);
    o_Vector o_vector = Vector();
    Collection_addAll(o_vector, self);
    void** array = Collection_toArray(o_vector, new_array_size);
    OOC_DELETE(o_vector);
    return array;
}
/*--------------- Map interface ------------------*/
static OVERWRITE_METHOD(TreeMap, M_MAP_ADD){
    CAST(self, TreeMap);
    ASSERT(self, false);
    o_TreeMapNode node = TreeMapNodeKeyCValueC(key, key_size, _o_value, value_size);
    return TreeMap_Collection_add(self, node);
}

static OVERWRITE_METHOD(TreeMap, M_MAP_DELETE_BY_VALUE){
    CAST(self, TreeMap);
    ASSERT(self, false);
    o_TreeMapNode node = Map_findByValue(self, _o_value);
    if(node){
        tree_map_delete(self, node);
        return true;
    }
    return false;
}

static OVERWRITE_METHOD(TreeMap, M_MAP_DELETE_BY_KEY){
    CAST(self, TreeMap);
    ASSERT(self, false);
    o_TreeMapNode node = Map_get(self, _o_key);
    if(node){
        tree_map_delete(self, node);
        return true;
    }
    return false;
}

static OVERWRITE_METHOD(TreeMap, M_MAP_GET){
    CAST(self, TreeMap);
    ASSERT(self, false);
    TreeMapNode_r* aux_x = self->root;
    while(aux_x != NULL &&  TreeMapNode_compareKey(aux_x, Clonable_safeClone(_o_key, aux_x->key_size)) != 0){
        if( TreeMapNode_compareKey(aux_x, Clonable_safeClone(_o_key, aux_x->key_size)) > 0){
            aux_x = aux_x->left;
        }else{
            aux_x = aux_x->right;
        }
    }
    OOC_DELETE(_o_key);
    return aux_x;
}

static OVERWRITE_METHOD(TreeMap, M_MAP_GET_VALUE){
    CAST(self, TreeMap);
    ASSERT(self, false);
    TreeMapNode_r* aux_x = Map_get(self, _o_key);
    return aux_x ? aux_x->value : NULL;
}


static OVERWRITE_METHOD(TreeMap, M_MAP_GET_VALUES){
    CAST(self, TreeMap);
    ASSERT(self && self->root, NULL);
    o_Vector o_vector = VectorCSize(self->node_count, self->root->value_size);
    o_Iterator o_iterator = Iterable_create(self);
    for(;!Iterator_isDone(o_iterator); Iterator_next(o_iterator)){
        TreeMapNode_r* node = Iterator_currItem(o_iterator);
        ASSERT(node, NULL);
        Collection_add(o_vector, Clonable_safeClone(node->value, node->value_size));
    }
    OOC_DELETE(o_iterator);
    return o_vector;
}

static OVERWRITE_METHOD(TreeMap, M_MAP_FIND_BY_VALUE){
    CAST(self, TreeMap);
    ASSERT(self, NULL);
    o_Iterator o_iterator = Iterable_create(self);
    for(;!Iterator_isDone(o_iterator); Iterator_next(o_iterator)){
        o_TreeMapNode _node = Iterator_currItem(o_iterator);
        CAST(node, TreeMapNode);
        ASSERT(node, NULL);
        if(TreeMapNode_compareValue(node, Clonable_safeClone(_o_value, node->value_size)) == 0){
            OOC_DELETE(o_iterator);
            OOC_DELETE(_o_value);
            return node;
        }
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(_o_value);
    return NULL;
}
static OVERWRITE_METHOD(TreeMap, M_MAP_GET_KEY){
    CAST(self, TreeMap);
    ASSERT(self, NULL);
    TreeMapNode_r* node = Map_findByValue(self, _o_value);
    if(node){
        return node->key;
    }
    return NULL;
}

static OVERWRITE_METHOD(TreeMap, M_MAP_GET_KEYS){
    CAST(self, TreeMap);
    ASSERT(self && self->root, NULL);
    o_Vector o_vector = VectorCSize(self->node_count, self->root->key_size);
    o_Iterator o_iterator = Iterable_create(self);
    for(;!Iterator_isDone(o_iterator); Iterator_next(o_iterator)){
        TreeMapNode_r* node = Iterator_currItem(o_iterator);
        ASSERT(node, NULL);
        Collection_add(o_vector, Clonable_safeClone(node->key, node->key_size));
    }
    OOC_DELETE(o_iterator);
    return o_vector;
}

/*------------ Tree Map Class --------------------*/
static OVERWRITE_METHOD(TreeMapClass, M_CTOR){
    SUPER_CTOR(self, TreeMapClass);
    SELECTOR_LOOP(
        FIRST_INTERFACE_SELECTOR(TreeMapClass, M_CLONABLE_CLONE)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_ITERABLE_CREATE)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_COLLECTION_ADD)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_COLLECTION_ADD_ALL)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_COLLECTION_ADD_ALL_C_POINTER)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_COLLECTION_CLEAR)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_COLLECTION_CONTAINS)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_COLLECTION_IS_EMPTY)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_COLLECTION_REMOVE)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_COLLECTION_REMOVE_ALL)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_COLLECTION_RETAIN_ALL)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_COLLECTION_SIZE)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_COLLECTION_TO_ARRAY)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_MAP_ADD)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_MAP_DELETE_BY_VALUE)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_MAP_DELETE_BY_KEY)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_MAP_GET)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_MAP_GET_VALUE)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_MAP_GET_VALUES)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_MAP_FIND_BY_VALUE)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_MAP_GET_KEY)
        ADD_INTERFACE_SELECTOR(TreeMapClass, M_MAP_GET_KEYS)
    )
}

/*------------------------------------------------*/
/*------- Class descriptor and initializer -------*/
/*------------------------------------------------*/

const void* TreeMapNode_d;
const void* TreeMapNodeClass_d;
const void* TreeMap_d;
const void* TreeMapClass_d;

const void* initTreeMapNode(){
    return ooc_new( TreeMapNodeClassClass(),
            "TreeMapNode",
            ObjectClass(),
            sizeof(TreeMapNode_r),
            LINK_METHOD(TreeMapNode, M_CTOR),
            LINK_METHOD(TreeMapNode, M_DTOR),
            LINK_INTERFACE_METHOD(TreeMapNode, TreeMapNodeClass, M_CLONABLE_CLONE),
            LINK_INTERFACE_METHOD(TreeMapNode, TreeMapNodeClass, M_COMPARABLE_COMPARE_TO),
            0);
}

const void* initTreeMapNodeClass(){
    return ooc_new( ClassClass(),
            "TreeMapNodeClass",
            ClassClass(),
            sizeof(TreeMapNodeClass_r),
            LINK_METHOD(TreeMapNodeClass, M_CTOR),
            0);
}

const void* initTreeMap(){
    return ooc_new( TreeMapClassClass(),
            "TreeMap",
            ObjectClass(),
            sizeof(TreeMap_r),
            LINK_METHOD(TreeMap, M_CTOR),
            LINK_METHOD(TreeMap, M_DTOR),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_CLONABLE_CLONE),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_ITERABLE_CREATE),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_COLLECTION_ADD),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_COLLECTION_ADD_ALL),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_COLLECTION_ADD_ALL_C_POINTER),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_COLLECTION_CLEAR),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_COLLECTION_CONTAINS),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_COLLECTION_IS_EMPTY),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_COLLECTION_REMOVE),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_COLLECTION_REMOVE_ALL),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_COLLECTION_RETAIN_ALL),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_COLLECTION_TO_ARRAY),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_COLLECTION_SIZE),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_MAP_ADD),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_MAP_DELETE_BY_VALUE),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_MAP_DELETE_BY_KEY),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_MAP_GET),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_MAP_GET_VALUE),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_MAP_GET_VALUES),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_MAP_FIND_BY_VALUE),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_MAP_GET_KEY),
            LINK_INTERFACE_METHOD(TreeMap, TreeMapClass, M_MAP_GET_KEYS),
            0);
}

const void* initTreeMapClass(){
    return ooc_new( ClassClass(),
            "TreeMapClass",
            ClassClass(),
            sizeof(TreeMapClass_r),
            LINK_METHOD(TreeMapClass, M_CTOR),
            0);
}

