/*
 * collection_interface.c
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */

#include <collection_interface.h>
#include <stddef.h>

INTERFACE_METHOD_IMPLEMENTATION(false, M_COLLECTION_ADD);
INTERFACE_METHOD_IMPLEMENTATION(false, M_COLLECTION_ADD_ALL);
INTERFACE_METHOD_IMPLEMENTATION(false, M_COLLECTION_ADD_ALL_C);
INTERFACE_METHOD_IMPLEMENTATION(false, M_COLLECTION_ADD_ALL_C_POINTER);
INTERFACE_METHOD_IMPLEMENTATION(, M_COLLECTION_CLEAR);
INTERFACE_METHOD_IMPLEMENTATION(false, M_COLLECTION_CONTAINS);
INTERFACE_METHOD_IMPLEMENTATION(false, M_COLLECTION_IS_EMPTY);
INTERFACE_METHOD_IMPLEMENTATION(false, M_COLLECTION_REMOVE);
INTERFACE_METHOD_IMPLEMENTATION(false, M_COLLECTION_REMOVE_ALL);
INTERFACE_METHOD_IMPLEMENTATION(false, M_COLLECTION_RETAIN_ALL);
INTERFACE_METHOD_IMPLEMENTATION(-1, M_COLLECTION_SIZE);
INTERFACE_METHOD_IMPLEMENTATION(0, M_COLLECTION_ELEMENT_SIZE);
INTERFACE_METHOD_IMPLEMENTATION(NULL, M_COLLECTION_TO_ARRAY);