#include <stdlib.h>
#include <string.h>
#include "decl.h"
#include "type.h"
#include "scope.h"
#include "codegenFunc.h"

int local_counter = 0;
int param_counter = 0;
extern bool type_error;
extern bool stmt_return_found;
extern FILE * ofp;

struct decl * decl_create( char *name, struct type *type, struct expr *value, struct stmt *code, struct decl *next ){
   struct decl * d = malloc(sizeof(struct decl));
   d->name = name;
   d->type = type;
   d->value = value;
   d->code = code;
   d->next = next;
   d->symbol = 0;
   return d;
}


void decl_print( struct decl *d, int indent ){

   if(!d) { return; }
   //indentLine(indent);
   printf("%s: ", d->name);
   type_print(d->type);

   //Value
   struct expr * v = d->value;
   if(v){
      printf( " = ");
      expr_print(v);
   }

   //Code or Semicolon
   struct stmt * c = d->code;
   if(c){
      printf(" = {\n");
      stmt_print(c, indent);
      printf("}\n");
   }
   else{
      printf(";\n");
   }

   decl_print(d->next, indent);
}


void decl_resolve( struct decl *d )
{
   if(!d) { return; }

   symbol_t kind = scope_level() > 0 ? SYMBOL_LOCAL : SYMBOL_GLOBAL;
   d->symbol = symbol_create(kind, d->type, d->name);

   if(kind == SYMBOL_GLOBAL){ local_counter = param_counter = 0; }
   //else if(kind == SYMBOL_PARAM){printf("EEEE");  local_counter = 0; d->symbol->which = ++param_counter + local_counter; }
   else { d->symbol->which = ++local_counter; }

   expr_resolve(d->value);
   scope_bind(d->name, d->symbol, d->code);

   if(d->type->subtype){
      if(!type_is_atomic(d->type->subtype->kind) && d->type->subtype->kind != TYPE_VOID && d->type->subtype->kind != TYPE_ARRAY) { 
         printf("type error: function %s cannot return arrays or other functions\n", d->name);
         type_error = true;
      }
   }

   if(d->code) {
      scope_enter();
      param_list_resolve(d->type->params);
      stmt_resolve(d->code);
      scope_exit();
   }

   int num_params = 0;
   param_list_typecheck(d->type->params, &num_params);
   if(d->code) { d->symbol->param_counter = num_params; }
   if(d->code && local_counter > 0){ d->symbol->local_counter = local_counter; }
   if(scope_correct()) { symbol_print(d->symbol); }
   decl_resolve(d->next);
}

void decl_delete( struct decl *d ){
   if(!d) { return; }
   expr_delete(d->value);
   stmt_delete(d->code);
   //type_delete(d->type);
   symbol_delete(d->symbol);
   decl_delete(d->next);
   free(d->name);
   free(d);
}

void decl_typecheck( struct decl * d ){
   if(!d) { return; }
   stmt_return_found = false;
   struct type * t = 0;
   if(d->value && d->type->kind != TYPE_ARRAY){
      t = expr_typecheck(d->value);
      if(!type_equals(t, d->symbol->type)){
         printf("type error: (%s) is of type ", d->name);
         type_print(d->type);
         printf(" but must be of type ");
         type_print(t);
         printf("\n");
         type_error = true;
      }
      else if(t->kind == TYPE_FUNCTION){
         printf("type error: (%s) cannot be assigned to function ", d->name);
         expr_print(d->value);
         printf("\n");
         type_error = true;
      }
   }

   if(d->type->kind == TYPE_ARRAY){
      if(!type_is_atomic(d->type->subtype->kind)/* && d->type->subtype->kind != TYPE_ARRAY */){
         printf("type error: array cannot be made up of ");
         type_print(d->type->subtype);
         printf("\n");
         type_error = true;
      }
      if(d->value){
         decl_array_typecheck(d->type, d->value->right);
      }
   }
   if(d->code){ 
      stmt_typecheck(d->code, d);
      if(d->type->subtype->kind != TYPE_VOID && !stmt_return_found){ 
      //   printf("type error: expected return type of ");
      //   type_print(d->type->subtype);
      //   printf(" from function %s\n", d->name);
      //  type_error = true;
      }
      if(d->symbol->kind != SYMBOL_GLOBAL){
         printf("type error: static array intialization must be global\n");
         type_error = true;
      }
   }
   decl_typecheck(d->next);
}

void decl_array_typecheck( struct type * t, struct expr * e ){
   if(!e || !t) { return; }
   if(!t->arrSubscript || t->arrSubscript->literal_value <= 0) { printf("type error: invalid subscript or type\n"); type_error = true; return; }
   int counter = 0;
   struct type * temp_t = 0;
   
   while(e->left){
      counter++;
      temp_t = expr_typecheck(e->right);
      if(!type_equals(t->subtype, temp_t)){ stmt_error_print(e->right, temp_t, t->subtype); }
      e = e->left;
   }

   counter++;
   temp_t = expr_typecheck(e);
   if(!type_equals(t->subtype, temp_t)){ stmt_error_print(e, temp_t, t->subtype); }

   if(counter != t->arrSubscript->literal_value){ printf("type error: Expected %d inputs but %d were given\n", t->arrSubscript->literal_value, counter); type_error = true; }

   //decl_array_typecheck(t->subtype->subtype, e->right);
}

void decl_codegen ( struct decl * d ){
   if(!d) { return; }
   if(d->code){
      fprintf(ofp, ".text\n");
      fprintf(ofp, "   .global %s\n", d->name);
      fprintf(ofp, "%s:\n", d->name);
      fprintf(ofp, "   PUSHQ %%rbp\n");
      fprintf(ofp, "   MOVQ %%rsp, %%rbp\n");
      decl_push_args(d->type->params, 0);
      fprintf(ofp, "   SUBQ $%d, %%rsp\n", d->symbol->local_counter * 8);
      decl_push_saved_regs();
      stmt_codegen(d->code, d);
      decl_postamble();
   }
   else{
      int value = 0;
      char * string = 0;
      if(d->symbol->kind == SYMBOL_GLOBAL){
         fprintf(ofp, ".data\n");
         fprintf(ofp, "   .global %s\n", d->name);
         if(d->value){
            value = d->value->literal_value;
            string = d->value->string_literal;
         }
         if(d->type->kind == TYPE_STRING){
            fprintf(ofp, "%s:\n", d->name);
            fprintf(ofp, "   .string \"%s\"\n", string); 
         }
         else if(d->type->kind == TYPE_ARRAY) {
            fprintf(ofp, "%s:\n", d->name);
            if(d->value) { decl_gen_array(d->value->right); }
            else{
               for(value = 0; value < d->type->arrSubscript->literal_value; value++){ fprintf(ofp, "   .quad 0\n"); }
            }
         }
         else{
            if(d->type->kind != TYPE_FUNCTION){
               fprintf(ofp, "%s:\n", d->name); 
               fprintf(ofp, "   .quad %d\n", value); 
            }
         }
      }
      else{
         if(d->value){
            expr_codegen(d->value);
            fprintf(ofp, "   MOVQ %s, %s\n", scratch_name(d->value->reg), symbol_codegen(d->symbol));
            scratch_free(d->value->reg);
         }
         else{
            fprintf(ofp, "   MOVQ $0, %s\n", symbol_codegen(d->symbol));
         }
      }
   }

   decl_codegen(d->next);
}

void decl_push_args( struct param_list * p, int counter ){
   if(!p) { return; }
   decl_push_args(p->next, ++counter);
   switch (counter){
      case 1:
         fprintf(ofp, "   PUSHQ %%rdi\n");
         break;
      case 2:
         fprintf(ofp, "   PUSHQ %%rsi\n");
         break;
      case 3:
         fprintf(ofp, "   PUSHQ %%rdx\n");
         break;
      case 4:
         fprintf(ofp, "   PUSHQ %%rcx\n");
         break;
      case 5:
         fprintf(ofp, "   PUSHQ %%r8\n");
         break;
      case 6:
         fprintf(ofp, "   PUSHQ %%r9\n");
         break;
      default:
         printf("codegen error: Too many function arguments\n");
         exit(1);
         break;
   }
}

void decl_push_saved_regs(){
   fprintf(ofp, "   PUSHQ %%r12\n");
   fprintf(ofp, "   PUSHQ %%r13\n");
   fprintf(ofp, "   PUSHQ %%r14\n");
   fprintf(ofp, "   PUSHQ %%r15\n");
   fprintf(ofp, "   PUSHQ %%rbx\n");
}

void decl_pop_saved_regs(){
   fprintf(ofp, "   POPQ %%rbx\n");
   fprintf(ofp, "   POPQ %%r15\n");
   fprintf(ofp, "   POPQ %%r14\n");
   fprintf(ofp, "   POPQ %%r13\n");
   fprintf(ofp, "   POPQ %%r12\n");
}

void decl_postamble(){
   decl_pop_saved_regs();
   fprintf(ofp, "   MOVQ %%rbp, %%rsp\n");
   fprintf(ofp, "   POPQ %%rbp\n");
   fprintf(ofp, "   RET\n");
}

void decl_gen_array( struct expr * e ){
   if(!e) { return; }
   decl_gen_array(e->left);
   if(e->right) { fprintf(ofp, "   .quad %d\n", e->right->literal_value); }
   else { fprintf(ofp, "   .quad %d\n", e->literal_value); }
}