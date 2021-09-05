#ifndef PRINTABLE_INTERFACE_H__
#define PRINTABLE_INTERFACE_H__

#include <ooc.h>
#include <stdio.h>

/*------------------------------------------------*/
/*----- Interface methods declaration ------------*/
/*------------------------------------------------*/

// This method should print an object string representation
// into the file descriptor passed into it.
// It must return the number of bytes written if succesful, if an error
// occurs it should return a negative value
// Function descriptor for int Printable_printToFile(void* _self, FILE* fp);
#define M_PRINTABLE_PRINT_TO_FILE_DEF int, Printable_printToFile
#define M_PRINTABLE_PRINT_TO_FILE_ARG const void* _self, FILE* fp
#define M_PRINTABLE_PRINT_TO_FILE_PARAM           _self,       fp
INTERFACE_METHOD_DECLARATION(M_PRINTABLE_PRINT_TO_FILE);

//Shortcut for printing an object into the standart output.
static inline int Printable_print(const void* _self){
    return Printable_printToFile(_self, stdout);
}

#endif //PRINTABLE_INTERFACE_H__