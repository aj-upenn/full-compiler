
%token TOKEN_REGISTER_RAX
%token TOKEN_REGISTER_RBX
%token TOKEN_REGISTER_RCX
%token TOKEN_REGISTER_RDX

%token TOKEN_REGISTER_FIRST_FUNCTION_ARG
%token TOKEN_REGISTER_SECOND_FUNCTION_ARG
%token TOKEN_REGISTER_STACK_POINTER
%token TOKEN_REGISTER_FRAME_POINTER

%token TOKEN_REGISTER_8
%token TOKEN_REGISTER_9
%token TOKEN_REGISTER_10
%token TOKEN_REGISTER_11
%token TOKEN_REGISTER_12
%token TOKEN_REGISTER_13
%token TOKEN_REGISTER_14
%token TOKEN_REGISTER_15

%token TOKEN_IMMEDIATE
%token TOKEN_DIGIT

%token TOKEN_OP_LEFT_PAREN
%token TOKEN_OP_RIGHT_PAREN
%token TOKEN_OP_COMMA 
%token TOKEN_OP_COLON
%token TOKEN_OP_NEWLINE

%token TOKEN_DIRECTIVE_DATA
%token TOKEN_DIRECTIVE_QUAD
%token TOKEN_DIRECTIVE_TEXT
%token TOKEN_DIRECTIVE_GLOBAL
%token TOKEN_DIRECTIVE_SECTION
%token TOKEN_DIRECTIVE_GNU_STACK
%token TOKEN_DIRECTIVE_PROGBITS
%token TOKEN_DIRECTIVE_FILE
%token TOKEN_DIRECTIVE_STRING

%token TOKEN_IDENTIFIER
%token TOKEN_LITERAL_STRING

%token TOKEN_INSTR_MOVQ
%token TOKEN_INSTR_LEAQ
%token TOKEN_INSTR_ADDQ
%token TOKEN_INSTR_SUBQ
%token TOKEN_INSTR_IMULQ
%token TOKEN_INSTR_IDIVQ
%token TOKEN_INSTR_NEGQ
%token TOKEN_INSTR_INCQ
%token TOKEN_INSTR_DECQ
%token TOKEN_INSTR_CQO
%token TOKEN_INSTR_CMPQ
%token TOKEN_INSTR_JE
%token TOKEN_INSTR_JNE
%token TOKEN_INSTR_JL
%token TOKEN_INSTR_JG
%token TOKEN_INSTR_JLE
%token TOKEN_INSTR_JGE
%token TOKEN_INSTR_JMP
%token TOKEN_INSTR_CALL
%token TOKEN_INSTR_PUSHQ
%token TOKEN_INSTR_POPQ

%token TOKEN_ERROR_UNDEFINED_CHAR
%token TOKEN_EOF

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