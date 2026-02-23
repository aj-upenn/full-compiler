#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "scannerAssemblerFunc.h"
#include "parserAssemblerFunc.h"
#include "printerAssemblerFunc.h"

extern FILE *yyin;
// extern struct decl * program_pointer;

int main(int argc, char *argv[]){
   if(argc != 3 && argc != 4){ fprintf(stderr, "Invalid number of inputs. Exiting.\n"); exit(1); }
   char *flag= argv[1];
   char *filename = argv[2];

   yyin = fopen(filename, "r");
   //if(!yyin) { printf("Invalid input file. Exiting.\n"); exit(1); }
   
   if(!strcmp(flag, "-scan")){ scanFile(false); }
   else if(!strcmp(flag, "-parse")){ scanFile(true); yyin = fopen(filename, "r"); parseFile();}
   else if(!strcmp(flag, "-print")){ scanFile(true); yyin = fopen(filename, "r"); printFile(); }


   return 0;
}

