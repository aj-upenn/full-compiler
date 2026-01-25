#include <stdlib.h>
#include "param_list.h"
#include "decl.h"
#include "scope.h"

extern int param_counter;
extern bool type_error;

struct param_list * param_list_create( char *name, struct type *type, struct param_list *next ){
   struct param_list * p = malloc(sizeof(struct param_list));
   p->name = name;
   p->type = type;
   p->next = next;
   p->symbol = 0;
   return p;
}

void param_list_print( struct param_list *a ){
   if(!a) { return; }
   printf("%s: ", a->name);
   type_print(a->type);
   if(a->next){
      printf(", ");
      param_list_print(a->next);
   }
}

void param_list_resolve( struct param_list * p ){
   if(!p) { return; }

   p->symbol = symbol_create(SYMBOL_PARAM, p->type, p->name);

   p->symbol->which = ++param_counter;
   scope_bind(p->name, p->symbol, 0);

   symbol_print(p->symbol);
   param_list_resolve(p->next);
   return;
}

void param_list_delete( struct param_list * p ){
   if(!p) { return; }
   type_delete(p->type);
   symbol_delete(p->symbol);
   param_list_delete(p->next);
   free(p);
}

struct param_list * param_list_copy( struct param_list * p ){
   if(!p) { return 0; }
   return param_list_create(p->name, type_copy(p->type), param_list_copy(p->next));
}

bool param_list_equals( struct param_list * a,  struct param_list * b ){
   if(!a && !b) { return true; }
   if(!a || !b) { return false; }
   if(type_equals(a->type, b->type)) { return param_list_equals(a->next, b->next); }
   else{ return false; } 
   return true;
}

void param_list_typecheck( struct param_list * p, int * counter ){
   if(!p) { return; }
   if((!type_is_atomic(p->type->kind) && p->type->kind != TYPE_ARRAY)){ 
      printf("type error: function cannot have ");
      type_print(p->type);
      printf(" as a paramter\n");
      type_error = true;
   }
   (*counter)++;
   param_list_typecheck(p->next, counter);
}