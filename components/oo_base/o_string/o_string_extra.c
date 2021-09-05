/*
 * string_splitter.c
 *
 *  Created on: 8 de jan de 2019
 *      Author: lua
 */
#include <o_string_extra.h>
#include <clonable_interface.h>
#include <o_string.r>

o_Vector String_split(o_String o_string, o_String o_separation_token){
    CHECK_INTERFACE(clone, o_separation_token, M_CLONABLE_CLONE);
    o_Vector o_vector = Vector();
    int start_position = 0;
    int end_position = String_find(o_string, clone(o_separation_token), 0);
    while(start_position < String_size(o_string)){
        o_String o_part = String_subString(o_string, start_position, end_position-start_position);
        start_position = end_position+String_size(o_separation_token);
        Collection_add(o_vector, o_part);
        end_position = String_find(o_string, clone(o_separation_token), start_position);
    }
    OOC_DELETE(o_separation_token);
    return o_vector;
}

o_String String_appendM_(o_String _self, ...){
    va_list ap;
    va_start(ap, _self);
    o_Vector o_strings = Vector();
    o_String o_string = va_arg(ap, o_String);
    while(o_string != NULL){
        if(IS_A(o_string, String)){
            Collection_add(o_strings, o_string);
        }else{
            Collection_add(o_strings, String(o_string));
        }
        o_string = va_arg(ap, o_String);
    }
    CAST(self, String);
    if(!self){
        OOC_DELETE(o_strings);
        return NULL;
    }
    o_Iterator o_iterator = Iterable_create(o_strings);
    for_iterator(o_iterator){
        o_string = Iterator_currItem(o_iterator);
        String_append(self, OOC_CLONE(o_string));
    }
    OOC_DELETE(o_iterator);
    OOC_DELETE(o_strings);
    return self;
}