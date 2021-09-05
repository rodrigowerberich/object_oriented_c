/*
 * tree_map_iterator.c
 *
 *  Created on: 9 de jan de 2019
 *      Author: lua
 */

#include <tree_map_iterator.h>
#include <tree_map_iterator.r>
#include <tree_map_helper_functions.h>
#include <lua_assert.h>

/*------------------------------------------------*/
/*------------- OVERWRITTEN METHODS --------------*/
/*------------------------------------------------*/
static OVERWRITE_METHOD(TreeMapIterator, M_CTOR){
    SUPER_CTOR(self, TreeMapIterator);
    TreeMapNode_r* root_node = va_arg(*app, TreeMapNode_r*);
    self->first_node = tree_map_minimun(root_node);
    self->last_node = tree_map_maximum(root_node);
    self->curr_node = self->first_node;
    return self;
}

static OVERWRITE_METHOD(TreeMapIterator, M_ITERATOR_FIRST){
    CAST(self, TreeMapIterator);
    ASSERT(self, );
    self->curr_node = self->first_node;
}

static OVERWRITE_METHOD(TreeMapIterator, M_ITERATOR_NEXT){
    CAST(self, TreeMapIterator);
    ASSERT(self, );
    if(!self->curr_node){
        return;
    }
    if(self->curr_node != self->last_node){
        if(self->curr_node->right){
            self->curr_node = tree_map_minimun(self->curr_node->right);
        }else{
            TreeMapNode_r* aux = self->curr_node->parent;
            while(tree_map_compare_keys(self->curr_node, aux) > 0){
                aux = aux->parent;
            }
            self->curr_node = aux;
        }
    }else{
        self->curr_node = NULL;
    }
}

static OVERWRITE_METHOD(TreeMapIterator, M_ITERATOR_IS_DONE){
    CAST(self, TreeMapIterator);
    ASSERT(self, false);
    return (self->curr_node == NULL);
}

static OVERWRITE_METHOD(TreeMapIterator, M_ITERATOR_CURR_ITEM){
    CAST(self, TreeMapIterator);
    ASSERT(self, NULL);
    if(self->curr_node){
        return self->curr_node;
    }else{
        return self->last_node;
    }
}

/*------------------------------------------------*/
/*------- Class descriptor and initializer -------*/
/*------------------------------------------------*/
const void* TreeMapIterator_d;

const void* initTreeMapIterator(){
    return ooc_new( IteratorClassClass(),
            "TreeMapIterator",
            ObjectClass(),
            sizeof(TreeMapIterator_r),
            LINK_METHOD(TreeMapIterator, M_CTOR),
            LINK_METHOD(TreeMapIterator, M_ITERATOR_FIRST),
            LINK_METHOD(TreeMapIterator, M_ITERATOR_NEXT),
            LINK_METHOD(TreeMapIterator, M_ITERATOR_IS_DONE),
            LINK_METHOD(TreeMapIterator, M_ITERATOR_CURR_ITEM),
            0);
}

