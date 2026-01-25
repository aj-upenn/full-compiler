#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "expr.h"
#include "scope.h"
#include "codegenFunc.h"
#include "printerFunc.h"

extern char *yytext;
extern bool type_error;
extern FILE * ofp;

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right ){
   struct expr * e = malloc(sizeof(struct expr));
   e->kind = kind;
   e->left = left;
   e->right = right;
   e->name = 0;
   e->literal_value = 0;
   e->string_literal = 0;
   e->symbol = 0;
   e->reg = -1;
   return e;
}

struct expr * expr_create_name( const char *n ){
   struct expr * e = expr_create(EXPR_IDENT, 0, 0);
   e->name = strdup(n);
   return e;
}

struct expr * expr_create_integer_literal( int c ){
   struct expr * e = expr_create(EXPR_INTEGER, 0, 0);
   e->literal_value = c;
   return e;
}

struct expr * expr_create_boolean_literal( int c ){
   struct expr * e = expr_create(EXPR_BOOLEAN, 0, 0);
   e->literal_value = c;
   return e;
}

struct expr * expr_create_char_literal( char c ){
   struct expr * e = expr_create(EXPR_CHAR, 0, 0);
   e->literal_value = c;
   return e;
}

struct expr * expr_create_string_literal( const char *str ){
   struct expr * e = expr_create(EXPR_STRING, 0, 0);
   e->string_literal = strdup(str);
   return e;
}

void expr_print( struct expr *e ){
   if(!e) { return; }
   char c = 0;
   bool prec = false;
   if(e && e->left){ 
      prec = expr_get_precedence(e) > expr_get_precedence(e->left) && expr_get_precedence(e) != 9 && expr_get_precedence(e) != -1;
      if(prec) { printf("("); }
      expr_print(e->left);
      if(prec) { printf(")"); }
   }
   else{
      expr_print(e->left);
   }

   switch(e->kind){
      case EXPR_STRING:
         printf("\"%s\"", e->string_literal);
         break;
      case EXPR_CHAR:
         c = e->literal_value;
         if(c == '\n'){ printf("'\\n'"); }
         else if(c == '\\'){ printf("'\\''"); }
         else if(c == '\''){ printf("'\\''"); }
         else{ printf("'%c'", c); }
         break;
      case EXPR_INTEGER:
         printf("%d", e->literal_value);
         break;
      case EXPR_BOOLEAN:
         if(e->literal_value){ printf("true"); }
         else{ printf("false"); }
         break;
      case EXPR_ADD:
         printf("+");
         break;
      case EXPR_NEGATIVE:
      case EXPR_SUBTRACT:
         printf("-");
         break;
      case EXPR_MULTIPLY:
         printf("*");
         break;
      case EXPR_DIVIDE:
         printf("/");
         break;
      case EXPR_INCREMENT:
         printf("++");
         break;
      case EXPR_DECREMENT:
         printf("--");
         break;
      case EXPR_MODULO:
         printf("%%");
         break;
      case EXPR_IDENT:
         printf("%s", e->name);
         break;
      case EXPR_LOGICAL_NOT:
         printf("!");
         break;
      case EXPR_LOGICAL_AND:
         printf(" && ");
         break;
      case EXPR_LOGICAL_OR:
         printf(" || ");
         break;
      case EXPR_EXPONENT:
         printf("^");
         break;
      case EXPR_ASSIGNMENT:
         printf(" = ");
         break;
      case EXPR_LESS_THAN_OR_EQUAL:
         printf(" <= ");
         break;
      case EXPR_LESS_THAN:
         printf(" < ");
         break;
      case EXPR_GREATER_THAN_OR_EQUAL:
         printf(" >= ");
         break;
      case EXPR_GREATER_THAN:
         printf(" > ");
         break;
      case EXPR_IS_EQUAL:
         printf(" == ");
         break;
      case EXPR_IS_NOT_EQUAL:
         printf(" != ");
         break;
      case EXPR_TERNARY:
         printf(" ? ");
         break;
      case EXPR_COLON:
         printf(" : ");
         break;
      case EXPR_FUNCTION_CALL:
         printf("(");
         expr_print(e->right);
         printf(")");
         return;
      case EXPR_INDEX:
         if(e->right){
            printf("[");
            expr_print(e->right);
            printf("]");
         }
         return;
      case EXPR_ARG:
         if(e->right) { printf(", "); }
         break;
      case EXPR_ARRAY_DECL:
         printf("{");
         expr_print(e->right);
         printf("}");
         return;
      case EXPR_ARRAY_DECL_AUX:
         printf(", ");
         expr_print(e->right);
         return;
      default:
         break;
   }

   if(e->kind == EXPR_FUNCTION_CALL || e->kind == EXPR_ARRAY_DECL){
      if(e->left){ printf(", "); }
   }
   
   if(e && e->right){ 
      prec = expr_get_precedence(e) >= expr_get_precedence(e->right) && expr_get_precedence(e) != 9 && expr_get_precedence(e) != -1  && expr_get_precedence(e) != 0 ;
      if(prec) { printf("("); }
      expr_print(e->right);
      if(prec) { printf(")"); }
   }
   else{
      expr_print(e->right);
   }
}

int expr_get_precedence( struct expr *e ){
   if(!e) { return 9; }

   switch(e->kind){
      case EXPR_ASSIGNMENT: return -1;
      case EXPR_TERNARY: return -1;
      case EXPR_COLON: return 0;
      case EXPR_LOGICAL_OR: return 1;
      case EXPR_LOGICAL_AND: return 2;
      case EXPR_LESS_THAN: return 3;
      case EXPR_LESS_THAN_OR_EQUAL: return 3;
      case EXPR_GREATER_THAN: return 3;
      case EXPR_GREATER_THAN_OR_EQUAL: return 3;
      case EXPR_IS_EQUAL: return 3;
      case EXPR_IS_NOT_EQUAL: return 3;
      case EXPR_ADD: return 4;
      case EXPR_SUBTRACT: return 4;
      case EXPR_MULTIPLY: return 5;
      case EXPR_DIVIDE: return 5;
      case EXPR_MODULO: return 5;
      case EXPR_EXPONENT: return 6;
      case EXPR_NEGATIVE: return 7;
      case EXPR_LOGICAL_NOT: return 7;
      case EXPR_INCREMENT: return 8;
      case EXPR_DECREMENT: return 8;
      default: return 9;
   }
   
   return 9;
}

void expr_delete( struct expr * e ){
   if(!e) { return; }
   expr_delete(e->left);
   expr_delete(e->right);
   symbol_delete(e->symbol);
   free((void *) e->name);
   free((void *) e->string_literal);
   free(e);
}

void expr_resolve( struct expr *e ){
   if(!e) { return; }
   if( e->kind == EXPR_IDENT ) {
      e->symbol = scope_lookup(e->name);
      if(!e->symbol) { scope_error(e->name, SCOPE_NOT_DEFINED); }
   } 
   else {
      expr_resolve( e->left );
      expr_resolve( e->right );
   }
   symbol_print(e->symbol);
}

struct type * expr_typecheck( struct expr * e ){
   if(!e) { return 0; }
   struct type *lt = expr_typecheck(e->left);
   struct type *rt = expr_typecheck(e->right);

   struct type * result = 0;
   switch (e->kind){
      case EXPR_ARRAY_DECL:
         result = type_create(TYPE_ARRAY, expr_typecheck(e->right->right), 0);
         break;
      case EXPR_ARRAY_DECL_AUX:
         result = type_copy(lt);
         break;
      case EXPR_IDENT:
         result = type_copy(e->symbol->type);
         break;
      case EXPR_INTEGER:
         result = type_create(TYPE_INTEGER, 0, 0);
         break;
      case EXPR_STRING:
         result = type_create(TYPE_STRING, 0, 0);
         break;
      case EXPR_BOOLEAN:
         result = type_create(TYPE_BOOLEAN, 0, 0);
         break;
      case EXPR_CHAR:
         result = type_create(TYPE_CHAR, 0, 0);
         break;
      case EXPR_ADD:
         if(!(lt->kind == TYPE_INTEGER && rt->kind == TYPE_INTEGER)){ expr_error_print_2("add", lt, e->left, rt, e->right); }
         result = type_create(TYPE_INTEGER, 0 , 0);
         break;
      case EXPR_SUBTRACT:
         if(!(lt->kind == TYPE_INTEGER && rt->kind == TYPE_INTEGER)){  expr_error_print_2("subtract", lt, e->left, rt, e->right); }
         result = type_create(TYPE_INTEGER, 0 , 0);
         break;
      case EXPR_NEGATIVE: 
         if(!(rt->kind == TYPE_INTEGER)){ expr_error_print_1("negate", rt, e->right); }
         result = type_create(TYPE_INTEGER, 0 , 0);
         break;
      case EXPR_MULTIPLY:
         if(!(lt->kind == TYPE_INTEGER && rt->kind == TYPE_INTEGER)){ expr_error_print_2("multiply", lt, e->left, rt, e->right); }
         result = type_create(TYPE_INTEGER, 0 , 0);
         break;
      case EXPR_DIVIDE:
         if(!(lt->kind == TYPE_INTEGER && rt->kind == TYPE_INTEGER)){ result = type_copy(lt); }
         result = type_create(TYPE_INTEGER, 0 , 0);
         break;
      case EXPR_INCREMENT:
         if(lt->kind != TYPE_INTEGER || e->left->kind != EXPR_IDENT){ expr_error_print_1("increment", lt, e->left); }
         result = type_create(TYPE_INTEGER, 0 , 0);
         break;
      case EXPR_DECREMENT:
         if(lt->kind != TYPE_INTEGER || e->left->kind != EXPR_IDENT){ expr_error_print_1("decrement", lt, e->left);  }
         result = type_create(TYPE_INTEGER, 0 , 0);
         break;
      case EXPR_EXPONENT:
         if(!(lt->kind == TYPE_INTEGER && rt->kind == TYPE_INTEGER)){ expr_error_print_2("exponentiate", lt, e->left, rt, e->right); }
         result = type_create(TYPE_INTEGER, 0 , 0);
         break;
      case EXPR_MODULO:
         if(!(lt->kind == TYPE_INTEGER && rt->kind == TYPE_INTEGER)){ expr_error_print_2("modulate", lt, e->left, rt, e->right); }
         result = type_create(TYPE_INTEGER, 0 , 0);
         break;
      case EXPR_LOGICAL_NOT:
         if(!(rt->kind == TYPE_BOOLEAN)){ expr_error_print_1("logically negate", rt, e->right); }
         result = type_create(TYPE_BOOLEAN, 0, 0);
         break;
      case EXPR_LOGICAL_OR:
         if(!(lt->kind == TYPE_BOOLEAN && rt->kind == TYPE_BOOLEAN)){ expr_error_print_2("logically or", lt, e->left, rt, e->right); }
         result = type_create(TYPE_BOOLEAN, 0, 0); 
         break;
      case EXPR_LOGICAL_AND:
         if(!(lt->kind == TYPE_BOOLEAN && rt->kind == TYPE_BOOLEAN)){ expr_error_print_2("logically and", lt, e->left, rt, e->right); }
         result = type_create(TYPE_BOOLEAN, 0, 0); 
         break;
      case EXPR_LESS_THAN:
      case EXPR_GREATER_THAN:
      case EXPR_GREATER_THAN_OR_EQUAL:
      case EXPR_LESS_THAN_OR_EQUAL:
         if(!(lt->kind == TYPE_INTEGER && rt->kind == TYPE_INTEGER)){  expr_error_print_2("compare", lt, e->left, rt, e->right); }
         result = type_create(TYPE_BOOLEAN, 0, 0);
         break;
      case EXPR_IS_NOT_EQUAL:
      case EXPR_IS_EQUAL:
         if(!(lt->kind == rt->kind)){ expr_error_print_2("equate", lt, e->left, rt, e->right); }
         result = type_create(TYPE_BOOLEAN, 0, 0);
         break;
      case EXPR_ASSIGNMENT:
         if(lt->kind == TYPE_AUTO){ lt = e->left->symbol->type = type_copy(rt); }
         if((lt->kind == rt->kind) && e->left->kind == EXPR_IDENT){ result = type_copy(lt); }
         else {
            if(!expr_is_array(e->left)){ 
               expr_error_print_2("assign", lt, e->left, rt, e->right); result = type_copy(lt); 
            }
            result = type_copy(lt);
         }
         break;
      case EXPR_TERNARY:
         if(lt->kind != TYPE_BOOLEAN){  
            printf("type error: first expression (");
            expr_print(e);
            printf(") in ternary operation must be a boolean\n");
            type_error = true;
         }
         result = type_copy(rt);
         break;
      case EXPR_FUNCTION_CALL:
         if(lt->kind != TYPE_FUNCTION){            
            printf("type error: ");
            expr_print(e->left);
            printf(" must be a function but is a "); 
            type_print(lt);
            printf("\n");
            type_error = true; 
         }
         expr_func_list_typecheck(lt, rt, e);
         result = type_copy(lt->subtype);
         break;
      case EXPR_INDEX:
         if(lt->kind == TYPE_ARRAY && rt->kind == TYPE_INTEGER){ result = type_copy(lt); }
         else{
            printf("type error: the symbol (");
            expr_print(e->left);
            printf(") is of type ");
            type_print(lt);
            printf(", but must be an array. (");
            expr_print(e->right);
            printf(") must also be an integer\n");
            //exit(1);
            type_error = true;
         }
         result = type_copy(lt->subtype);
         break;
      case EXPR_COLON:
         if(!(e->left->kind == e->right->kind)){ expr_error_print_2("have the result of a ternary opeartor be a", lt, e->left, rt, e->right); }
         result = type_copy(lt);
         break;
      case EXPR_ARG:
         result = type_copy(lt);
         break;
      default:
         break;
   }

   return result;
}

void expr_error_print_1( char * verb, struct type *t, struct expr * e ){
   printf("type error: cannot ");
   printf("%s (", verb);
   expr_print(e);
   printf("), a ");
   type_print(t);
   printf("\n");
   type_error = true;
}

void expr_error_print_2( char * verb, struct type * t1, struct expr * e1, struct type * t2, struct expr * e2 ){
   printf("type error: cannot ");
   printf("%s ", verb);
   type_print(t1);
   printf(" (");
   expr_print(e1);
   printf(") and a ");
   type_print(t2);
   printf(" (");
   expr_print(e2);
   printf(")\n");
   type_error = true;
}

void expr_func_list_typecheck(struct type * lt, struct type * rt, struct expr * e ){
   while(1){
      if(!lt->params && !rt) { break; }
      else if((!rt && lt->params)) { 
         printf("type error: not enough arguments for function\n"); 
         type_error = true; 
         break; 
      }
      else if((!lt->params && rt)) { stmt_error_print(e->right, rt, type_create(TYPE_VOID, 0 , 0)); break; } 
         else if(!type_equals(lt->params->type, rt)) { stmt_error_print(e->right, rt, lt->params->type); }
         lt->params = lt->params->next;
         e = e->right;
         rt = expr_typecheck(e->right);
      }
}


void expr_codegen( struct expr * e ){
   if(!e) { return; }
   char * l1 = 0;
   char * l2 = 0;
   switch(e->kind){
      case EXPR_ARRAY_DECL:
         break;
      case EXPR_ARRAY_DECL_AUX:
         break;
      case EXPR_IDENT:
         e->reg = scratch_alloc();
         if(e->symbol->kind == SYMBOL_GLOBAL && e->symbol->type->kind == TYPE_STRING){ fprintf(ofp, "   LEAQ %s, %s\n", symbol_codegen(e->symbol), scratch_name(e->reg)); }
         else {          fprintf(ofp, "   MOVQ %s, %s\n", symbol_codegen(e->symbol), scratch_name(e->reg)); }
         break;
      case EXPR_INTEGER:
         e->reg = scratch_alloc();
         fprintf(ofp, "   MOVQ $%d, %s\n", e->literal_value, scratch_name(e->reg));
         break;
      case EXPR_STRING:
         e->reg = scratch_alloc();
         l1 = label_name(label_create());
         fprintf(ofp, ".data\n");
         label_print(l1);
         fprintf(ofp, "   .string \"%s\"\n", e->string_literal);
         fprintf(ofp, ".text\n");
         fprintf(ofp, "   LEAQ %s, %s\n", l1, scratch_name(e->reg));
         break;
      case EXPR_BOOLEAN:
         e->reg = scratch_alloc();
         fprintf(ofp, "   MOVQ $%d, %s\n", e->literal_value, scratch_name(e->reg));
         break;
      case EXPR_CHAR:
         e->reg = scratch_alloc();
         fprintf(ofp, "   MOVQ $%d, %s\n", e->literal_value, scratch_name(e->reg));
         break;
      case EXPR_ADD:
         expr_codegen(e->left);
         expr_codegen(e->right);
         fprintf(ofp, "   ADDQ %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
         e->reg = e->right->reg;
         scratch_free(e->left->reg);
         break;
      case EXPR_SUBTRACT:
         expr_codegen(e->left);
         expr_codegen(e->right);
         fprintf(ofp, "   SUBQ %s, %s\n", scratch_name(e->right->reg) ,scratch_name(e->left->reg));
         e->reg = e->left->reg;
         scratch_free(e->right->reg);
         break;
      case EXPR_NEGATIVE:
         expr_codegen(e->right);
         fprintf(ofp, "   NEGQ %s\n", scratch_name(e->right->reg));
         e->reg = e->right->reg;
         break;
      case EXPR_MULTIPLY:
         expr_codegen(e->left);
         expr_codegen(e->right);
         fprintf(ofp, "   MOVQ %s, %%rax\n", scratch_name(e->right->reg));
         fprintf(ofp, "   IMULQ %s\n", scratch_name(e->left->reg));
         fprintf(ofp, "   MOVQ %%rax, %s\n", scratch_name(e->right->reg));
         e->reg = e->right->reg;
         scratch_free(e->left->reg);
         break;
      case EXPR_DIVIDE:
         expr_codegen(e->left);
         expr_codegen(e->right);
         fprintf(ofp, "   MOVQ %s, %%rax\n", scratch_name(e->left->reg));
         fprintf(ofp, "   CQO\n");
         fprintf(ofp, "   IDIVQ %s\n", scratch_name(e->right->reg));
         fprintf(ofp, "   MOVQ %%rax, %s\n", scratch_name(e->right->reg));
         e->reg = e->right->reg;
         scratch_free(e->left->reg);
         break;
      case EXPR_INCREMENT:
         fprintf(ofp, "   INCQ %s\n", symbol_codegen(e->left->symbol));
         e->reg = scratch_alloc();
         break;
      case EXPR_DECREMENT:
         fprintf(ofp, "   DECQ %s\n", symbol_codegen(e->left->symbol));
         e->reg = scratch_alloc();
         break;
      case EXPR_EXPONENT:
         e->reg = scratch_alloc();
         expr_codegen(e->left);
         expr_codegen(e->right);
         expr_push_saved_regs();
         fprintf(ofp, "   MOVQ %s, %%rdi\n", scratch_name(e->left->reg));
         fprintf(ofp, "   MOVQ %s, %%rsi\n", scratch_name(e->right->reg));
         fprintf(ofp, "   CALL integer_power\n");
         expr_pop_saved_regs();
         scratch_free(e->left->reg);
         scratch_free(e->right->reg);
         fprintf(ofp, "   MOVQ %%rax, %s\n", scratch_name(e->reg));
         break;
      case EXPR_MODULO:
         expr_codegen(e->left);
         expr_codegen(e->right);
         fprintf(ofp, "   MOVQ %s, %%rax\n", scratch_name(e->left->reg));
         fprintf(ofp, "   CQO\n");
         fprintf(ofp, "   IDIVQ %s\n", scratch_name(e->right->reg));
         fprintf(ofp, "   MOVQ %%rdx, %s\n", scratch_name(e->right->reg));
         e->reg = e->right->reg;
         scratch_free(e->left->reg);
         break;
      case EXPR_LOGICAL_NOT:
         expr_codegen(e->right);
         l1 = label_name(label_create());
         l2 = label_name(label_create());
         fprintf(ofp, "   CMPQ $0, %s\n", scratch_name(e->right->reg));
         fprintf(ofp, "   JE %s\n", l1);
         fprintf(ofp, "   MOVQ $0, %s\n", scratch_name(e->right->reg));
         fprintf(ofp, "   JMP %s\n", l2);
         label_print(l1);
         fprintf(ofp, "   MOVQ $1, %s\n", scratch_name(e->right->reg));
         label_print(l2);
         e->reg = e->right->reg;
         break;
      case EXPR_LOGICAL_OR:
         expr_codegen(e->left);
         expr_codegen(e->right);
         l1 = label_name(label_create());
         l2 = label_name(label_create());
         fprintf(ofp, "   CMPQ $1, %s\n", scratch_name(e->left->reg));
         fprintf(ofp, "   JE %s\n", l1);
         fprintf(ofp, "   CMPQ $1, %s\n", scratch_name(e->right->reg));
         fprintf(ofp, "   JE %s\n", l1);
         fprintf(ofp, "   MOVQ $0, %s\n", scratch_name(e->right->reg));
         fprintf(ofp, "   JMP %s\n", l2);
         label_print(l1);
         fprintf(ofp, "   MOVQ $1, %s\n", scratch_name(e->right->reg));
         label_print(l2);
         e->reg = e->right->reg;
         scratch_free(e->left->reg);
         break;
      case EXPR_LOGICAL_AND: 
         expr_codegen(e->left);
         expr_codegen(e->right);
         l1 = label_name(label_create());
         l2 = label_name(label_create());
         fprintf(ofp, "   CMPQ $0, %s\n", scratch_name(e->left->reg));
         fprintf(ofp, "   JE %s\n", l1);
         fprintf(ofp, "   CMPQ $0, %s\n", scratch_name(e->right->reg));
         fprintf(ofp, "   JE %s\n", l1);
         fprintf(ofp, "   MOVQ $1, %s\n", scratch_name(e->right->reg));
         fprintf(ofp, "   JMP %s\n", l2);
         label_print(l1);
         fprintf(ofp, "   MOVQ $0, %s\n", scratch_name(e->right->reg));
         label_print(l2);
         e->reg = e->right->reg;
         scratch_free(e->left->reg);
         break;
      case EXPR_LESS_THAN:
         expr_gen_comparison(e, "JL");
         break;
      case EXPR_GREATER_THAN:
         expr_gen_comparison(e, "JG");
         break;
      case EXPR_GREATER_THAN_OR_EQUAL:
         expr_gen_comparison(e, "JGE");
         break;
      case EXPR_LESS_THAN_OR_EQUAL:
         expr_gen_comparison(e, "JLE");
         break;
      case EXPR_IS_NOT_EQUAL:
         expr_gen_comparison(e, "JNE");
         break;
      case EXPR_IS_EQUAL:
         expr_gen_comparison(e, "JE");
         break;
      case EXPR_ASSIGNMENT:
         expr_codegen(e->right);
         if(expr_is_array(e->left)){
            expr_codegen(e->left);
            scratch_free(e->left->reg);
            fprintf(ofp, "   MOVQ %s, (%%rax)\n", scratch_name(e->right->reg)); 
         }
         else{ fprintf(ofp, "   MOVQ %s, %s\n", scratch_name(e->right->reg), symbol_codegen(e->left->symbol)); }
         e->reg = e->right->reg;
         break;
      case EXPR_TERNARY:
         expr_codegen(e->left);
         fprintf(ofp, "   CMPQ $1, %s\n", scratch_name(e->left->reg));
         expr_codegen(e->right->left);
         expr_codegen(e->right->right);
         l1 = label_name(label_create());
         l2 = label_name(label_create());
         fprintf(ofp, "   JE %s\n", l1);
         fprintf(ofp, "   MOVQ %s, %s\n", scratch_name(e->right->right->reg), scratch_name(e->left->reg));
         fprintf(ofp, "   JMP %s\n", l2);
         label_print(l1);
         fprintf(ofp, "   MOVQ %s, %s\n", scratch_name(e->right->left->reg), scratch_name(e->left->reg));
         label_print(l2);
         e->reg = e->left->reg;
         scratch_free(e->right->left->reg);
         scratch_free(e->right->right->reg);
         break;
      case EXPR_FUNCTION_CALL:
         expr_codegen(e->right);
         e->reg = scratch_alloc();
         expr_push_saved_regs();
         expr_setup_args(e->right, 0);
         fprintf(ofp, "   CALL %s\n", e->left->symbol->name);
         expr_pop_saved_regs();
         fprintf(ofp, "   MOVQ %%rax, %s\n", scratch_name(e->reg));
         if(e->right) { scratch_free(e->right->reg); }
         break;
      case EXPR_INDEX:
         expr_codegen(e->right);
         //expr_codegen(e->left);
         e->reg = scratch_alloc();
         fprintf(ofp, "   LEAQ %s, %s\n", symbol_codegen(e->left->symbol), scratch_name(e->reg));
         //scratch_free(e->left->reg);
         fprintf(ofp, "   MOVQ $8, %%rax\n");
         scratch_free(e->right->reg);
         fprintf(ofp, "   IMULQ %s\n", scratch_name(e->right->reg));
         fprintf(ofp, "   ADDQ %s, %%rax\n", scratch_name(e->reg));
         fprintf(ofp, "   MOVQ (%%rax), %s\n", scratch_name(e->reg));
         break;
      case EXPR_COLON:
         break;
      case EXPR_ARG:
         expr_codegen(e->left);
         expr_codegen(e->right);
         e->reg = e->left->reg;
         if(e->right){ scratch_free(e->right->reg); }
         break;
      default:
         break;
   }
}

void expr_gen_comparison( struct expr * e, char * instruction ){
   expr_codegen(e->left);
   expr_codegen(e->right);
   char * cond_fufilled = label_name(label_create());
   char * end = label_name(label_create());

   if(expr_typecheck(e->left)->kind == TYPE_STRING){
      expr_push_saved_regs();
      fprintf(ofp, "   MOVQ %s, %%rdi\n", scratch_name(e->left->reg));
      fprintf(ofp, "   MOVQ %s, %%rsi\n", scratch_name(e->right->reg));
      fprintf(ofp, "   CALL strcmp\n");
      expr_pop_saved_regs();
      fprintf(ofp, "   CMPQ $0, %%rax\n");
   }
   else{
      fprintf(ofp, "   CMPQ %s, %s\n", scratch_name(e->right->reg), scratch_name(e->left->reg));
   }
   fprintf(ofp, "   %s %s\n", instruction, cond_fufilled);
   fprintf(ofp, "   MOVQ $0, %s\n", scratch_name(e->right->reg));
   fprintf(ofp, "   JMP %s\n", end);
   label_print(cond_fufilled);
   fprintf(ofp, "   MOVQ $1, %s\n", scratch_name(e->right->reg));
   label_print(end);
   e->reg = e->right->reg;
   scratch_free(e->left->reg);
}

void expr_push_saved_regs(){
   fprintf(ofp, "   PUSHQ %%r10\n");
   fprintf(ofp, "   PUSHQ %%r11\n");
}

void expr_pop_saved_regs(){
   fprintf(ofp, "   POPQ %%r11\n");
   fprintf(ofp, "   POPQ %%r10\n");
}

void expr_setup_args( struct expr * e, int counter ){
   if(!e) { return; }
   expr_setup_args(e->right, ++counter);
   struct type * type = expr_typecheck(e);
   char instruction[10] = {0};
   char name[10] = {0};

   if(type->kind == TYPE_STRING){ 
      if(e->left->symbol->kind == SYMBOL_GLOBAL) { strcpy(instruction, "LEAQ"); }
      else{ strcpy(instruction, "MOVQ"); }
      strcpy(name, symbol_codegen(e->left->symbol));
   }
   else{ 
      strcpy(instruction, "MOVQ");
      strcpy(name, scratch_name(e->reg)); 
   }
   switch (counter){
      case 1:
         fprintf(ofp, "   %s %s, %%rdi\n", instruction, name);
         break;
      case 2:
         fprintf(ofp, "   %s %s, %%rsi\n", instruction, name);
         break;
      case 3:
         fprintf(ofp, "   %s %s, %%rdx\n", instruction, name);
         break;
      case 4:
         fprintf(ofp, "   %s %s, %%rcx\n", instruction, name);
         break;
      case 5:
         fprintf(ofp, "   %s %s, %%r8\n", instruction, name);
         break;
      case 6:
         fprintf(ofp, "   %s %s, %%r9\n", instruction, name);
         break;
      default:
         printf("codegen error: Too many function arguments\n");
         exit(1);
         break;
   }
}

bool expr_is_array( struct expr * e ){
   if(!(e && e->left && e->left->symbol->type->kind == TYPE_ARRAY)) { return false; }
   return true;
}