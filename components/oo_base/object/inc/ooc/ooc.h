/*
 * ooc.h
 *
 *  Created on: 28 de dez de 2018
 *      Author: lua
 */

#ifndef COMPONENTS_OO_BASE_OBJECT_OOC_H_
#define COMPONENTS_OO_BASE_OBJECT_OOC_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <ooc/ooc_macros.h>
/*------------------------------------------------*/
/*---------------- Helper constructs -------------*/
/*------------------------------------------------*/
// Generic type for selector functions
typedef void (*ooc_method_t)();
/*------------------------------------------------*/
/*------------------- Helper methods -------------*/
/*------------------------------------------------*/
// These methods create pointers for c variables from values
// For ease of use, use the C var constructors
void* ooc_new_c_(const char* name, ...);
// Automatically casts and writes the type name
#define ooc_new_c(type_, ...) (type_*) ooc_new_c_( #type_ , __VA_ARGS__)
/* These are the methods that creates and destroys every object */
//  Ex:
//      o_String o_var = ooc_new(StringClass, "String value");
//      ...
//      o_var = ooc_delete(o_var);
// The new method takes in the ClassVar that defines a class and the arguments
// that will be passed on to the class constructor
void* ooc_new(const void* class_descriptor, ...);
// This methods must be called after you are done using the object to free
// the dynamic memory, it can also replace calls to free if the pointer passed is not an object
void* ooc_delete(void * self);
// This is a quick define to delete an array of pointer values
#define ooc_deleteCArrayContent(array_)\
    for( int aux_index = 0; aux_index < (sizeof(array_)/sizeof(array_[0])) ; aux_index++){\
        array_[aux_index] = ooc_delete(array_[aux_index]);\
    }
// Deletes the object inplace
#define OOC_DELETE(_self) (_self) = ooc_delete(_self)
// Just sets the pointer to NULL
#define OOC_NULLIFY(_self) (_self) = NULL 
/*------------------------------------------------*/
/*----------- ClassVar declaration ---------------*/
/*------------------------------------------------*/
// This variable represents the class itself, this will be referred as the ClassVar
CLASS_DECLARATION(Object);
/*------------------------------------------------*/
/*--------- MetaClassVar declaration -------------*/
/*------------------------------------------------*/
// This variable represents the metaclass, this will be referred as the MetaClassVar
// The Metaclass contains the methods that can ne overwritten
CLASS_DECLARATION(Class);
/*------------------------------------------------*/
/*------------ Class constructors ----------------*/
/*------------------------------------------------*/
static inline o_Object Object(){
    return ooc_new(ObjectClass());
}
#define CLASS(class_, name_, super_, size_, selector_) ooc_new(class_, name_, super_, size_, selector_, 0)
/*------------ C var constructors ----------------*/
// These are used to create c types pointers out of values
#define BASE_C_CONSTRUCTOR(type_, value_) ooc_new_c(type_, value_)
#define CHAR(    value_) BASE_C_CONSTRUCTOR(char,     value_)
#define INT(     value_) BASE_C_CONSTRUCTOR(int,      value_)
#define BOOL(    value_) BASE_C_CONSTRUCTOR(bool,      value_)
#define UINT8_T( value_) BASE_C_CONSTRUCTOR(uint8_t,  value_)
#define UINT16_T(value_) BASE_C_CONSTRUCTOR(uint16_t, value_)
#define UINT32_T(value_) BASE_C_CONSTRUCTOR(uint32_t, value_)
#define INT8_T(  value_) BASE_C_CONSTRUCTOR(int8_t,   value_)
#define INT16_T( value_) BASE_C_CONSTRUCTOR(int16_t,  value_)
#define INT32_T( value_) BASE_C_CONSTRUCTOR(int32_t,  value_)
#define SIZE_T(  value_) BASE_C_CONSTRUCTOR(size_t,   value_)
#define FLOAT(   value_) BASE_C_CONSTRUCTOR(float,    value_)
#define DOUBLE(  value_) BASE_C_CONSTRUCTOR(double,   value_)
// Both static and dynamic linked methods works on all subclasses
// of this class. Static linked methods cannot be overwritten, and
// Dynamic linked methods can
/*------------------------------------------------*/
/*--------------- Class methods ------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
/*----------- Static linked methods --------------*/
/*------------------------------------------------*/
// Returns the class structure of the object
const void* ooc_classOf(const void* self);
size_t ooc_sizeOf(const void* self);
// Checks if the object is an instance of the specified class
bool ooc_isA (const void* _self, const void* _class);
// Checks if the object is an instance of any class that subclasses the specified class
bool ooc_isOf (const void* _self, const void* _class);
// If the object passed is not of class specified, it returns NULL
void* ooc_cast (const void* _class, const void* _self);
// Returns the superclass of an object
const void* ooc_super(const void * self);
// A quick helper to check if void* pointer is of an object or not
static inline int ooc_isObject(const void* self){
    return ooc_isOf(self, ObjectClass());
}
ooc_method_t ooc_respondsTo(const void* _self, const char* tag);
/*-------------------------------------------------*/
/*----------- Dynamic linked methods --------------*/
/*-------------------------------------------------*/
/*------------------- Mandatory -------------------*/
// The class constructor
#define M_CTOR_DEF   void*, ooc_ctor
#define M_CTOR_ARG   void* _self, va_list* app
#define M_CTOR_PARAM       _self,          app
DYNAMIC_METHOD_HEADER(M_CTOR);
// The class destructor
#define M_DTOR_DEF   void*, ooc_dtor
#define M_DTOR_ARG   void* _self
#define M_DTOR_PARAM       _self
DYNAMIC_METHOD_HEADER(M_DTOR);
// Compares two objects pointers to see if they are different
// Sometimes the compareTo method of the class will be called
#define M_DIFFER_DEF          int, ooc_differ
#define M_DIFFER_ARG   const void* _self, const void* _other
#define M_DIFFER_PARAM             _self,             _other
DYNAMIC_METHOD_HEADER(M_DIFFER);
//
//// Prints the object to the passed output stream
//#define M_PUTO_DEF    int, ooc_putO
//#define M_PUTO_ARG    const void * _self, FILE* fp
//#define M_PUTO_PARAM               _self,       fp
//DYNAMIC_METHOD_HEADER(M_PUTO);
//// Prints the object to the default output
//static inline int ooc_putObject(const void* self_){
//    return ooc_putO(self_, stdout);
//}

#endif /* COMPONENTS_OO_BASE_OBJECT_OOC_H_ */
