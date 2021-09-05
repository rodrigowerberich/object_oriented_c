/*
 * o_string.c
 *
 *  Created on: 8 de jan de 2019
 *      Author: lua
 */

#include <o_string.h>
#include <o_string.r>

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

#include <lua_assert.h>
#include <lua_malloc.h>

/*------------------------------------------------*/
/*-------------- DEFINE HELPERS ------------------*/
/*------------------------------------------------*/
static const int MIN_BUFFER_SIZE = 5;
static OVERWRITE_METHOD(String, M_CLONABLE_CLONE); // Forward declaration
/*------------------------------------------------*/
/*------------------- Helper methods -------------*/
/*------------------------------------------------*/

static void o_string_expand(String_r* p_string, int new_size) {
    if ( (2 * p_string->buffer_size) > new_size) {
        p_string->buffer_size = 2 * p_string->buffer_size;
    } else {
        p_string->buffer_size = 1.5 * new_size;
    }
    p_string->buffer = (char*) lua_realloc(p_string->buffer, p_string->buffer_size*sizeof(char));
}
static void o_string_add_space(String_r* p_string, int extra_space){
    p_string->str_size += extra_space;
    int new_size = p_string->str_size + 1;
    if (p_string->buffer_size < new_size) {
        o_string_expand(p_string, new_size);
    }
}

/*------------------------------------------------*/
/*--------------- Class methods ------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
/*----------- Static linked methods --------------*/
/*------------------------------------------------*/
// ---------  Capacity
int String_size(o_String _self){
    CAST(self, String);
    ASSERT(self, -1);
    return self->str_size;
}
bool String_isEmpty(o_String _self){
    CAST(self, String);
    ASSERT(self, true);
    return self->str_size == 0;
}
void String_clear(o_String _self) {
    CAST(self, String);
    ASSERT(self, );
    self->buffer[0] = '\0';
    self->str_size = 0;
}
// --------- Element access
char* String_charAt(o_String _self, int index) {
    CAST(self, String);
    ASSERT(self, NULL);
    if( (index < 0) || (index >= self->str_size) ){
        return NULL;
    }
    return self->buffer + index;
}
// ---------  Modifiers
void String_assign(o_String _self, char* new_value) {
    CAST(self, String);
    ASSERT(self, );
    self->str_size = strlen(new_value);
    int new_size = self->str_size + 1;
    if (self->buffer_size < new_size) {
        o_string_expand(self, new_size);
    }
    strcpy(self->buffer, new_value);
}
void String_appendC(o_String _self, char* c_string) {
    CAST(self, String);
    ASSERT(self, );
    size_t old_size = self->str_size;
    size_t other_size = strlen(c_string);
    o_string_add_space(self, other_size);
    memcpy(self->buffer+old_size, c_string, other_size);
    self->buffer[self->str_size] = '\0';
}
void String_append(o_String _self, o_String _o_other) {
    CAST(o_other, String);
    CAST(self, String);
    ASSERT(o_other && self, );
    size_t old_size = self->str_size;
    o_string_add_space(self, o_other->str_size);
    memcpy(self->buffer+old_size, o_other->buffer, o_other->str_size);
    self->buffer[self->str_size] = '\0';
    OOC_DELETE(o_other);
}

void String_add(o_String _self, char char_to_add){
    CAST(self, String);
    ASSERT(self, );
    int old_size = self->str_size;
    o_string_add_space(self, 1);
    self->buffer[old_size] = char_to_add;
    self->buffer[old_size+1] = '\0';
}
void String_insertC(o_String _self, int index, char* c_string, int size_of_string){
    CAST(self, String);
    ASSERT(self, );
    if( (index < 0) || (index > self->str_size) ){
        return;
    }
    int old_size = self->str_size;
    o_string_add_space(self, size_of_string);
    memmove(self->buffer+index+size_of_string, self->buffer+index, old_size-index+1);
    strncpy(self->buffer+index, c_string, size_of_string);
}
void String_insert(o_String _self, int index, o_String _o_string){
    CAST(o_string, String);
    ASSERT(o_string, );
    String_insertC(_self, index, o_string->buffer, o_string->str_size);
    OOC_DELETE(o_string);
}
void String_erase(o_String _self, int index, int size_to_erase){
    CAST(self, String);
    ASSERT(self, );
    if( (index < 0) || (index >= self->str_size) || (size_to_erase < 1)){
        return;
    }
    if( ((index+size_to_erase) >= self->str_size) || ((index+size_to_erase) <= 0) ){
        self->buffer[index] = '\0';
        self->str_size = index;
    }else{
        memmove(self->buffer+index, self->buffer+index+size_to_erase, self->str_size-(index+size_to_erase)+1);
        self->str_size -= size_to_erase;
    }
}
void String_replaceC(o_String self, int index, int size_to_replace, char* c_string){
    String_erase(self, index, size_to_replace);
    String_insertC(self, index, c_string, strlen(c_string));
}
void String_replace(o_String self, int index, int size_to_replace, o_String _o_other){
    CAST(o_other, String);
    ASSERT(o_other, );
    String_replaceC(self, index, size_to_replace, o_other->buffer);
    OOC_DELETE(o_other);
}
void String_replaceAll(o_String _self, o_String _o_replace, o_String _o_replacement){
    CAST(self,String);
    CAST(o_replace, String);
    CAST(o_replacement, String);
    ASSERT(self && o_replace && o_replacement, );
    int position = String_find(self, String_Clonable_clone(o_replace), 0);
    while(position < String_size(self)){
        position = String_find(self, String_Clonable_clone(o_replace), position);
        if(position < String_size(self)){
            String_replace(self, position, String_size(o_replace), String_Clonable_clone(o_replacement));
        }
    }
    OOC_DELETE(o_replace);
    OOC_DELETE(o_replacement);
}
// ---------  string operations
const char* String_toArray(o_String _self) {
    CAST(self, String);
    ASSERT(self, "<NULL>");
    return self->buffer;
}
int String_findC(o_String _self, char* to_search, int first_pos_to_search){
    CAST(self, String);
    ASSERT(self, -1);
    int to_search_size = strlen(to_search);
    if(to_search_size > self->str_size) return self->str_size;
    for(int i = first_pos_to_search; i < (self->str_size - to_search_size) + 1; i++){
        if(strncmp(to_search, self->buffer+i, to_search_size) == 0){
            return i;
        }
    }
    return self->str_size;
}
int String_find(o_String self, o_String _to_search, int first_pos_to_search){
    CAST(to_search, String);
    ASSERT(to_search, -1);
    int result = String_findC(self, to_search->buffer, first_pos_to_search);
    OOC_DELETE(to_search);
    return result;
}
int String_rfindC(o_String _self, char* to_search, int first_pos_to_search){
    CAST(self, String);
    ASSERT(self, -1);
    int to_search_size = strlen(to_search);
    if(to_search_size > self->str_size) return self->str_size;
    if(first_pos_to_search > (self->str_size - to_search_size)){
        first_pos_to_search = (self->str_size - to_search_size);
    }
    for(int i = first_pos_to_search; i > -1; i--){
        if(strncmp(to_search, self->buffer+i, to_search_size) == 0){
            return i;
        }
    }
    return self->str_size;
}
int String_rfind(o_String self, o_String _to_search, int first_pos_to_search){
    CAST(to_search, String);
    ASSERT(to_search, INT_MAX);
    int result = String_rfindC(self, to_search->buffer, first_pos_to_search);
    OOC_DELETE(to_search);
    return result;
}
o_String String_subString(o_String _self, int start_index, int size_of_substring){
    CAST(self, String);
    ASSERT(self, NULL);
    if( (start_index >= self->str_size) || (start_index < 0) ){
        return String("");
    }
    if(size_of_substring > self->str_size){
        size_of_substring = self->str_size-start_index;
    }
    char* temp = strncpy(lua_malloc(size_of_substring+1), self->buffer+start_index, size_of_substring);
    temp[size_of_substring] = '\0';
    o_String substr = SizedString(temp, size_of_substring);
    lua_free(temp);
    return substr;
}
bool String_endsWith(o_String _self, o_String _other){
    CAST(self, String);
    CAST(other, String);
    ASSERT(self && other, false);
    if(self && other){
        if(String_size(self) < String_size(other)){
            OOC_DELETE(other);
            return false;
        }else{
            void* substr = String_subString(self, String_size(self)-String_size(other), String_size(other));
            bool result = !ooc_differ(other, substr);
            OOC_DELETE(other);
            return result;
        }
    }
    return false;
}
bool String_startsWith(o_String _self, o_String _other){
    CAST(self, String);
    CAST(other, String);
    ASSERT(self && other, false);
    if(self && other){
        if(String_size(self) < String_size(other)){
            OOC_DELETE(other);
            return false;
        }else{
            void* substr = String_subString(self, 0, String_size(other));
            bool result = !ooc_differ(other, substr);
            OOC_DELETE(other);
            return result;
        }
    }
    return false;
}
void String_toLower(o_String _self){
    CAST(self, String);
    ASSERT(self, );
    uint8_t* p = (uint8_t*) self->buffer;
    while (*p) {
         *p = tolower((uint8_t)*p);
          p++;
      }
}
void String_toUpper(o_String _self){
    CAST(self, String);
    ASSERT(self, );
    uint8_t* p = (uint8_t*) self->buffer;
    while (*p) {
         *p = toupper((uint8_t)*p);
          p++;
      }
}
void String_trim(o_String _self){
    CAST(self, String);
    ASSERT(self, );
    int start = 0;
    int finish = 0;
    for(int i=0; i < String_size(self); i++){
        if(!isspace((int)self->buffer[i])){
            start = i;
            break;
        }
    }
    String_erase(self, 0, start);
    for(int i=String_size(self)-1; i > -1; i--){
        if(!isspace((int)self->buffer[i])){
            finish = i;
            break;
        }
    }
    String_erase(self, finish+1, INT_MAX);
}
/*-------------------------------------------------*/
/*----------- Dynamic linked methods --------------*/
/*-------------------------------------------------*/
INTERFACE_METHOD(StringClass, -1, M_COMPARABLE_COMPARE_TO);
INTERFACE_METHOD(StringClass, NULL, M_CLONABLE_CLONE);
/*------------------------------------------------*/
/*------------- OVERWRITTEN METHODS --------------*/
/*------------------------------------------------*/
/*------------------- Object -------------------*/
static OVERWRITE_METHOD(String, M_CTOR){
    SUPER_CTOR(self, String);
    char* buffer = va_arg(*app, char*);
    self->str_size = va_arg(*app, size_t);
    if(self->str_size == 0){
        self->str_size = strlen(buffer);
    }
    self->buffer_size = self->str_size + MIN_BUFFER_SIZE;
    self->buffer = lua_malloc(self->buffer_size);
    memcpy(self->buffer, buffer, self->str_size);
    self->buffer[self->str_size] = '\0';
    return self;
}
static OVERWRITE_METHOD(String, M_DTOR){
    SUPER_DTOR(self, String);
    lua_free(self->buffer);
    return self;
}
static OVERWRITE_METHOD(String, M_COMPARABLE_COMPARE_TO){
    CAST(self, String);
    CAST(destroyable_other, String);
    if (!self || !destroyable_other) {
        OOC_DELETE(destroyable_other);
        return INT_MAX;
    }
    int result = strcmp(self->buffer, destroyable_other->buffer);
    OOC_DELETE(destroyable_other);
    return result;
}
static OVERWRITE_METHOD(String, M_CLONABLE_CLONE){
    CAST(self, String);
    ASSERT(self, NULL);
    return SizedString(self->buffer, self->str_size);
}
static OVERWRITE_METHOD(String, M_DIFFER){
    CAST(self, String);
    ASSERT(self, 0);
    return String_Comparable_compareTo(self, (void*)_other);
}
//static OVERWRITE_METHOD(String, M_PUTO){
//    CAST(self, String);
//    ASSERT(self, 0);
//    return fprintf(fp, "\"%s\"\n", self->buffer);
//}
/*------------------- String Class -------------------*/
static OVERWRITE_METHOD(StringClass, M_CTOR){
    SUPER_CTOR(self, StringClass);
    SELECTOR_LOOP(
        FIRST_INTERFACE_SELECTOR(StringClass, M_CLONABLE_CLONE)
        ADD_INTERFACE_SELECTOR(StringClass, M_COMPARABLE_COMPARE_TO)
    )
}
/*-------------------------------*/
/*------- Initialization --------*/
/*-------------------------------*/
const void* String_d;
const void* initString() {
    return CLASS(
                StringClassClass(),
                "String",
                ObjectClass(),
                sizeof(String_r),
                ARG(
                    LINK_METHOD(String, M_CTOR),
                    LINK_METHOD(String, M_DTOR),
                    LINK_METHOD(String, M_DIFFER),
                    LINK_INTERFACE_METHOD(String, StringClass, M_CLONABLE_CLONE),
                    LINK_INTERFACE_METHOD(String, StringClass, M_COMPARABLE_COMPARE_TO)
                )
            );
}

const void* StringClass_d;
const void* initStringClass() {
    return CLASS(
                ClassClass(),
                "String",
                ClassClass(),
                sizeof(StringClass_r),
                ARG(
                    LINK_METHOD(StringClass, M_CTOR)
                )
            );
}

