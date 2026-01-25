#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "decl.h"
#include "scannerFunc.h"
#include "parserFunc.h"
#include "printerFunc.h"
#include "typecheckerFunc.h"
#include "codegenFunc.h"

extern FILE *yyin;
extern struct decl * program_pointer;

int main(int argc, char *argv[]){
   if(argc != 3 && argc != 4){ fprintf(stderr, "Invalid number of inputs. Exiting.\n"); exit(1); }
   char *flag= argv[1];
   char *filename = argv[2];

   yyin = fopen(filename, "r");
   if(!yyin) { printf("Invalid input file. Exiting.\n"); exit(1); }
   
   if(!strcmp(flag, "-scan")){ scanFile(false); }
   else if(!strcmp(flag, "-parse")){ scanFile(true); yyin = fopen(filename, "r"); parseFile(); }
   else if(!strcmp(flag, "-print")){ scanFile(true); yyin = fopen(filename, "r"); printFile(); }
   else if(!strcmp(flag, "-resolve")){ scanFile(true); yyin = fopen(filename, "r"); resolveFile(); }
   else if(!strcmp(flag, "-typecheck")){ scanFile(true); yyin = fopen(filename, "r"); typecheckFile(); }
   else if(!strcmp(flag, "-codegen")){ 
      if(argc != 4){ printf("Invalid ourput file. Exiting.\n"); exit(1); }
      scanFile(true); yyin = fopen(filename, "r"); typecheckFile(); 
      codegen(argv[2], argv[3]);
   }
   else{ fprintf(stderr, "Invalid flag. Exiting.\n"); exit(1); } 

   //decl_delete(program_pointer);
   return 0;
}

