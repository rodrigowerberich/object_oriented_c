#ifndef O_STRING_EXTRA_H__
#define O_STRING_EXTRA_H__

#include <o_string.h>
#include <vector.h>

// Returns a vector with the string separate by the token, the parts
// do not contain the token and the token string is deleted in the end
o_Vector String_split(o_String _self, o_String o_separation_token);
// Appends multiple strings to the string
// String_appendM(o_string, String("Ola"), "");
o_String String_appendM_(o_String _self, ...);
#define String_appendM(self_, ...) String_appendM_(self_, __VA_ARGS__, NULL)

#endif //O_STRING_EXTRA_H__