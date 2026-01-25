#include <stdlib.h>
#include <stdio.h>
#include "typecheckerFunc.h"
#include "printerFunc.h"
#include "decl.h"
#include "scope.h"


extern bool type_error;
extern int yyparse();
extern int yylex_destroy();
extern FILE *yyin;
struct decl * program_pointer;

void resolveFile(){
   if(yyparse() == 0){ 
      fclose(yyin); 
      yylex_destroy();
      scope_enter();
      scope_create_function_code();
      decl_resolve(program_pointer);
      scope_delete_function_code();
      if(!scope_correct()) { exit(1); }
   }
   else{ 
      printf("Parse Failed!\n"); 
      fclose(yyin); 
      yylex_destroy(); 
      exit(1); 
   } 
}

void typecheckFile(){
   resolveFile();
   decl_typecheck(program_pointer);
   if(type_error){ exit(1); }
}


