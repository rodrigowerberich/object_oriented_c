/*
 * vector_test.c
 *
 *  Created on: 7 de jan de 2019
 *      Author: lua
 */

#include <o_string_test.h>
#include <vector.h>
#include <vector_iterator.h>
#include <clonable_interface.h>
#include <lua_assert.h>
#include <string.h>
#include <o_string.h>
#include <o_string_extra.h>
#include <test_suite.h>
#include <limits.h>

static char* test_string1  = "/Primeiro/Segundo/Terceiro";
static char* test_string2  = "Banana";
static char* test_string3  = "Nada";
static char* test_string4  = "";
static char* test_string5  = "Legumes";
static char* test_string6  = " sao bons!";
static char* test_string7  = "Legumes sao bons!";
static char* test_string8  = " sao ruins!";
static char* test_string9  = "Legumes sao ruins!";
static char* test_string10 = "Nah!";
static char* test_string11 = "abcd";
static char* test_string12 = "Algo novo e bonito";
static char* test_string13 = "Algo  e bonito";
static char* test_string14 = "velho";
static char* test_string15 = "Algo velho e bonito";
static char* test_string16 = "Nome da coisa.exe";
static char* test_string17 = ".exe";
static char* test_string18 = ".banana";
static char* test_string19 = "e";


UNIT_TEST(o_string_test_clears);
static bool o_string_test_clears(){
    o_String o_string1 = String(test_string1);
    ASSERT(String_size(o_string1) == strlen(test_string1), false);
    char buffer[30];
    sprintf(buffer, "%s", String_toArray(o_string1));
    ASSERT(strcmp(buffer, test_string1) == 0, false);
    ASSERT(Comparable_compareTo(o_string1, String(test_string1)) == 0, false);
    String_clear(o_string1);
    int size1 = String_size(o_string1);
    ASSERT(size1 == 0, false);
    String_assign(o_string1, test_string2);
    ASSERT(String_size(o_string1) == strlen(test_string2) &&
            Comparable_compareTo(o_string1, String(test_string2)) == 0, false);
    OOC_DELETE(o_string1);
    return true;
}

UNIT_TEST(o_string_test_charAt);
static bool o_string_test_charAt(){
    o_String string1 = String(test_string3);
    for(int i=0; i < String_size(string1); i++){
        ASSERT( String_charAt(string1,i) && (*String_charAt(string1,i)) == test_string3[i], false)
    }
    ASSERT(String_charAt(string1,-3) == NULL && String_charAt(string1,4) == NULL, false);
    OOC_DELETE(string1);
    return true;
}

UNIT_TEST(o_string_test_assign_append_erase);
static bool o_string_test_assign_append_erase(){
    o_String o_string1 = String(test_string4);
    String_assign(o_string1, test_string5);
    ASSERT(Comparable_compareTo(o_string1, String(test_string5)) == 0, 0);
    String_appendC(o_string1, test_string6);
    ASSERT(Comparable_compareTo(o_string1, String(test_string7)) == 0, 0);
    String_erase(o_string1, 7, INT_MAX);
    ASSERT(Comparable_compareTo(o_string1, String(test_string5)) == 0, 0);
    String_append(o_string1, String(test_string8));
    ASSERT(ooc_differ(o_string1, String(test_string9)) == 0, 0);
    String_assign(o_string1, test_string10);
    ASSERT(ooc_differ(o_string1, String(test_string10)) == 0, 0);
    OOC_DELETE(o_string1);
    return true;
}

UNIT_TEST(o_string_test_add);
static bool o_string_test_add(){
    o_String string1 = String(test_string4);
    String_add(string1, 'a');
    String_add(string1, 'b');
    String_add(string1, 'c');
    String_add(string1, 'd');
    ASSERT(!ooc_differ(string1, String(test_string11)), 0);
    OOC_DELETE(string1);
    return true;
}

UNIT_TEST(o_string_test_insert_erase);
static bool o_string_test_insert_erase(){
    o_String string1 = String(test_string4);
    char insertion[] = "Algo novo e bonito";
    String_insertC(string1, 0, insertion, strlen(insertion));
    ASSERT(!ooc_differ(string1, String(test_string12)), 0);
    String_erase(string1, 5, 4);
    ASSERT(!ooc_differ(string1, String(test_string13)), 0);
    String_insert(string1, 5, String(test_string14));
    ASSERT(!ooc_differ(string1, String(test_string15)), 0);
    String_erase(string1, 0, INT_MAX);
    ASSERT(!ooc_differ(string1, String(test_string4)), 0);
    OOC_DELETE(string1);
    return true;
}

UNIT_TEST(o_string_test_ends_with);
static bool o_string_test_ends_with(){
    o_String o_string = String(test_string16);
    int result = String_endsWith(o_string, String(test_string17));
    ASSERT(result, 0);
    result = String_endsWith(o_string, String(test_string18));
    ASSERT(!result, 0);
    o_String o_string1 = String(test_string19);
    result = String_endsWith(o_string, Clonable_clone(o_string1));
    ASSERT(result,0);
    OOC_DELETE(o_string);
    OOC_DELETE(o_string1);
    return true;
}

UNIT_TEST(o_string_test_starts_with);
static bool o_string_test_starts_with(){
    o_String string = String("Nome da coisa.exe");
    int result = String_startsWith(string, String("Nome da"));
    ASSERT(result, 0);
    result = String_startsWith(string, String("Cachorro"));
    ASSERT(!result, 0);
    o_String string1 = String("No");
    result = String_startsWith(string, Clonable_clone(string1));
    ASSERT(result,0);
    OOC_DELETE(string);
    OOC_DELETE(string1);
    return true;
}

UNIT_TEST(o_string_test_to_lower);
static bool o_string_test_to_lower(){
    o_String string1 = String("NoMe MALuco");
    o_String string2 = String("nome maluco");
    String_toLower(string1);
    ASSERT(!ooc_differ(string1, string2),0);
    OOC_DELETE(string1);
    return true;
}

UNIT_TEST(o_string_test_trim);
static bool o_string_test_trim(){
    o_String string1 = String("         Nome real     \n\t\r");
    String_trim(string1);
    ASSERT(!ooc_differ(string1, String("Nome real")),0);
    OOC_DELETE(string1);
    return true;
}

UNIT_TEST(o_string_test_replace_all);
static bool o_string_test_replace_all(){
    o_String string1 = String("Cheia de a e a e a e a, amor e pagode");
    o_String string2 = String("Chei@ de @ e @ e @ e @, @mor e p@gode");
    String_replaceAll(string1, String("a"), String("@"));
    ASSERT(!ooc_differ(string1, string2),0);
    OOC_DELETE(string1);
    string1 = String("A palavra e uma palavra que nao e apenas uma palavra, mas duas palavras");
    string2 = String("A cachorro e uma cachorro que nao e apenas uma cachorro, mas duas cachorros");
    String_replaceAll(string1, String("palavra"), String("cachorro"));
    ASSERT(!ooc_differ(string1, string2),0);
    OOC_DELETE(string1);
    return true;
}
UNIT_TEST(o_string_test_split);
static bool o_string_test_split(){
    o_String string1 = String("Primeiro/Segundo/Terceiro");
    o_String string2 = String("Primeiro");
    o_String string3 = String("Segundo");
    o_String string4 = String("Terceiro");
    o_Vector parts = String_split(string1, String("/"));
    ASSERT(Collection_size(parts) ==  3, 0);
    ASSERT(!ooc_differ(List_get(parts,0), Clonable_clone(string2)),0);
    ASSERT(!ooc_differ(List_get(parts,1), Clonable_clone(string3)),0);
    ASSERT(!ooc_differ(List_get(parts,2), Clonable_clone(string4)),0);
    OOC_DELETE(string1);
    OOC_DELETE(parts);
    string1 = String("Primeiro/Separador/Segundo/Separador/Terceiro");
    parts = String_split(string1, String("/Separador/"));
    ASSERT(Collection_size(parts) ==  3, 0);
    ASSERT(!ooc_differ(List_get(parts,0), string2),0);
    ASSERT(!ooc_differ(List_get(parts,1), string3),0);
    ASSERT(!ooc_differ(List_get(parts,2), string4),0);
    OOC_DELETE(string1);
    OOC_DELETE(parts);
    return true;
}
UNIT_TEST(o_string_find_replace);
static bool o_string_find_replace(){
    o_String string1 = String("Ola sou seu melhor amigo e melhor parceiro");
    int found = String_findC(string1, "pior", 0);
    ASSERT(found == String_size(string1), 0);
    found = String_findC(string1, "melhor", 0);
    ASSERT(found == 12, 0);
    found = String_findC(string1, "melhor", found+1);
    ASSERT(found == 27, 0);
    String_replaceC(string1, found, strlen("melhor"), "pior");
    ASSERT(!ooc_differ(string1, String("Ola sou seu melhor amigo e pior parceiro")), 0);
    found = String_find(string1, String("melhores"), 0);
    ASSERT(found == String_size(string1), 0);
    found = String_find(string1, String("melhor"), 0);
    ASSERT(found == 12, 0);
    String_replace(string1, found, strlen("melhor"), String("pior"));
    ASSERT(!ooc_differ(string1, String("Ola sou seu pior amigo e pior parceiro")), 0);
    found = String_find(string1, String("pior"), found+1);
    ASSERT(found == 25, 0);
    found = String_rfind(string1, String("pior"), INT_MAX);
    ASSERT(found == 25, 0);
    found = String_rfind(string1, String("pior"), found-1);
    ASSERT(found == 12, 0);
    found = String_rfind(string1, String("melhor"), INT_MAX);
    ASSERT(found == String_size(string1), 0);
    found = String_rfindC(string1, "pior", INT_MAX);
    ASSERT(found == 25, 0);
    found = String_rfindC(string1, "pior", found-1);
    ASSERT(found == 12, 0);
    found = String_rfindC(string1, "melhor", INT_MAX);
    ASSERT(found == String_size(string1), 0);
    OOC_DELETE(string1);
    return true;
}

UNIT_TEST(o_string_test_iterators_and_chars);
static bool o_string_test_iterators_and_chars(){
    o_String string1 = String("Nada");
    char string2[] = "Nada";
    const char* buffer = String_toArray(string1);
    ASSERT(strcmp(buffer, string2) == 0, 0 );
    OOC_DELETE(string1);
    return true;
}

UNIT_TEST(o_string_test_substr);
static bool o_string_test_substr(){
    o_String string1 = String("Um nada e um nada");
    o_String substr1 = String_subString(string1, 3, 4);
    o_String substr2 = String_subString(string1, 3, INT_MAX);
    o_String substr3 = String_subString(string1, -1, INT_MAX);
    ASSERT(!ooc_differ(substr1, String("nada")), 0 );
    ASSERT(!ooc_differ(substr2, String("nada e um nada")), 0 );
    ASSERT(!ooc_differ(substr3, String("")), 0 );
    OOC_DELETE(string1);
    OOC_DELETE(substr1);
    OOC_DELETE(substr2);
    OOC_DELETE(substr3);
    return true;
}

UNIT_TEST(o_string_test_append_m);
static bool o_string_test_append_m(){
    o_String o_string1 = String("Um");
    String_appendM(o_string1, " nada", String(" e um nada"));
    ASSERT(!ooc_differ(o_string1, String("Um nada e um nada")), false);
    OOC_DELETE(o_string1);
    o_String o_string2 = String_appendM(String("Ola"), " eu sou o goku!", String(" Vamos ser felizes."));
    ASSERT(!ooc_differ(o_string2, String("Ola eu sou o goku! Vamos ser felizes.")), false);
    OOC_DELETE(o_string2);
    return true;
}

void o_string_test(){
	// o_String o_string = String("Ola");
	// OOC_DELETE(o_string);
    StringClass();
    VectorClass();
    VectorIteratorClass();
	RUN_TEST(o_string_test_clears);
	RUN_TEST(o_string_test_charAt);
	RUN_TEST(o_string_test_assign_append_erase);
	RUN_TEST(o_string_test_add);
	RUN_TEST(o_string_test_insert_erase);
	RUN_TEST(o_string_test_ends_with);
	RUN_TEST(o_string_test_starts_with);
	RUN_TEST(o_string_test_to_lower);
	RUN_TEST(o_string_test_trim);
	RUN_TEST(o_string_test_replace_all);
	RUN_TEST(o_string_test_split);
	RUN_TEST(o_string_find_replace);
	RUN_TEST(o_string_test_iterators_and_chars);
	RUN_TEST(o_string_test_substr);
    RUN_TEST(o_string_test_append_m);
}

