
%token TOKEN_EOF
%token TOKEN_KEY_ARRAY
%token TOKEN_KEY_AUTO
%token TOKEN_KEY_BOOLEAN
%token TOKEN_KEY_CHAR
%token TOKEN_KEY_ELSE
%token TOKEN_KEY_FALSE
%token TOKEN_KEY_FOR
%token TOKEN_KEY_FUNCTION
%token TOKEN_KEY_IF
%token TOKEN_KEY_INTEGER
%token TOKEN_KEY_PRINT
%token TOKEN_KEY_RETURN
%token TOKEN_KEY_STRING
%token TOKEN_KEY_TRUE
%token TOKEN_KEY_VOID
%token TOKEN_KEY_WHILE
%token TOKEN_IDENTIFIER
%token TOKEN_OP_LEFT_PAREN
%token TOKEN_OP_RIGHT_PAREN
%token TOKEN_OP_LEFT_BRACKET
%token TOKEN_OP_RIGHT_BRACKET
%token TOKEN_OP_LEFT_BRACE
%token TOKEN_OP_RIGHT_BRACE
%token TOKEN_OP_INCREMENT
%token TOKEN_OP_DECREMENT
%token TOKEN_OP_SUBTRACT
%token TOKEN_OP_ADD
%token TOKEN_OP_LOGICAL_NOT
%token TOKEN_OP_EXPONENT
%token TOKEN_OP_MULTIPLY
%token TOKEN_OP_DIVIDE
%token TOKEN_OP_MODULO
%token TOKEN_OP_LESS_THAN
%token TOKEN_OP_LESS_THAN_OR_EQUAL
%token TOKEN_OP_GREATER_THAN
%token TOKEN_OP_GREATER_THAN_OR_EQUAL
%token TOKEN_OP_IS_EQUAL
%token TOKEN_OP_IS_NOT_EQUAL
%token TOKEN_OP_ASSIGNMENT
%token TOKEN_OP_LOGICAL_AND
%token TOKEN_OP_LOGICAL_OR
%token TOKEN_OP_SEMICOLON
%token TOKEN_OP_COLON
%token TOKEN_OP_TERNARY
%token TOKEN_OP_COMMA
%token TOKEN_LITERAL_INTEGER
%token TOKEN_LITERAL_CHAR
%token TOKEN_LITERAL_STRING
%token TOKEN_COMMENT_C
%token TOKEN_COMMENT_CPP
%token TOKEN_ERROR_INVALID_CHAR_LITERAL
%token TOKEN_ERROR_INVALID_STRING_LITERAL
%token TOKEN_ERROR_INVALID_IDENTIFIER
%token TOKEN_ERROR_UNDEFINED_CHAR

%union {
	struct decl *decl;
	struct stmt *stmt;
	struct expr *expr;
   struct type *type;
   struct param_list *param_list;
   struct symbol *symbol;
   char *name;
   int value;
};

%type <decl> program

%{

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *yytext;
extern int yylex();
extern int yyerror( char *str );
extern struct decl * program_pointer;

%}

%%

/* PROGRAM */

program  : /* epsilon */   { $$ = 0; }
         ;

%%

int yyerror( char *str ) {
   printf("Parse Error: %s\n",str);
   return 0;
}