
#include "scope.h"
#include "hash_table.h"

struct scope_table scope_table = { .stack = {0}, .level = -1, .error_found = false };
struct hash_table * function_table;

void scope_enter(){
   scope_table.stack[++scope_table.level] = hash_table_create(0, 0);
}

void scope_exit(){
   hash_table_delete(scope_table.stack[scope_table.level--]);
}

int scope_level(){
   return scope_table.level;
}

void scope_bind( const char * name, struct symbol * sym, struct stmt * code ){
   if(!sym || !name) { return; }
   struct symbol * p = scope_lookup_current(name);
   if(p){
      if(sym->type->kind == TYPE_FUNCTION){
         if(!type_equals(p->type, sym->type)){ scope_error(name, SCOPE_ALREADY_DEFINED); }
         if(code){
            if(hash_table_lookup(function_table, name)){ scope_error(name, SCOPE_ALREADY_DEFINED); }
            else{ hash_table_insert(function_table, name, sym); }
         }
      }
      else{
         scope_error(name, SCOPE_ALREADY_DEFINED);
      }
   }
   else{
      hash_table_insert(scope_table.stack[scope_table.level], name, sym);
      if((sym->type->kind == TYPE_FUNCTION) && code){ hash_table_insert(function_table, name, sym); }
   }
}

struct symbol *scope_lookup( const char *name ){
   if(!name) { return 0; }
   int l = scope_table.level;
   struct symbol * s = 0;
   while(l >= 0){
      s = hash_table_lookup(scope_table.stack[l], name);
      if(s){ return s; }
      l--;
   }
   
   return 0;
}

struct symbol *scope_lookup_current( const char *name ){
   struct symbol * s = hash_table_lookup(scope_table.stack[scope_table.level], name);
   if(s) { return s; }
   return 0;
}

void scope_error( const char * s, int type){
   printf("Resolve Error: %s ", s);
   if(type == SCOPE_ALREADY_DEFINED){ printf("is already defined\n"); }
   else{ printf("is not defined\n"); }
   scope_table.error_found = true;
}


bool scope_correct(){
   return !scope_table.error_found;
}

void scope_create_function_code(){
   function_table = hash_table_create(0, 0);
}

void scope_delete_function_code(){
   hash_table_delete(function_table);
}