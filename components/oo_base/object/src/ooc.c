/*
 * ooc.c
 *
 *  Created on: 28 de dez de 2018
 *      Author: lua
 */


#include <ooc/ooc.h>
#include <ooc/object/ooc.r>
#include <ooc/malloc.h>
#include <ooc/assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>


/*------------------------------------------------*/
/*-------------- DEFINE HELPERS ------------------*/
/*------------------------------------------------*/
// The magic number to identify an object
#define MAGIC 0x0effaced
// Used only in the ooc_v_new_c to check the
// type and create an appropriate variable
#define TYPE_DECODER_BASE(type_, ap_type_)\
    if(strcmp(name, #type_) == 0){\
        type_* v_aux = ooc_malloc(sizeof(type_));\
        *v_aux = va_arg(*app, ap_type_);\
        return v_aux;\
    }
#define TYPE_DECODER(type_) TYPE_DECODER_BASE(type_, type_)
/*------------------------------------------------*/
/*------------------- Helper methods -------------*/
/*------------------------------------------------*/
// Check if the pointer passed is a valid object
static inline bool ooc_is_not_object(const Object_r* self){
    return (!self || (self->magic != MAGIC));
}
// Helper function to create a pointer to an specified value
// Shouldn't be called directly, instead you should use the macros INT, CHAR, BOOL, etc
static void* ooc_v_new_c(const char* name, va_list* app){
    TYPE_DECODER_BASE(char, int);
    TYPE_DECODER(int);
    TYPE_DECODER_BASE(_Bool, int);
    TYPE_DECODER_BASE(uint8_t, int);
    TYPE_DECODER_BASE(uint16_t, int);
    TYPE_DECODER(uint32_t);
    TYPE_DECODER_BASE(int8_t, int);
    TYPE_DECODER_BASE(int16_t, int);
    TYPE_DECODER(int32_t);
    TYPE_DECODER(size_t);
    TYPE_DECODER_BASE(float, double);
    TYPE_DECODER(double);
    return NULL;
}
// Just transforms the variadic list to the va_list and calls the apropriate function
void* ooc_new_c_(const char* name, ...){
    va_list ap;
    va_start(ap, name);
    void* return_value = ooc_v_new_c(name, &ap);
    va_end(ap);
    return return_value;
}
// Handles the creation of objects, calling their constructors
void* ooc_new(const void* class_descriptor, ...) {
    const Class_r* class = ooc_cast(Class_d, class_descriptor);
    ASSERT(class, NULL);
    Object_r* object;
    va_list ap;
    ASSERT(class && class->size, NULL);
    object = ooc_calloc(1, class->size);
    ASSERT(object, NULL);
    object->magic = MAGIC;
    object->class = class;
    va_start(ap, class_descriptor);
    object = ooc_ctor(object, &ap);
    va_end(ap);
    return object;
}
// Handles the destruction of an object or normal pointer
void* ooc_delete(void* self) {
    if (self) {
        if(ooc_is_not_object(self)){
            ooc_free(self);
        }else{
            void* value = ooc_dtor(self);
            ((Object_r*)value)->magic = 0;
            ooc_free(value);
        }
    }
    return NULL;
}
/*------------------------------------------------*/
/*--------------- Class methods ------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
/*----------- Static linked methods --------------*/
/*------------------------------------------------*/
const void* ooc_classOf(const void* _self){
    const Object_r* self = _self;
    ASSERT(!ooc_is_not_object(self), NULL);
    return self->class;
}
size_t ooc_sizeOf(const void* _self){
    const Class_r* class = ooc_classOf(_self);
    ASSERT(class, 0)
    return class->size;
}
bool ooc_isA(const void* self, const void* class){
    if(ooc_is_not_object(self)){
        return false;
    }
    return (self && (ooc_classOf(self) == class));
}
bool ooc_isOf(const void* self, const void* class){
    if(self){
        if(ooc_is_not_object(self)){
            return false;
        }
        const Class_r* my_class = ooc_classOf(self);
        ASSERT(my_class, false);
        if(class != Object_d){
            while( my_class != class){
                if(my_class != Object_d){
                    my_class = ooc_super(my_class);
                }else{
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
void* ooc_cast(const void* class, const void* self){
    ASSERT(ooc_isOf(self, class), NULL);
    return (void*) self;

}
const void* ooc_super(const void* self){
    const Class_r* class = ooc_cast(Class_d, self);
    ASSERT(class && class->super, NULL);
    return class->super;
}

ooc_method_t ooc_respondsTo(const void* _self, const char* tag){
    if(!ooc_is_not_object(_self) && tag && *tag){
        const Class_r* class = ooc_classOf(_self);
        ASSERT(class, NULL);
        const struct ooc_method* p = &class->ooc_ctor;
        int nmeth = (ooc_sizeOf(class) - offsetof(Class_r, ooc_ctor))/sizeof(struct ooc_method);
        do{
            if( p->tag && strcmp(p->tag,tag) == 0){
                return p->method? p->selector: NULL;
            }
        }while(++p, --nmeth);
    }
    return NULL;
}
/*-------------------------------------------------*/
/*----------- Dynamic linked methods --------------*/
/*-------------------------------------------------*/
DYNAMIC_METHOD(Class, NULL, M_CTOR);
DYNAMIC_METHOD(Class, NULL, M_DTOR);
DYNAMIC_METHOD(Class, -1,   M_DIFFER);
/*------------------------------------------------*/
/*------------- OVERWRITTEN METHODS --------------*/
/*------------------------------------------------*/
/*-------------------- Object --------------------*/
static OVERWRITE_METHOD(Object, M_CTOR){
    return _self;
}
static OVERWRITE_METHOD(Object, M_DTOR){
    return _self;
}
// Simple pointer comparison to check if they are the same
static OVERWRITE_METHOD(Object, M_DIFFER){
    return _self != _other;
}
#if 0
static OVERWRITE_METHOD(Object, M_PUTO){
   const Class_r* class = ooc_classOf(_self);
   ASSERT(class, 0);
   return fprintf(fp, "%s at %p\n", class->name, class);
}
#endif 
/*------------------- Class -------------------*/
static OVERWRITE_METHOD(Class, M_CTOR){
    Class_r* self = _self;
    const size_t offset = offsetof(struct Class_r, ooc_ctor);
    self->name = va_arg(*app, char*);
    self->super = va_arg(*app, Class_r*);
    self->size = va_arg(*app, size_t);
    ASSERT(self->super, NULL);
    memcpy((char*) self + offset, (char*) self->super + offset, ooc_sizeOf(self->super) - offset);
    SELECTOR_LOOP(
            FIRST_SELECTOR(M_CTOR)
            ADD_SELECTOR(M_DTOR)
            ADD_SELECTOR(M_DIFFER)
    )
}

static OVERWRITE_METHOD(Class, M_DTOR){
    Class_r* self = _self;
    printf("%s: cannot destroy class\n", self->name);
    return NULL;
}
/*------------------------------------------------*/
/*------- Class descriptor and initializer -------*/
/*------------------------------------------------*/
static const Class_r object[] = {
        {
                {
                        MAGIC,
                        object + 1
                },
                "Object",
                object,
                sizeof(Object_r),
                {"", (ooc_method_t) NULL, (ooc_method_t)Object_ooc_ctor},
                {"", (ooc_method_t) NULL, (ooc_method_t)Object_ooc_dtor},
                {"ooc_differ", (ooc_method_t) ooc_differ, (ooc_method_t)Object_ooc_differ}
        },
        {
                {
                        MAGIC,
                        object + 1
                },
                "Class",
                object,
                sizeof(Class_r),
                {"", (ooc_method_t) NULL, (ooc_method_t)Class_ooc_ctor},
                {"", (ooc_method_t) NULL, (ooc_method_t)Class_ooc_dtor},
                {"ooc_differ", (ooc_method_t) ooc_differ, (ooc_method_t)Object_ooc_differ}
        }
};
const void * Object_d = object;
const void * Class_d = object + 1;

const void* initClass(){
    return Class_d;
}
const void* initObject(){
    return Object_d;
}
