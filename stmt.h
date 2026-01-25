
#ifndef STATEMENT_H
#define STATEMENT_H

#include <stdbool.h>
#include "decl.h"

typedef enum {
	STMT_DECL,
	STMT_EXPR,
	STMT_IF_ELSE,
	STMT_FOR,
	STMT_WHILE,
	STMT_PRINT,
	STMT_RETURN,
	STMT_BLOCK
} stmt_t;

struct stmt {
	stmt_t kind;
	struct decl *decl;
	struct expr *init_expr;
	struct expr *expr;
	struct expr *next_expr;
	struct stmt *body;
	struct stmt *else_body;
	struct stmt *next;
};

struct stmt * stmt_create( stmt_t kind, struct decl *decl, struct expr *init_expr, struct expr *expr, struct expr *next_expr, struct stmt *body, struct stmt *else_body, struct stmt *next );
void stmt_print( struct stmt *s, int indent );
void stmt_print_block( struct stmt * to_print, int indent );
void stmt_resolve( struct stmt * s );
void stmt_delete( struct stmt * s );
bool stmt_equals( struct stmt * a, struct stmt * b );
void stmt_typecheck( struct stmt * s, struct decl * d );

void stmt_error_print( struct expr * e, struct type *t1, struct type *t2 );
void stmt_codegen( struct stmt * s, struct decl * d );
void stmt_print_space();

#endif
