
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

%type <decl> program decl_list decl decl_empty decl_assign decl_array decl_func
%type <stmt> stmt stmt_list stmt_list_aux stmt_closed stmt_open stmt_atom
%type <type> type type_func
%type <expr> expr expr_l0 expr_l0_aux expr_l1 expr_l2 expr_l3 expr_l4 expr_l5 expr_l6 expr_l7 expr_l8 expr_l9 expr_atom stmt_or_empty expr_arg expr_arg_aux arr_list expr_or_eps arr_expr_list arr_index
%type <param_list> decl_param decl_param_list decl_param_list_aux
%type <name> ident literal_string literal_char
%type <value> literal_integer literal_false literal_true

%{

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stmt.h"
#include "decl.h"
#include "expr.h"
#include "param_list.h"
#include "scannerFunc.h"

extern char *yytext;
extern int yylex();
extern int yyerror( char *str );
extern struct decl * program_pointer;

%}

%%

/* PROGRAM */

program  : decl_list       { program_pointer = $$ = $1; }
         | /* epsilon */   { $$ = 0; }
         ;

/* DECLARATIONS*/

decl_list: decl decl_list  { $1->next = $2; $$ = $1; }
         | decl            { $$ = $1; }
         ;
   
decl     : decl_empty TOKEN_OP_SEMICOLON  { $$ = $1; }
         | decl_assign TOKEN_OP_SEMICOLON { $$ = $1; }
         | decl_array TOKEN_OP_SEMICOLON  { $$ = $1; }
         | decl_func TOKEN_OP_ASSIGNMENT TOKEN_OP_LEFT_BRACE stmt_list TOKEN_OP_RIGHT_BRACE { $1->code = $4; $$ = $1; }
         | decl_func TOKEN_OP_SEMICOLON   { $$ = $1; }
         ;

decl_empty  : ident TOKEN_OP_COLON type { $$ = decl_create($1, $3, 0, 0, 0); }
            ;

decl_assign : ident TOKEN_OP_COLON type TOKEN_OP_ASSIGNMENT expr { $$ = decl_create($1, $3, $5, 0, 0); }
            ;

decl_array  : ident TOKEN_OP_COLON type TOKEN_OP_ASSIGNMENT arr_list { $$ = decl_create($1, $3, $5, 0, 0); }
            ;

decl_func: ident TOKEN_OP_COLON type_func { $$ = decl_create($1, $3, 0, 0, 0); }
         ;


decl_param  : decl_empty   { param_list_create($1->name, $1->type, 0);  }
            | decl_func    { param_list_create($1->name, $1->type, 0); }
            ;


decl_param_list: decl_param_list_aux   { $$ = $1; }
               | /* epsilon */         { $$ = 0; }
               ;
   
decl_param_list_aux  : decl_param TOKEN_OP_COMMA decl_param_list_aux { $1->next = $3; $$ = $1; }
                     | decl_param                                    { $$ = $1; }      
                     ;


/* TYPES */

type     : TOKEN_KEY_STRING   { $$ = type_create(TYPE_STRING, 0, 0); }
         | TOKEN_KEY_BOOLEAN  { $$ = type_create(TYPE_BOOLEAN, 0, 0); }
         | TOKEN_KEY_AUTO     { $$ = type_create(TYPE_AUTO, 0, 0); }
         | TOKEN_KEY_CHAR     { $$ = type_create(TYPE_CHAR, 0, 0); }
         | TOKEN_KEY_INTEGER  { $$ = type_create(TYPE_INTEGER, 0, 0); }
         | TOKEN_KEY_ARRAY TOKEN_OP_LEFT_BRACKET expr_or_eps TOKEN_OP_RIGHT_BRACKET type  { $$ = type_create(TYPE_ARRAY, $5, 0); $$->arrSubscript = $3; }
         | TOKEN_KEY_VOID     { $$ = type_create(TYPE_VOID, 0, 0); }
         ;

type_func: TOKEN_KEY_FUNCTION type TOKEN_OP_LEFT_PAREN decl_param_list TOKEN_OP_RIGHT_PAREN      { $$ = type_create(TYPE_FUNCTION, $2, $4); }
         | TOKEN_KEY_FUNCTION type_func TOKEN_OP_LEFT_PAREN decl_param_list TOKEN_OP_RIGHT_PAREN { $$ = type_create(TYPE_FUNCTION, $2, $4); }
         ;

/* STATEMENTS */ 

stmt     : stmt_open    { $$ = $1; }
         | stmt_closed  { $$ = $1; } 
         ;

stmt_open: TOKEN_KEY_IF TOKEN_OP_LEFT_PAREN expr TOKEN_OP_RIGHT_PAREN stmt_open                                      { $$ = stmt_create(STMT_IF_ELSE, 0, 0, $3, 0, $5, 0, 0); }
         | TOKEN_KEY_IF TOKEN_OP_LEFT_PAREN expr TOKEN_OP_RIGHT_PAREN stmt_closed TOKEN_KEY_ELSE stmt_open           { $$ = stmt_create(STMT_IF_ELSE, 0, 0, $3, 0, $5, $7, 0); }           
         | TOKEN_KEY_IF TOKEN_OP_LEFT_PAREN expr TOKEN_OP_RIGHT_PAREN stmt_closed                                    { $$ = stmt_create(STMT_IF_ELSE, 0, 0, $3, 0, $5, 0, 0); }
         | TOKEN_KEY_FOR TOKEN_OP_LEFT_PAREN stmt_or_empty stmt_or_empty expr_or_eps TOKEN_OP_RIGHT_PAREN stmt_open  { $$ = stmt_create(STMT_FOR, 0, $3, $4, $5, $7, 0, 0); }
         ;

stmt_closed : TOKEN_KEY_IF TOKEN_OP_LEFT_PAREN expr TOKEN_OP_RIGHT_PAREN stmt_closed TOKEN_KEY_ELSE stmt_closed            { $$ = stmt_create(STMT_IF_ELSE, 0, 0, $3, 0, $5, $7, 0); }
            | TOKEN_KEY_FOR TOKEN_OP_LEFT_PAREN stmt_or_empty stmt_or_empty expr_or_eps TOKEN_OP_RIGHT_PAREN stmt_closed   { $$ = stmt_create(STMT_FOR, 0, $3, $4, $5, $7, 0, 0); }
            | stmt_atom                                                                                                    { $$ = $1; }
            ;

stmt_atom: expr TOKEN_OP_SEMICOLON                             { $$ = stmt_create(STMT_EXPR, 0, 0, $1, 0, 0, 0, 0); }
         | TOKEN_KEY_RETURN expr_or_eps TOKEN_OP_SEMICOLON     { $$ = stmt_create(STMT_RETURN, 0, 0, $2, 0, 0, 0, 0); }
         | TOKEN_OP_LEFT_BRACE stmt_list TOKEN_OP_RIGHT_BRACE  { $$ = stmt_create(STMT_BLOCK, 0, 0, 0, 0, $2, 0, 0); }
         | TOKEN_KEY_PRINT expr_arg TOKEN_OP_SEMICOLON         { $$ = stmt_create(STMT_PRINT, 0, 0, $2, 0, 0, 0, 0); }
         | decl                                                { $$ = stmt_create(STMT_DECL, $1, 0, 0, 0, 0, 0, 0); }
         ;

stmt_or_empty  : expr TOKEN_OP_SEMICOLON  { $$ = $1; }          
               | TOKEN_OP_SEMICOLON       { $$ = 0; } 
               ;
         
stmt_list   : stmt_list_aux   { $$ = $1; }
            | /* epsilon */   { $$ = 0; }  
            ;

stmt_list_aux  : stmt stmt_list_aux { $1->next = $2; $$ = $1; }
               | stmt               { $$ = $1; }
               ;

/* EXPRESSIONS */

expr     : expr_l0   { $$ = $1; }
         ;

expr_l0  : expr_l1 TOKEN_OP_ASSIGNMENT expr_l0  { $$ = expr_create(EXPR_ASSIGNMENT, $1, $3); }
         | expr_l1 TOKEN_OP_TERNARY expr_l0_aux { $$ = expr_create(EXPR_TERNARY, $1, $3); }
         | expr_l1                              { $$ = $1; }
         ;

expr_l0_aux : expr_l1 TOKEN_OP_COLON expr_l0_aux   { $$ = expr_create(EXPR_COLON, $1, $3); }
            | expr_l0                              { $$ = $1; }   
            ;       

expr_l1  : expr_l1 TOKEN_OP_LOGICAL_OR expr_l2  { $$ = expr_create(EXPR_LOGICAL_OR, $1, $3); }
         | expr_l2                              { $$ = $1; }
         ;

expr_l2  : expr_l2 TOKEN_OP_LOGICAL_AND expr_l3 { $$ = expr_create(EXPR_LOGICAL_AND, $1, $3); }
         | expr_l3                              { $$ = $1; }
         ;              

expr_l3  : expr_l3 TOKEN_OP_LESS_THAN expr_l4               { $$ = expr_create(EXPR_LESS_THAN, $1, $3); }
         | expr_l3 TOKEN_OP_LESS_THAN_OR_EQUAL expr_l4      { $$ = expr_create(EXPR_LESS_THAN_OR_EQUAL, $1, $3); }
         | expr_l3 TOKEN_OP_GREATER_THAN  expr_l4           { $$ = expr_create(EXPR_GREATER_THAN, $1, $3); }
         | expr_l3 TOKEN_OP_GREATER_THAN_OR_EQUAL expr_l4   { $$ = expr_create(EXPR_GREATER_THAN_OR_EQUAL, $1, $3); }   
         | expr_l3 TOKEN_OP_IS_EQUAL expr_l4                { $$ = expr_create(EXPR_IS_EQUAL, $1, $3); }
         | expr_l3 TOKEN_OP_IS_NOT_EQUAL expr_l4            { $$ = expr_create(EXPR_IS_NOT_EQUAL, $1, $3); }
         | expr_l4                                          { $$ = $1; }
         ;

expr_l4  : expr_l4 TOKEN_OP_ADD expr_l5      { $$ = expr_create(EXPR_ADD, $1, $3); }
         | expr_l4 TOKEN_OP_SUBTRACT expr_l5 { $$ = expr_create(EXPR_SUBTRACT, $1, $3); }
         | expr_l5                           { $$ = $1; }
         ;              

expr_l5  : expr_l5 TOKEN_OP_MULTIPLY expr_l6 { $$ = expr_create(EXPR_MULTIPLY, $1, $3); }
         | expr_l5 TOKEN_OP_DIVIDE expr_l6   { $$ = expr_create(EXPR_DIVIDE, $1, $3); }
         | expr_l5 TOKEN_OP_MODULO expr_l6   { $$ = expr_create(EXPR_MODULO, $1, $3); }
         | expr_l6                           { $$ = $1; }
         ;                  

expr_l6  : expr_l7 TOKEN_OP_EXPONENT expr_l6 { $$ = expr_create(EXPR_EXPONENT, $1, $3); }
         | expr_l7                           { $$ = $1; }
         ;                           

expr_l7  : TOKEN_OP_ADD expr_l7           { $$ = $2;}
         | TOKEN_OP_SUBTRACT expr_l7      { $$ = expr_create(EXPR_NEGATIVE, 0, $2); }
         | TOKEN_OP_LOGICAL_NOT expr_l7   { $$ = expr_create(EXPR_LOGICAL_NOT, 0, $2); }
         | expr_l8                        { $$ = $1; }
         ;         

expr_l8  : expr_l8 TOKEN_OP_INCREMENT  { $$ = expr_create(EXPR_INCREMENT, $1, 0); }
         | expr_l8 TOKEN_OP_DECREMENT  { $$ = expr_create(EXPR_DECREMENT, $1, 0); }
         | expr_l9                     { $$ = $1; }
         ;         

expr_l9  : TOKEN_OP_LEFT_PAREN expr TOKEN_OP_RIGHT_PAREN                { $$ = $2; }
         | expr_l9 arr_index                                            { $$ = expr_create(EXPR_INDEX, $1, $2); }
         | expr_l9 TOKEN_OP_LEFT_PAREN expr_arg TOKEN_OP_RIGHT_PAREN    { $$ = expr_create(EXPR_FUNCTION_CALL, $1, $3); }
         | expr_atom                                                    { $$ = $1; }  
         ;

expr_atom: ident           { $$ = expr_create_name($1); }
         | literal_string  { $$ = expr_create_string_literal($1); }
         | literal_char    { $$ = expr_create_char_literal(*$1); }
         | literal_integer { $$ = expr_create_integer_literal($1); }
         | literal_false   { $$ = expr_create_boolean_literal($1); }
         | literal_true    { $$ = expr_create_boolean_literal($1); }   
         ; 

expr_arg : expr_arg_aux   { $$ = $1; }
         | /* epsilon */ { $$ = 0; }  
         ;

expr_arg_aux: expr TOKEN_OP_COMMA expr_arg_aux { $$ = expr_create(EXPR_ARG, $1, $3); }
            | expr                             { $$ = expr_create(EXPR_ARG, $1, 0); }
            ;

expr_or_eps : expr            { $$ = $1; }
            | /* epsilon */   { $$ = 0; }
            ;



/* MISCELLANEOUS */

arr_list : TOKEN_OP_LEFT_BRACE arr_expr_list TOKEN_OP_RIGHT_BRACE   { $$ = expr_create(EXPR_ARRAY_DECL, 0, $2); }
         ;

arr_expr_list  : arr_expr_list TOKEN_OP_COMMA expr       { $$ = expr_create(EXPR_ARRAY_DECL_AUX, $1, $3); }
               | expr                                    { $$ = $1; }
               | arr_expr_list TOKEN_OP_COMMA arr_list   { $$ = expr_create(EXPR_ARRAY_DECL_AUX, $1, $3); } 
               | arr_list                                { $$ = $1; }  
               ;
            
arr_index: TOKEN_OP_LEFT_BRACKET expr TOKEN_OP_RIGHT_BRACKET   { $$ = $2; }
         ;

ident : TOKEN_IDENTIFIER { $$ = strdup(yytext); } 
      ;

literal_string : TOKEN_LITERAL_STRING  { $$ = strdup(beautifyString(yytext)); }
               ;

literal_char: TOKEN_LITERAL_CHAR   { $$ = strdup(beautifyChar(yytext)); } 
            ;

literal_integer: TOKEN_LITERAL_INTEGER { $$ = atoi(yytext); }
               ;

literal_false  : TOKEN_KEY_FALSE { $$ = 0; }
               ;

literal_true: TOKEN_KEY_TRUE { $$ = 1; }
            ;
%%

int yyerror( char *str ) {
   printf("Parse Error: %s\n",str);
   return 0;
}