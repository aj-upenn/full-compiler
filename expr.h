#ifndef EXPR_H
#define EXPR_H

#include "symbol.h"

typedef enum {
   EXPR_ADD,
   EXPR_SUBTRACT,
   EXPR_NEGATIVE,
   EXPR_MULTIPLY,
   EXPR_DIVIDE,
   EXPR_INCREMENT,
   EXPR_DECREMENT,
   EXPR_EXPONENT,
   EXPR_MODULO,
   EXPR_LOGICAL_NOT,
   EXPR_LOGICAL_OR,
   EXPR_LOGICAL_AND,
   EXPR_LESS_THAN_OR_EQUAL,
   EXPR_LESS_THAN,
   EXPR_GREATER_THAN_OR_EQUAL,
   EXPR_GREATER_THAN,
   EXPR_IS_EQUAL,
   EXPR_IS_NOT_EQUAL,
   EXPR_ASSIGNMENT,
   EXPR_TERNARY,
   EXPR_COLON,
   EXPR_IDENT,
   EXPR_INTEGER,
   EXPR_BOOLEAN,
   EXPR_CHAR,
   EXPR_STRING,
   EXPR_ARG,
   EXPR_FUNCTION_CALL,
   EXPR_INDEX,
   EXPR_ARRAY_DECL,
   EXPR_ARRAY_DECL_AUX
} expr_t;

struct expr {
   /* used by all kinds of exprs */
   expr_t kind;
   struct expr *left;
   struct expr *right;

   /* used by various leaf exprs */
   const char *name;
   int literal_value;
   char * string_literal;
   struct symbol *symbol;
   int reg;
};

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right );

struct expr * expr_create_name( const char *n );
struct expr * expr_create_integer_literal( int c );
struct expr * expr_create_boolean_literal( int c );
struct expr * expr_create_char_literal( char c );
struct expr * expr_create_string_literal( const char *str );

void expr_print( struct expr *e );
int expr_get_precedence( struct expr *e );
void expr_resolve( struct expr *e );
void expr_delete( struct expr * e );
struct type * expr_typecheck( struct expr * e );
void expr_error_print_1( char * verb, struct type *t, struct expr * e );
void expr_error_print_2( char * verb, struct type * t1, struct expr * e1, struct type * t2, struct expr * e2 );
void expr_func_list_typecheck(struct type * lt, struct type * rt, struct expr * e );
void expr_codegen( struct expr * e );
void expr_gen_comparison( struct expr * e, char * instruction );
void expr_push_saved_regs();
void expr_pop_saved_regs();
void expr_setup_args( struct expr * e, int counter );
bool expr_is_array( struct expr * e );

#endif
