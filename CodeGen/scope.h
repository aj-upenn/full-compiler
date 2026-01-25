
#ifndef SCOPE_H
#define SCOPE_H

#include <stdbool.h>
#include "symbol.h"
#include "stmt.h"

typedef enum {
   SCOPE_ALREADY_DEFINED,
   SCOPE_NOT_DEFINED
} scope_error_t;

struct scope_table {
   struct hash_table * stack[100];
   int level;
   bool error_found;
};

void scope_enter();
void scope_exit();
int scope_level();
void scope_bind( const char *name, struct symbol *sym, struct stmt * code );
struct symbol *scope_lookup( const char *name );
struct symbol *scope_lookup_current( const char *name );
void scope_create_function_code();
void scope_delete_function_code();

void scope_error( const char * s, int type );
bool scope_correct();

#endif