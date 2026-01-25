#include <stdlib.h>
#include "stmt.h"
#include "printerFunc.h"
#include "scope.h"
#include "codegenFunc.h"

bool stmt_return_found = false;
extern bool type_error;
extern FILE * ofp;

struct stmt * stmt_create( stmt_t kind, struct decl *decl, struct expr *init_expr, struct expr *expr, struct expr *next_expr, struct stmt *body, struct stmt *else_body, struct stmt *next ){
   struct stmt * s = malloc(sizeof(struct stmt));
   s->kind = kind;
   s->decl = decl;
   s->init_expr = init_expr;
   s->expr = expr;
   s->next_expr = next_expr;
   s->body = body;
   s->else_body = else_body;
   s->next = next;
   return s;
}


void stmt_print( struct stmt *s, int indent ){
   if(!s) { return; }
   indentLine(indent + INDENT);
   struct stmt * to_print = 0;
   switch(s->kind){
      case STMT_DECL:
         decl_print(s->decl, indent);
         break;
      case STMT_EXPR:
         expr_print(s->expr);
         printf(";\n");
         break;
      case STMT_BLOCK:
         stmt_print_block(s->body, indent + INDENT);
         break;
      case STMT_FOR:
         printf("for(");
         expr_print(s->init_expr);
         printf(";");
         expr_print(s->expr);
         printf(";");
         expr_print(s->next_expr);
         printf(") ");
         if(s->body->kind != STMT_BLOCK){ stmt_print_block(s->body, indent); }
         else{ 
            to_print = s->body->body;
            if(!to_print) { to_print = s->body; }
            stmt_print_block(to_print, indent);
         }

         break;
         
      case STMT_IF_ELSE:
         printf("if(");
         expr_print(s->expr);
         printf(") ");
         if(s->body->kind != STMT_BLOCK){ stmt_print_block(s->body, indent); }
         else{ 
            to_print = s->body->body;
            if(!to_print) { to_print = s->body; }
            stmt_print_block(to_print, indent);
         }


         if(s->else_body){
            to_print = s->else_body->body;
            if(!to_print) { to_print = s->else_body; }
            indentLine(indent + INDENT);
            printf("else ");
            stmt_print_block(to_print, indent);
         }

         break;   
      case STMT_RETURN:
         stmt_return_found = true;
         printf("return ");
         expr_print(s->expr);
         printf(";\n");
         break;
      case STMT_PRINT:
         printf("print ");
         expr_print(s->expr);
         printf(";\n");
         break;
      default:
         break;
   }

   stmt_print(s->next, indent);
}

void stmt_print_block(struct stmt * to_print, int indent){
   printf("{\n");
   stmt_print(to_print, indent + INDENT);
   if(!to_print){ indentLine(indent); }
   else { indentLine(indent + INDENT); }
   printf("}\n");
}

void stmt_delete( struct stmt * s ){
   if(!s) { return; }
   decl_delete(s->decl);
   expr_delete(s->init_expr);
   expr_delete(s->expr);
   expr_delete(s->next_expr);
   stmt_delete(s->body);
   stmt_delete(s->else_body);
   stmt_delete(s->next);
   free(s);
}

void stmt_resolve( struct stmt * s ){
   if(!s) { return; }
   decl_resolve(s->decl);
   expr_resolve(s->init_expr);
   expr_resolve(s->expr);
   expr_resolve(s->next_expr);
   scope_enter();
   stmt_resolve(s->body);
   scope_exit();
   scope_enter();
   stmt_resolve(s->else_body);
   scope_exit();
   stmt_resolve(s->next);
}

bool stmt_equals( struct stmt * a, struct stmt * b ){
   return true;
}

void stmt_typecheck( struct stmt * s, struct decl * d ){
   if(!s) { return; }
   struct type * t = 0;
   struct expr * expr_temp = 0;
   switch(s->kind){
      case STMT_EXPR:
         t = expr_typecheck(s->expr);
         break;
      case STMT_IF_ELSE:
         t = expr_typecheck(s->expr);
         if(t->kind != TYPE_BOOLEAN){ 
            struct type * t2 = type_create(TYPE_BOOLEAN, 0, 0);
            stmt_error_print(s->expr, t, t2); 
         }

         stmt_typecheck(s->body, d);
         stmt_typecheck(s->else_body, d);
         break;
      case STMT_DECL:
         t = expr_typecheck(s->decl->value);
         if(s->decl->type->kind == TYPE_ARRAY){
            printf("type error: static arrays cannot be local\n"); type_error = true;
         }
         else if(t && !type_equals(t, s->decl->type)){ 
            if(t->kind != TYPE_FUNCTION){
               if(s->decl->type->kind == TYPE_AUTO){ s->decl->symbol->type = type_copy(t); }
               else{
                  printf("type error: (%s) is of type ", s->decl->name);
                  type_print(s->decl->type);
                  printf(" but must be of type ");
                  type_print(t);
                  printf("\n");
                  type_error = true;
               }
            }

         }
         break;
      case STMT_BLOCK:
         stmt_typecheck(s->body, d);
         break;
      case STMT_FOR:
         expr_typecheck(s->init_expr);
         expr_typecheck(s->expr);
         expr_typecheck(s->next_expr);
         stmt_typecheck(s->body, d);
         break;
      case STMT_PRINT:
         if(!s->expr) { break; }
         expr_temp = s->expr;
         while(1){
            t = expr_typecheck(s->expr);
            if(!type_is_atomic(t->kind)){ expr_error_print_1("print", t, s->expr); }
            s->expr = s->expr->right;
            if(!s->expr) { break; }
         }
         s->expr = expr_temp;
         break;
      case STMT_RETURN:
         t = expr_typecheck(s->expr);
         if(d->type->subtype->kind == TYPE_AUTO){ d->type->subtype = type_copy(t); }
         if(!type_equals(t, d->type->subtype)){ 
            if(d->type->subtype->kind == TYPE_VOID){ 
               if(t != 0){ stmt_error_print(s->expr, t, d->type->subtype); }
            }
            else{ stmt_error_print(s->expr, t, d->type->subtype); }
         }
         stmt_return_found = true;
         break;
      default:
         break;
   }
   //type_delete(t);
   stmt_typecheck(s->next, d);
}

void stmt_error_print( struct expr * e, struct type *t1, struct type *t2 ){
   printf("type error: (");
   expr_print(e);
   printf(") is of type ");
   if(!t1) { printf("void"); }
   else { type_print(t1); }
   printf(" but must be of type ");
   if(!t2) { printf("void "); }
   else{ type_print(t2); } 
   printf("\n");
   type_error = true;
}

void stmt_codegen( struct stmt * s, struct decl * d ){
   if(!s) { return; }
   char * l1 = 0;
   char * l2 = 0;
   struct type * t = 0;
   switch (s->kind){
      case STMT_DECL:
         s->decl->symbol->param_counter = d->symbol->param_counter;
         s->decl->symbol->local_counter = d->symbol->local_counter;
         decl_codegen(s->decl);
         break;
      case STMT_EXPR:
         expr_codegen(s->expr);
         scratch_free(s->expr->reg);
         break;
      case STMT_BLOCK:
         stmt_codegen(s->body, d);
         break;
      case STMT_FOR:
         if(s->init_expr){ 
            expr_codegen(s->init_expr);
            scratch_free(s->init_expr->reg); 
         }
         l1 = label_name(label_create());
         l2 = label_name(label_create());
         label_print(l1);
         
         if(s->expr) { 
            expr_codegen(s->expr);
            fprintf(ofp, "   CMPQ $0, %s\n", scratch_name(s->expr->reg));
            fprintf(ofp, "   JE %s\n", l2);
            scratch_free(s->expr->reg); 
         }
         stmt_codegen(s->body, d);

         if(s->next_expr) { 
            expr_codegen(s->next_expr);
            fprintf(ofp, "   JMP %s\n", l1);
            scratch_free(s->next_expr->reg); 
         }
         label_print(l2);
         break;
      case STMT_IF_ELSE:
         l1 = label_name(label_create());
         l2 = label_name(label_create());
         expr_codegen(s->expr);
         fprintf(ofp, "   CMPQ $0, %s\n", scratch_name(s->expr->reg));
         scratch_free(s->expr->reg);
         fprintf(ofp, "   JE %s\n", l1);
         stmt_codegen(s->body, d);
         fprintf(ofp, "   JMP %s\n", l2);
         label_print(l1);
         stmt_codegen(s->else_body, d);
         label_print(l2);
         break;   
      case STMT_RETURN:
         if(s->expr){
            expr_codegen(s->expr);
            if(d->type->subtype->kind != TYPE_VOID){ fprintf(ofp, "   MOVQ %s, %%rax\n", scratch_name(s->expr->reg)); }
            scratch_free(s->expr->reg);
         }
         decl_postamble();
         break;
      case STMT_PRINT:
         while(s->expr){
            t = expr_typecheck(s->expr);
            if(!t) { break; }
            expr_codegen(s->expr);
            fprintf(ofp, "   MOVQ %s, %%rdi\n", scratch_name(s->expr->reg));
            scratch_free(s->expr->reg);
            expr_push_saved_regs();
            switch (t->kind){
               case TYPE_INTEGER:
                  fprintf(ofp, "   CALL print_integer\n");
                  break;
               case TYPE_CHAR:
                  fprintf(ofp, "   CALL print_character\n");
                  break;
               case TYPE_BOOLEAN:
                  fprintf(ofp, "   CALL print_boolean\n");
                  break;
               case TYPE_STRING:
                  if(s->expr->left->symbol && s->expr->left->symbol->kind == SYMBOL_GLOBAL){ 
                     fprintf(ofp, "   LEAQ %s, %%rdi\n", s->expr->left->name); 
                  }
                  fprintf(ofp, "   CALL print_string\n");
                  break;
               default:
                  break;
               }
            //stmt_print_space();
            expr_pop_saved_regs();
            s->expr = s->expr->right;
         }
         break;
      default:
         break;
   }
   stmt_codegen(s->next, d);
}


void stmt_print_space(){
   expr_push_saved_regs();
   fprintf(ofp, "   MOVQ $32, %%rdi\n");
   fprintf(ofp, "   CALL print_character\n");
   expr_pop_saved_regs();
}
//ARRAY CHECKS
/*
if(!type_is_atomic(s->decl->type->subtype->kind) && s->decl->type->subtype->kind != TYPE_ARRAY){
   printf("type error: array cannot be made up of ");
   type_print(s->decl->type->subtype);
   printf("\n");
   type_error = true;
}
t = expr_typecheck(s->decl->type->arrSubscript);
if(!t || t->kind != TYPE_INTEGER){
   printf("type error: array intializer (");
   expr_print(s->decl->type->arrSubscript);
   printf(") must be an integer\n");
   type_error = true;
}
*/