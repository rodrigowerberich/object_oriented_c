/*
 * o_string.h
 *
 *  Created on: 8 de jan de 2019
 *      Author: lua
 */

#ifndef COMPONENTS_OO_BASE_O_STRING_O_STRING_H_
#define COMPONENTS_OO_BASE_O_STRING_O_STRING_H_

/*
 * vector.h
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */

#include <ooc.h>
#include <comparable_interface.h>
#include <clonable_interface.h>

/*------------------------------------------------*/
/*----------- ClassVar declaration ---------------*/
/*------------------------------------------------*/
CLASS_DECLARATION(String);
CLASS_DECLARATION(StringClass);
/*------------------------------------------------*/
/*------------ Class constructors ----------------*/
/*------------------------------------------------*/
static inline o_String String(const char* value){ return ooc_new(StringClass(), value, 0);}
static inline o_String SizedString(const char* value, size_t string_size){ return ooc_new(StringClass(), value, string_size);}
/*------------------------------------------------*/
/*--------------- Class methods ------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
/*----------- Static linked methods --------------*/
/*------------------------------------------------*/
// ---------  Capacity
int String_size(o_String _self);
bool String_isEmpty(o_String _self);
// Clears the strings content, but doesn't change the capacity
void String_clear(o_String _self);
// --------- Element access
// Returns a pointer to the element at position pos, if position is out of range, returns NULL
char* String_charAt(o_String _self, int index);
// ---------  Modifiers
// Erase the current content and replaces it with the new one
void String_assign(o_String _self, char* new_value);
// Appends the c string to the end of the current string, the c string is NOT deleted
void String_appendC(o_String _self, char* c_string);
// Appends the string to the end of the current string, the other string is deleted
void String_append(o_String _self, o_String _o_other);
// Appends a char to the end of the current string
void String_add(o_String _self, char char_to_add);
// Insert a c string into position index, the size_of_string parameter is used to choose how much of the
// c string is copied. The original content at position index are shifted size_of_string positions to the
// side
void String_insertC(o_String _self, int index, char* c_string, int size_of_string);
// Insert a string into position index, the size_of_string parameter is used to choose how much of the
// string is copied. The original content at position index are shifted size_of_string positions to the
// side
void String_insert(o_String _self, int index, o_String _o_string);
// Erases content from the string starting from index and the amount size_to_erase
void String_erase(o_String _self, int index, int size_to_erase);
// Replaces in the current string starting from index until index+size_to_replace the contents of other,
// the c string is not deleted
void String_replaceC(o_String _self, int index, int size_to_replace, char* c_string);
// Replaces in the current string starting from index until index+size_to_replace the contents of other,
// the string is deleted
void String_replace(o_String _self, int index, int size_to_replace, o_String _o_other);
// Replaces all occurrences of _replace with _replacement. Both are deleted
void String_replaceAll(o_String _self, o_String _replace, o_String _replacement);
// ---------  string operations
// Returns the underlying c string buffer
const char* String_toArray(o_String _self);
// Search the string for _to_search starting from first_pos_to_search, if none is
// found, return the len of the string, the c string is not deleted
int String_findC(o_String _self, char* to_search, int first_pos_to_search);
// Search the string for _to_search starting from first_pos_to_search, if none is
// found, return the len of the string, the to_search string is deleted
int String_find(o_String _self, o_String to_search, int first_pos_to_search);
// Backwards search the string for to_search starting from first_pos_to_search, if none is
// found, return the len of the string, the c string is not deleted
int String_rfindC(o_String _self, char* to_search, int first_pos_to_search);
// Backwards search the string for to_search starting from first_pos_to_search, if none is
// found, return the len of the string, the to_search string is deleted
int String_rfind(o_String _self, o_String to_search, int first_pos_to_search);
// Returns a string that start from position pos with length len,
// if pos < 0 or pos >= self->len returns "", if pos+len surpasses the  original len
// the substring size will be smaller then len
o_String String_subString(o_String _self, int start_index, int size_of_substring);
// Checks if string ends with other, other is deleted
bool String_endsWith(o_String _self, o_String _other);
// Checks if string starts with other, other is deleted
bool String_startsWith(o_String _self, o_String _other);
void String_toLower(o_String _self);
void String_toUpper(o_String _self);
// Removes all trailing and front space, tabs, enters, feeds, etc
void String_trim(o_String _self);
/*------------------------------------------------*/
/*------------- Interface methods ----------------*/
/*------------------------------------------------*/
INTERFACE_METHOD_HEADER(StringClass, M_COMPARABLE_COMPARE_TO);
INTERFACE_METHOD_HEADER(StringClass, M_CLONABLE_CLONE);
#endif /* COMPONENTS_OO_BASE_O_STRING_O_STRING_H_ */
