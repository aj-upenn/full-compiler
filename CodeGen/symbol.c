#include <stdlib.h>
#include "symbol.h"

struct symbol * symbol_create( symbol_t kind, struct type *type, char *name ){
   struct symbol * s = malloc(sizeof(struct symbol));
   s->kind = kind;
   s->type = type;
   s->name = name;
   s->which = 0;
   s->local_counter = 0;
   s->param_counter = 0;
   return s;
}

void symbol_print( struct symbol * s ){
   if(!s) { return; }

   printf("%s resolves to ", s->name);
   switch(s->kind){
      case SYMBOL_GLOBAL:
         printf("global %s", s->name);
         break;
      case SYMBOL_LOCAL:
         printf("local %d", s->which);
         break;
      case SYMBOL_PARAM:
         printf("param %d", s->which);
         break;
      default:
         break;
   }

   printf("\n");
}

void symbol_delete( struct symbol * s ){
   if(!s) { return; }
   type_delete(s->type);
   free(s->name);
   free(s);
}

const char * symbol_codegen( struct symbol * s ){
   if(!s) { return 0; }

   char * buf = 0;

   switch(s->kind){
      case SYMBOL_GLOBAL: 
         return s->name;
      case SYMBOL_PARAM:
         buf = malloc(12);
         sprintf(buf, "%d(%%rbp)", s->which * -8); 
         return buf;
      case SYMBOL_LOCAL:
         buf = malloc(12);
         sprintf(buf, "%d(%%rbp)", (s->which + s->param_counter) * -8); 
         return buf;
      default:
         break;
   }

   return 0;
}