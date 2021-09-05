/*
 * ooc_macros.h
 *
 *  Created on: 28 de dez de 2018
 *      Author: lua
 */

#ifndef COMPONENTS_OO_BASE_OOC_MACROS_H_
#define COMPONENTS_OO_BASE_OOC_MACROS_H_

/*------------------------------------------------*/
/*------------ FUNCTIONS DESCRIPTORS -------------*/
/*------------------------------------------------*/
// Function descriptors are use to define a function in one single place,
// and be able to reuse this declaration across the program
// The function descriptor is composed of 3 macros and must obey the following rules:
//  - The name must be all caps and start with M_
//  - The name must reflect the function the descriptor describes
//  - The three macros must start with the names of the descriptor
// The three macros are the definition macro, the argument list macro and the parameter list macro
// Ex:
//  For a function descriptor called M_COMPARABLE_COMPARE_TO that describes the function 
//  int Comparable_compareTo(const void* _self, void* _destroyable_other)
//  We have the definition macro that has the return type of the function followed by the
//  function name
//  #define M_COMPARABLE_COMPARE_TO_DEF int, Comparable_compareTo
//  We have the argument list macro which describes the arguments the function takes
//  #define M_COMPARABLE_COMPARE_TO_ARG   const void* _self, void* _destroyable_other
//  And the parameter list which is the M_COMPARABLE_COMPARE_TO_ARG without the types
//  #define M_COMPARABLE_COMPARE_TO_PARAM       _self,       _destroyable_other
/*------------------------------------------------*/
/*---------------- GENERAL MACROS ----------------*/
/*------------------------------------------------*/
// Helper macro to pass multiple arguments to another macro as a single argument
#define ARG(...) __VA_ARGS__
/*------------------------------------------------*/
/*---------------- HELPER MACROS -----------------*/
/*------------------------------------------------*/
// Cast an existing name_ into a variable name with the type of the class specified
// If the object is not of that type, a NULL reference is returned
#define CAST(out, class_) class_##_r* out = ooc_cast(class_##Class(), _ ## out);
// Return true if the object is a subclass of class
#define IS_A(in_, class_) ooc_isA(in_, class_##Class())
// Create a pointer to a function in the new method if the object passed implements an interface of
// the function descriptor passed, if it is not the pointer is a NULL pointer
#define CHECK_INTERFACE__(new_method_, object_, return_value_, name_)\
    name_##_t new_method_ = (name_##_t) ooc_respondsTo(object_, #name_)
#define CHECK_INTERFACE_(new_method_, object_, description_) CHECK_INTERFACE__(new_method_, object_, description_)
#define CHECK_INTERFACE(new_method_, object_, description_) CHECK_INTERFACE_(new_method_, object_, ARG(description_##_##DEF))
/*------------------------------------------------*/
/*------------ CLASS CREATION MACROS -------------*/
/*------------------------------------------------*/
// Creat the type, descriptor pointer, init declaration and auto initializer of the class
#define CLASS_DECLARATION(name_)\
        extern const void* name_##_d;\
        typedef void* o_##name_;\
        const void* init##name_();\
        static inline const void* name_##Class(){\
            if(!name_##_d){\
                name_##_d = init##name_();\
            }\
            return name_##_d;\
        }
/*------------------------------------------------*/
/*-------- CLASS IMPLEMENTATION MACROS -----------*/
/*------------------------------------------------*/
// Creates a function with the signature of the class name plus the function descriptor
// Used to overwrite a dynamic or interface method
#define OVERWRITE_METHOD__(class_, return_, name_, ...)\
return_ class_##_##name_(__VA_ARGS__)
#define OVERWRITE_METHOD_(class_, def_, args_) OVERWRITE_METHOD__(class_, def_, args_)
#define OVERWRITE_METHOD(class_, name_) OVERWRITE_METHOD_(class_, ARG(name_##_DEF), ARG(name_##_ARG))
/*------ CLASS IMPLEMENTATION CTOR MACROS --------*/
// Retrieves a variable of type_ from the variable list passed
#define CTOR_GET_PARAM(type_) va_arg(*app, type_)
// Makes a call to the super constructor
#define SUPER_CTOR(out, class_) class_##_r* out = super_ooc_ctor(class_##Class(), _##out, app)
/*------ CLASS IMPLEMENTATION DTOR MACROS --------*/
// Makes a call to the super destructor
#define SUPER_DTOR(out, class_) class_##_r* out = super_ooc_dtor(class_##Class(), _##out)
/*------------------------------------------------*/
/*---- DYNAMIC METHOD CLASS HEADER CREATION ------*/
/*------------------------------------------------*/
// The DYNAMIC_METHOD_HEADER macro expects a function descriptor as its parameter
#define DYNAMIC_METHOD_HEADER__(return_, name_, ...)\
        return_ name_(__VA_ARGS__);\
        typedef return_ (*name_##_t)(__VA_ARGS__)
#define DYNAMIC_METHOD_HEADER_(x1,x2) DYNAMIC_METHOD_HEADER__(x1,x2)
#define DYNAMIC_METHOD_HEADER(x) DYNAMIC_METHOD_HEADER_(ARG(x ##_DEF), ARG(x ##_ARG))
/*------------------------------------------------*/
/* DYNAMIC METHOD RESTRICTED CLASS HEADER CREATION */
/*------------------------------------------------*/
// Creates the pointer to the dynamic method
#define CLASS_DYNAMIC_METHOD__(return_, name_, ...) struct ooc_method name_
#define CLASS_DYNAMIC_METHOD_(x1,x2) CLASS_DYNAMIC_METHOD__(x1,x2)
#define CLASS_DYNAMIC_METHOD(x) CLASS_DYNAMIC_METHOD_(ARG(x ##_DEF), ARG(x ##_ARG))
// Creates the super method of the dynamic method
#define SUPER_DYNAMIC_METHOD__(return_, name_, ...) return_ super_##name_(const void* _class, __VA_ARGS__)
#define SUPER_DYNAMIC_METHOD_(x1, x2) SUPER_DYNAMIC_METHOD__(x1, x2)
#define SUPER_DYNAMIC_METHOD(x) SUPER_DYNAMIC_METHOD_(ARG(x ##_DEF), ARG(x ##_ARG))
/*------------------------------------------------*/
/*------ DYNAMIC METHOD CLASS IMPLEMENTATION -----*/
/*------------------------------------------------*/
// Create the body for the dynamic method call, should not be called directly
#define DYNAMIC_METHOD_BODY(class_, method_, return_, ...)\
    const class_##_r* class = ooc_cast(class_##Class(), ooc_classOf(_self));\
    ASSERT(class && class->method_.method, return_); \
    method_##_t call = (method_##_t) class->method_.method;\
    return call(__VA_ARGS__);
// Create the function for the dynamic method call, should not be called directly
#define DYNAMIC_METHOD_IMP_(class_, error_return_, return_type_, method_, _arguments, _parameters)\
        return_type_ method_(_arguments){\
            DYNAMIC_METHOD_BODY(class_, method_, error_return_, _parameters)\
        }
#define DYNAMIC_METHOD_IMP(class_, error_return_, def_, parameter_)\
        DYNAMIC_METHOD_IMP__(class_, error_return_, def_, ARG(parameter_))
// Create the body for the dynamic super method call, should not be called directly
#define SUPER_METHOD_BODY(class_, method_, error_return_, ...)\
        const class_##_r* superclass = ooc_cast(class_##Class(), ooc_super(_class));\
        ASSERT(_self && superclass && superclass->method_.method, error_return_);\
        method_##_t call = (method_##_t) superclass->method_.method;\
        return call(__VA_ARGS__);
#define SUPER_METHOD_IMP_(class_, error_return_, return_type_, method_, _arguments, _parameters)\
        return_type_ super_##method_(const void* _class, _arguments){\
            SUPER_METHOD_BODY(class_, method_, error_return_, _parameters)\
        }
// Create the function for the dynamic super method call, should not be called directly
#define SUPER_METHOD_IMP(class_, error_return_, def_, parameter_)\
        SUPER_METHOD_IMP_(class_, error_return_, def_, ARG(parameter_))
// Implements the dynamic method and super class method, this is the one you must call
// Receives the metaclass, the value to return when something wrong occurs and the function descriptor        
#define DYNAMIC_METHOD__(class_, error_return_, def_, arg_,parameters_)\
        DYNAMIC_METHOD_IMP_(class_, error_return_, def_, ARG(arg_), ARG(parameters_))\
        SUPER_METHOD_IMP_(class_, error_return_, def_, ARG(arg_), ARG(parameters_))
#define DYNAMIC_METHOD_(class_, error_return_, def_, args_, parameters_)\
        DYNAMIC_METHOD__(class_, error_return_, ARG(def_), ARG(args_), ARG(parameters_));
#define DYNAMIC_METHOD(class_, error_return_, name_) DYNAMIC_METHOD_(class_, error_return_, ARG(name_##_DEF), ARG(name_##_ARG), ARG(name_##_PARAM))
/*------------------------------------------------*/
/*----- DYNAMIC METHOD METACLASS CONSTRUCTOR -----*/
/*------------------------------------------------*/
// The selector loop must be inside the metaclass contructor
#define SELECTOR_LOOP(body_)\
        ooc_method_t selector;\
        va_list ap;\
        va_copy(ap, *app);\
        while ((selector = va_arg(ap, ooc_method_t))) {\
            const char* tag = va_arg(ap, const char*);\
            ooc_method_t method = va_arg(ap, ooc_method_t);\
            body_\
        }\
        return self;
#define SELECTOR(name_)\
    (selector == (ooc_method_t) name_){\
        if(tag){\
            self->name_.tag = tag;\
            self->name_.selector = selector;\
            self->name_.method = method;\
        }\
    }
// Receives the function descriptor
// Must be called inside the SELECTOR_LOOP macro in the metaclass constructor
// The FIRST_SELECTOR should only be used if it is the first line inside the SELECTOR_LOOP, 
// otherwise use the ADD_SELECTOR
#define FIRST_SELECTOR__(ignore_, name_) if SELECTOR(name_)
#define FIRST_SELECTOR_(expand_) FIRST_SELECTOR__(expand_)
#define FIRST_SELECTOR(def_) FIRST_SELECTOR_(def_##_DEF)
#define ADD_SELECTOR__(ignore_, name_) else if SELECTOR(name_)
#define ADD_SELECTOR_(expand_) ADD_SELECTOR__(expand_)
#define ADD_SELECTOR(def_) ADD_SELECTOR_(def_##_DEF)
/*------------------------------------------------*/
/*------ DYNAMIC METHOD CLASS LINKAGE ------------*/
/*------------------------------------------------*/
// Receives the class and function descriptor
// Must be called in the init`ClassName` inside the ooc_new call
#define LINK_METHOD__(class_, ignore_, name_)  name_, #name_ , class_##_##name_
#define LINK_METHOD_(class_, expand_) LINK_METHOD__(class_, expand_)
#define LINK_METHOD(class_, def_) LINK_METHOD_(class_, def_##_DEF)
// Receives the function descriptor and the function name to link
// Used when we want to link a method when we didn't overwrite it
// Must be called in the init`ClassName` inside the ooc_new call
#define LINK_METHOD_TO_OTHER__(ignore_, name_, other_) name_, #name_ , other_
#define LINK_METHOD_TO_OTHER_(def_, other_)  LINK_METHOD_TO_OTHER__(def_, other_)
#define LINK_METHOD_TO_OTHER(def_, other_)   LINK_METHOD_TO_OTHER_(def_##_DEF, other_)
/*------------------------------------------------*/
/*------- INTERFACE CREATION MACROS --------------*/
/*------------------------------------------------*/
// The INTERFACE_METHOD_DECLARATION macro expects a function descriptor as its parameter
#define INTERFACE_METHOD_DECLARATION__(return_, name_, ...)\
        return_ name_(__VA_ARGS__);\
        typedef return_ (*name_##_t)(__VA_ARGS__)
#define INTERFACE_METHOD_DECLARATION_(x1,x2) INTERFACE_METHOD_DECLARATION__(x1,x2)
#define INTERFACE_METHOD_DECLARATION(x) INTERFACE_METHOD_DECLARATION_(ARG(x ##_DEF), ARG(x ##_ARG))
/*------------------------------------------------*/
/*---- INTERFACE IMPLEMENTATION MACROS -----------*/
/*------------------------------------------------*/
// The INTERFACE_METHOD_IMPLEMENTATION expect a default error value to return if something goes wrong and the function descriptor
#define INTERFACE_METHOD_IMPLEMENTATION__(return_value_, return_, name_, arguments_, ...)\
        return_ name_(arguments_){\
            name_##_t method = (name_##_t) ooc_respondsTo(_self, #name_);\
            if(!method){\
                return return_value_;\
            }\
            return method(__VA_ARGS__);\
        }
#define INTERFACE_METHOD_IMPLEMENTATION_(return_value_, x1, x2, x3) INTERFACE_METHOD_IMPLEMENTATION__(return_value_, x1, ARG(x2), x3)
#define INTERFACE_METHOD_IMPLEMENTATION(return_value_, x) INTERFACE_METHOD_IMPLEMENTATION_(return_value_, ARG(x ##_DEF), ARG(x ##_ARG), ARG(x ##_PARAM))
/*------------------------------------------------*/
/*---- INTERFACE CLASS HEADER INCLUSION ----------*/
/*------------------------------------------------*/
// The INTERFACE_METHOD_HEADER expects the metaclass of the class and the function descriptor
#define INTERFACE_METHOD_HEADER__(class_, return_, name_, ...)\
    return_ class_##_##name_(__VA_ARGS__)
#define INTERFACE_METHOD_HEADER_(class_, x1,x2) INTERFACE_METHOD_HEADER__(class_, x1,x2)
#define INTERFACE_METHOD_HEADER(class_, x) INTERFACE_METHOD_HEADER_(class_, ARG(x ##_DEF), ARG(x ##_ARG))
/*------------------------------------------------*/
/*-- INTERFACE CLASS RESTRICTED HEADER INCLUSION -*/
/*------------------------------------------------*/
// Creates the pointer to the interface method
#define CLASS_INTERFACE_METHOD__(class_, return_, name_, ...)\
    struct ooc_method class_##_##name_
#define CLASS_INTERFACE_METHOD_(class_, x1,x2) CLASS_INTERFACE_METHOD__(class_, x1,x2)
#define CLASS_INTERFACE_METHOD(class_, x) CLASS_INTERFACE_METHOD_(class_, ARG(x ##_DEF), ARG(x ##_ARG))
// Creates the super method of the interface
#define SUPER_INTERFACE_METHOD__(class_, return_, name_, ...)\
    return_ super_##class_##_##name_(const void* _class, __VA_ARGS__)
#define SUPER_INTERFACE_METHOD_(class_, x1,x2) SUPER_INTERFACE_METHOD__(class_, x1,x2)
#define SUPER_INTERFACE_METHOD(class_, x) SUPER_INTERFACE_METHOD_(class_, ARG(x ##_DEF), ARG(x ##_ARG))
/*------------------------------------------------*/
/*------ INTERFACE CLASS IMPLEMENTATION ----------*/
/*------------------------------------------------*/
// Create the body for the interface method call, should not be called directly
#define INTERFACE_METHOD_BODY(metaclass_, method_, return_, ...)\
    const metaclass_##_r* class = ooc_cast(metaclass_##Class(), ooc_classOf(_self));\
    ASSERT(class && class->metaclass_##_##method_.method, return_); \
    method_##_t call = (method_##_t) class->metaclass_##_##method_.method;\
    return call(__VA_ARGS__);
// Create the function for the interface method call, should not be called directly
#define INTERFACE_METHOD_IMP_(metaclass_, error_return_, return_type_, method_, _arguments, _parameters)\
        return_type_ metaclass_##_##method_(_arguments){\
            INTERFACE_METHOD_BODY(metaclass_, method_, error_return_, _parameters)\
        }
#define INTERFACE_METHOD_IMP(metaclass_, error_return_, def_, parameter_)\
        INTERFACE_METHOD_IMP__(metaclass_, error_return_, def_, ARG(parameter_))
// Create the body for the interface super method call, should not be called directly
#define SUPER_INTERFACE_BODY(metaclass_, method_, error_return_, ...)\
        const metaclass_##_r* superclass = ooc_cast(metaclass_##Class(), ooc_super(_class));\
        ASSERT(_self && superclass && superclass->metaclass_##_##method_.method, error_return_);\
        method_##_t call = (method_##_t) superclass->metaclass_##_##method_.method;\
        return call(__VA_ARGS__);
// Create the function for the interface super method call, should not be called directly
#define SUPER_INTERFACE_IMP_(metaclass_, error_return_, return_type_, method_, _arguments, _parameters)\
        return_type_ super_##metaclass_##_##method_(const void* _class, _arguments){\
            SUPER_INTERFACE_BODY(metaclass_, method_, error_return_, _parameters)\
        }
#define SUPER_INTERFACE_IMP(metaclass_, error_return_, def_, parameter_)\
        SUPER_INTERFACE_IMP_(metaclass_, error_return_, def_, ARG(parameter_))
// Implements the interface method and super class method, this is the one you must call
// Receives the metaclass, the value to return when something wrong occurs and the function descriptor
#define INTERFACE_METHOD__(metaclass_, error_return_, def_, arg_,parameters_)\
        INTERFACE_METHOD_IMP_(metaclass_, error_return_, def_, ARG(arg_), ARG(parameters_))\
        SUPER_INTERFACE_IMP_(metaclass_, error_return_, def_, ARG(arg_), ARG(parameters_))
#define INTERFACE_METHOD_(metaclass_, error_return_, def_, args_, parameters_)\
        INTERFACE_METHOD__(metaclass_, error_return_, ARG(def_), ARG(args_), ARG(parameters_));
#define INTERFACE_METHOD(metaclass_, error_return_, name_) INTERFACE_METHOD_(metaclass_, error_return_, ARG(name_##_DEF), ARG(name_##_ARG), ARG(name_##_PARAM))
/*------------------------------------------------*/
/*------ INTERFACE METACLASS CONSTRUCTOR ---------*/
/*------------------------------------------------*/
// Receives the metaclass and the function descriptor
// Must be called inside the SELECTOR_LOOP macro in the metaclass constructor
// The FIRST_INTERFACE_SELECTOR should only be used if it is the first line inside the SELECTOR_LOOP, 
// otherwise use the ADD_INTERFACE_SELECTOR
#define FIRST_INTERFACE_SELECTOR__(metaclass_, ignore_, name_) if SELECTOR(metaclass_##_##name_)
#define FIRST_INTERFACE_SELECTOR_(metaclass_, expand_) FIRST_INTERFACE_SELECTOR__(metaclass_, expand_)
#define FIRST_INTERFACE_SELECTOR(metaclass_, def_) FIRST_INTERFACE_SELECTOR_(metaclass_, def_##_DEF)
#define ADD_INTERFACE_SELECTOR__(metaclass_, ignore_, name_) else if SELECTOR(metaclass_##_##name_)
#define ADD_INTERFACE_SELECTOR_(metaclass_, expand_) ADD_INTERFACE_SELECTOR__(metaclass_, expand_)
#define ADD_INTERFACE_SELECTOR(metaclass_, def_) ADD_INTERFACE_SELECTOR_(metaclass_, def_##_DEF)
/*------------------------------------------------*/
/*---------- INTERFACE CLASS LINKAGE -------------*/
/*------------------------------------------------*/
// Receives the class, metaclass and function descriptor
// Must be called in the init`ClassName` inside the ooc_new call
#define LINK_INTERFACE_METHOD__(class_, metaclass_, ignore_, name_)  metaclass_##_##name_, #name_ , class_##_##name_
#define LINK_INTERFACE_METHOD_(class_, metaclass_, expand_) LINK_INTERFACE_METHOD__(class_, metaclass_, expand_)
#define LINK_INTERFACE_METHOD(class_, metaclass_, def_) LINK_INTERFACE_METHOD_(class_, metaclass_, def_##_DEF)

#endif /* COMPONENTS_OO_BASE_OOC_MACROS_H_ */

