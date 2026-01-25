#include <stdio.h>
#include <stdlib.h>
#include "parserFunc.h"

extern int yyparse();
extern int yylex_destroy();
extern FILE *yyin;

void parseFile(){
   if(yyparse() == 0){ printf("Parse Successful!\n"); fclose(yyin); yylex_destroy(); }
   else{ printf("Parse Failed!\n"); fclose(yyin); yylex_destroy(); exit(1); } 
}