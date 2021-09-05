/*
 * oo_base_assert.h
 *
 *  Created on: 11 de dez de 2018
 *      Author: lua
 */

#ifndef OO_CONFIG_ASSERT_H__
#define OO_CONFIG_ASSERT_H__

// Helper define to verify an assertion, is basically an if with the assert negated
#define ASSERTION_(_assertion, ...)\
    if(!(_assertion)){\
        __VA_ARGS__\
    }

// Defines the verbosity level of this file, it can be 0 or 1
// If 1 it will show all the prints
// If 0 no prints will be shown, not even for the notify and error notify
#define ASSERT_VERBOSE 1
// The actual macro definitions depending on verbosity
#if ASSERT_VERBOSE == 1

#define ASSERT_(_assertion, _return_value)\
    ASSERTION_(_assertion,\
        return _return_value;\
    )
#define ERROR_NOTIFY_F_(format_, ...) 
#define NOTIFY_F_(format_, ...)
#define ASSERT_NOTIFY_F_(assertion_, return_value_, format_, ...) ASSERT_(assertion_, return_value_)

// Checks if the condition passed in assertion_ is valid, if not it will return the value passed
// in return_value_
#define ASSERT(assertion_, return_value_) ASSERT_(assertion_, return_value_)
// Prints an error message with the same syntax as printf to the default error handler
#define ERROR_NOTIFY_F(format_, ...) ERROR_NOTIFY_F_(format_, __VA_ARGS__)
// Prints a c string as an error message to the default error handler
#define ERROR_NOTIFY(message_) ERROR_NOTIFY_F("%s", message_)
// Combines a call to ERROR_NOTIFY_F and ASSERT
#define ASSERT_NOTIFY_F(assertion_, return_value_, format_, ...) ASSERT_NOTIFY_F_(assertion_, return_value_, format_, __VA_ARGS__)
// Combines a call to ERROR_NOTIFY and ASSERT
#define ASSERT_NOTIFY(assertion_, return_value_, message_) ASSERT_NOTIFY_F(assertion_, return_value_, "%s", message_)
// Prints an info message with the same syntax as printf to the default output handler
#define NOTIFY_F(format_, ...) NOTIFY_F_(format_, __VA_ARGS__)
// Prints a c string as an info message to the default output handler
#define NOTIFY(message_) NOTIFY_F("%s", message_)
#else
#define ASSERT_(_assertion, _return_value)\
    ASSERTION_(_assertion,\
        return _return_value;\
    )
#define ERROR_NOTIFY_F_(format_, ...) 
#define NOTIFY_F_(format_, ...)
#define ASSERT_NOTIFY_F_(assertion_, return_value_, format_, ...) ASSERT_(assertion_, return_value_)
#endif

#endif /* OO_CONFIG_ASSERT_H__ */
