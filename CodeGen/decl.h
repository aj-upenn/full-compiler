
#ifndef DECLARATION_H
#define DECLARATION_H

#include "type.h"
#include "stmt.h"
#include "expr.h"

struct decl {
	char *name;
	struct type *type;
	struct expr *value;
	struct stmt *code;
	struct symbol *symbol;
	struct decl *next;
   int local_counter;
};

struct decl * decl_create( char *name, struct type *type, struct expr *value, struct stmt *code, struct decl *next );
void decl_print( struct decl *d, int indent );
void decl_resolve( struct decl * d );
void decl_delete( struct decl *d );
void decl_typecheck( struct decl * d );
void decl_array_typecheck( struct type * t_param, struct expr * e_param );
void decl_codegen ( struct decl * d );
void decl_push_args( struct param_list * p, int counter );
void decl_push_saved_regs();
void decl_pop_saved_regs();
void decl_postamble();
void decl_gen_array( struct expr * e );

#endif


