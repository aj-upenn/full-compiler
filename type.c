#include <stdlib.h>
#include "type.h"
#include "expr.h"

bool type_error = false;

struct type * type_create( type_t kind, struct type *subtype, struct param_list *params ){
   struct type * t = malloc(sizeof(struct type));
   t->kind = kind;
   t->subtype = subtype;
   t->params = params;
   t->arrSubscript = 0;
   return t;
}


void type_print( struct type *t ){
   if(!t) { return; }
   switch(t->kind){
      case TYPE_STRING:
         printf("string");
         break;
      case TYPE_BOOLEAN:
         printf("boolean");
         break;
      case TYPE_AUTO:
         printf("auto");
         break;
      case TYPE_CHAR:
         printf("char");
         break;
      case TYPE_INTEGER:
         printf("integer");
         break;
      case TYPE_VOID:
         printf("void");
         break;   
      case TYPE_FUNCTION:
         printf("function ");
         type_print(t->subtype);
         printf(" (");
         param_list_print(t->params);
         printf(")");
         break;
      case TYPE_ARRAY:
         printf("array [");
         expr_print(t->arrSubscript);
         printf("] ");
         type_print(t->subtype);
         break;
      default:
         break;
   }
}

void type_delete( struct type *t ){
   if(!t) { return; }
   type_delete(t->subtype);
   param_list_delete(t->params);
   expr_delete(t->arrSubscript);
   free(t);
}

bool type_equals( struct type * a, struct type * b ){
   if(!a && !b) { return true;}
   else if((!a && b) || (a && !b)) { return false; }
   type_t k = a->kind;
   if(k == b->kind){
      if(type_is_atomic(k)){ return true; }
      else if(k == TYPE_ARRAY){ 
         if(type_equals(a->subtype, b->subtype)){ return true; }
      }
      else if(k == TYPE_FUNCTION) { 
         if(type_equals(a->subtype, b->subtype) && param_list_equals(a->params, b->params)){ return true; }
      }
   }

   return false;
}

struct type * type_copy( struct type * t ){
   if(!t) { return 0; }
   return type_create(t->kind, t->subtype, param_list_copy(t->params));
}

bool type_is_atomic(type_t k){
   return (k == TYPE_BOOLEAN || k == TYPE_CHAR || k == TYPE_STRING || k == TYPE_INTEGER || k == TYPE_AUTO);
}