
#include <stdio.h>
#include <stdlib.h>
#include "printerFunc.h"
#include "stmt.h"
#include "decl.h"
#include "expr.h"
#include "param_list.h"
#include "type.h"

extern int yyparse();
extern int yylex_destroy();
extern FILE *yyin;
extern struct decl * program_pointer;

void printFile(){
   if(yyparse() == 0){ decl_print(program_pointer, 0); fclose(yyin); yylex_destroy(); }
   else{ printf("Parse Failed!\n"); fclose(yyin); yylex_destroy(); exit(1); } 
}

void indentLine(int indent){
   int i = 0;
   for(i = 0; i < indent; i++){ printf(" "); }
}
